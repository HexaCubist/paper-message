#include <FetchBMP.h>


const int httpsPort = 443;

uint8_t input_buffer[3 * input_buffer_pixels]; // up to depth 24
uint8_t output_row_mono_buffer[display_width / 8]; // buffer for at least one row of b/w bits
uint8_t output_row_color_buffer[display_width / 8]; // buffer for at least one row of color bits
uint8_t mono_palette_buffer[max_palette_pixels / 8]; // palette buffer for depth <= 8 b/w
uint8_t color_palette_buffer[max_palette_pixels / 8]; // palette buffer for depth <= 8 c/w
uint16_t rgb_palette_buffer[max_palette_pixels]; // palette buffer for depth <= 8 for buffered graphics, needed for 7-color display



uint16_t read16(WiFiClient* client)
{
	// BMP data is stored little-endian, same as Arduino.
	uint16_t result;
	((uint8_t *)&result)[0] = client->read(); // LSB
	((uint8_t *)&result)[1] = client->read(); // MSB
	return result;
}

uint32_t read32(WiFiClient* client)
{
	// BMP data is stored little-endian, same as Arduino.
	uint32_t result;
	((uint8_t *)&result)[0] = client->read(); // LSB
	((uint8_t *)&result)[1] = client->read();
	((uint8_t *)&result)[2] = client->read();
	((uint8_t *)&result)[3] = client->read(); // MSB
	return result;
}


uint32_t skip(WiFiClient* client, int32_t bytes)
{
	int32_t remain = bytes;
	uint32_t start = millis();
	while ((client->connected() || client->available()) && (remain > 0))
	{
		if (client->available())
		{
			client->read();
			remain--;
		}
		else delay(1);
		if (millis() - start > 2000) break; // don't hang forever
	}
	return bytes - remain;
}

uint32_t read8n(WiFiClient* client, uint8_t* buffer, int32_t bytes) {
	int32_t remain = bytes;
	uint32_t start = millis();
	while ((client->connected() || client->available()) && (remain > 0))
	{
		if (client->available())
		{
			int16_t v = client->read();
			*buffer++ = uint8_t(v);
			remain--;
		}
		else delay(1);

		if (millis() - start > 2000) break; // don't hang forever
	}
	return bytes - remain;
}



// const char* host, const char* path, const char* filename, const char* fingerprint, int16_t x, int16_t y,
bool loadBitmap(uint8_t mono_buffer[display_m_height*display_m_width], uint8_t page_num, char* api_token, bool with_color) {

	Serial.print("connecting to "); Serial.println(rsb_host);


	// Not validating server
	uint32_t startTime = millis();
	
	// path + user_token + pagesEndpoint
	char full_path [128];

	if (!snprintf(full_path, 128, "https://%s/api/%s/pages/%d", rsb_host, api_token, page_num)) {
		// Buffer too small
		Serial.println("Buffer too small");
		return false;
	}

	HTTPClient& http = HttpClientSingleton::getInstance();


	http.setUserAgent("ESP32_Zac_EPaper");
	http.setReuse(true);
	
	http.begin(full_path);

	int httpCode = http.GET();

	if (httpCode != HTTP_CODE_OK) {
		Serial.print("HTTP Code: ");
		Serial.println(httpCode);
		return false;
	}

	int len = http.getSize();


	bool connection_ok = true;
	bool valid = false; // valid format to be handled
	bool flip = true; // bitmap is stored bottom-to-topO


	Serial.println();
	Serial.print("downloading file \""); Serial.print(full_path);  Serial.println("\"");

	
	WiFiClient *stream = http.getStreamPtr();


	Serial.println("request sent");


	// Hunt stream for BMP header
	uint16_t signature = 0;
	for (int16_t i = 0; i < 50; i++) {
		if (!stream->available()) delay(100);
		else signature = read16(stream);
		//Serial.print("signature: 0x"); Serial.println(signature, HEX);
		if (signature == 0x4D42) break;
	}

	// BMP signature
	if (signature != 0x4D42) {
		stream->stop();

		Serial.print("Invalid file signature on image loaded! Found: ");
		Serial.println(signature, HEX);
		return false;
	}

    uint32_t fileSize = read32(stream);
	uint32_t creatorBytes = read32(stream); (void)creatorBytes; //unused
	uint32_t imageOffset = read32(stream); // Start of image data
	uint32_t headerSize = read32(stream);
	uint32_t width  = read32(stream);
	int32_t height = (int32_t) read32(stream);
	uint16_t planes = read16(stream);
	uint16_t depth = read16(stream); // bits per pixel
	uint32_t format = read32(stream);
	uint32_t bytes_read = 7 * 4 + 3 * 2; // read so far

	// uncompressed is handled, 565 also
	if (!((planes == 1) && ((format == 0) || (format == 3)))) {
		Serial.print("Invalid format: "); Serial.print(planes); Serial.print('x'); Serial.println(format);
		stream->stop();
		return false;
	}

	Serial.print("File size: "); Serial.println(fileSize);
	Serial.print("Image Offset: "); Serial.println(imageOffset);
	Serial.print("Header size: "); Serial.println(headerSize);
	Serial.print("Bit Depth: "); Serial.println(depth);
	Serial.print("Image size: ");
	Serial.print(width);
	Serial.print('x');
	Serial.println(height);

	// BMP rows are padded (if needed) to 4-byte boundary
	uint32_t rowSize = (width * depth / 8 + 3) & ~3;
	if (depth < 8) rowSize = ((width * depth + 8 - depth) / 8 + 3) & ~3;
	if (height < 0)
	{
		height = -height;
		flip = false;
	}
	uint16_t w = width;
	uint16_t h = height;

	if (w > max_row_width) {
		Serial.println("File too large for buffer");
		stream->stop();
		return false;
	}
	// handle with direct drawing
	valid = true;
	uint8_t bitmask = 0xFF;
	uint8_t bitshift = 8 - depth;
	uint16_t red, green, blue;
	bool whitish = false;
	bool colored = false;
	
	if (depth == 1) with_color = false;

	if (depth <= 8) {
		if (depth < 8) bitmask >>= depth;

		//bytes_read += skip(client, 54 - bytes_read); //palette is always @ 54
		bytes_read += skip(stream, imageOffset - (4 << depth) - bytes_read); // 54 for regular, diff for colorsimportant
		
		for (uint16_t pn = 0; pn < (1 << depth); pn++) {
			blue  = stream->read();
			green = stream->read();
			red   = stream->read();
			stream->read();
			bytes_read += 4;
			whitish = with_color ? ((red > 0x80) && (green > 0x80) && (blue > 0x80)) : ((red + green + blue) > 3 * 0x80); // whitish
			colored = (red > 0xF0) || ((green > 0xF0) && (blue > 0xF0)); // reddish or yellowish?
			if (0 == pn % 8) mono_palette_buffer[pn / 8] = 0;
			mono_palette_buffer[pn / 8] |= whitish << pn % 8;
			if (0 == pn % 8) color_palette_buffer[pn / 8] = 0;
			color_palette_buffer[pn / 8] |= colored << pn % 8;
		}
	}
		
	uint32_t rowPosition = flip ? imageOffset + (height - h) * rowSize : imageOffset;
	//Serial.print("skip "); Serial.println(rowPosition - bytes_read);
	bytes_read += skip(stream, rowPosition - bytes_read);
	
	// Scan through image data rows
	for (uint16_t row = 0; row < h; row++, rowPosition += rowSize) {
		if (!connection_ok || !(http.connected() || stream->available())) {
			Serial.println("Connection lost!");
			Serial.print("Row: "); Serial.println(row);
			Serial.print("Connection: "); Serial.println(connection_ok);
			Serial.print("HTTP: "); Serial.println(http.connected());
			Serial.print("Stream: "); Serial.println(stream->available());
			
			break;
		}

		delay(1); // yield() to avoid WDT
		uint32_t in_remain = rowSize;
		uint32_t in_idx = 0;
		uint32_t in_bytes = 0;
		uint8_t in_byte = 0; // for depth <= 8
		uint8_t in_bits = 0; // for depth <= 8
		uint8_t out_byte = 0xFF; // white (for w%8!=0 border)
		uint8_t out_color_byte = 0xFF; // white (for w%8!=0 border)
		uint32_t out_idx = 0;

		// Individual pixels in row
		for (uint16_t col = 0; col < w; col++) // for each pixel
		{
			yield(); // Let the rest of the RTOS have some CPU time :)

			if (!connection_ok || !(http.connected() || stream->available())) break;

			// Time to read more pixel data?
			if (in_idx >= in_bytes) {
				// ok, exact match for 24bit also (size IS multiple of 3)
				uint32_t get = in_remain > sizeof(input_buffer) ? sizeof(input_buffer) : in_remain;
				uint32_t got = read8n(stream, input_buffer, get);

				while ((got < get) && connection_ok) {
					//Serial.print("got "); Serial.print(got); Serial.print(" < "); Serial.print(get); Serial.print(" @ "); Serial.println(bytes_read);
					//if ((get - got) > client.available()) delay(200); // does improve? yes, if >= 200

					uint32_t gotmore = read8n(stream, input_buffer + got, get - got);
					got += gotmore;
					connection_ok = gotmore > 0;
				}
				in_bytes = got;
				in_remain -= got;
				bytes_read += got;
			}

			if (!connection_ok) {
				Serial.print("Error: got no more after "); Serial.print(bytes_read); Serial.println(" bytes read!");
				break;
			}

			// Map read data to EInk palette
			switch (depth) {
				case 32:
					blue = input_buffer[in_idx++];
					green = input_buffer[in_idx++];
					red = input_buffer[in_idx++];
					in_idx++; // skip alpha
					whitish = with_color ? ((red > 0x80) && (green > 0x80) && (blue > 0x80)) : ((red + green + blue) > 3 * 0x80); // whitish
					colored = (red > 0xF0) || ((green > 0xF0) && (blue > 0xF0)); // reddish or yellowish?
					break;
				case 24:
					blue = input_buffer[in_idx++];
					green = input_buffer[in_idx++];
					red = input_buffer[in_idx++];
					whitish = with_color ? ((red > 0x80) && (green > 0x80) && (blue > 0x80)) : ((red + green + blue) > 3 * 0x80); // whitish
					colored = (red > 0xF0) || ((green > 0xF0) && (blue > 0xF0)); // reddish or yellowish?
					break;
				case 16:
					{
					uint8_t lsb = input_buffer[in_idx++];
					uint8_t msb = input_buffer[in_idx++];
					if (format == 0) // 555
					{
						blue  = (lsb & 0x1F) << 3;
						green = ((msb & 0x03) << 6) | ((lsb & 0xE0) >> 2);
						red   = (msb & 0x7C) << 1;
					}
					else // 565
					{
						blue  = (lsb & 0x1F) << 3;
						green = ((msb & 0x07) << 5) | ((lsb & 0xE0) >> 3);
						red   = (msb & 0xF8);
					}
					whitish = with_color ? ((red > 0x80) && (green > 0x80) && (blue > 0x80)) : ((red + green + blue) > 3 * 0x80); // whitish
					colored = (red > 0xF0) || ((green > 0xF0) && (blue > 0xF0)); // reddish or yellowish?
					}
					break;
				case 1:
				case 2:
				case 4:
				case 8:
					{
					if (0 == in_bits)
					{
						in_byte = input_buffer[in_idx++];
						in_bits = 8;
					}
					uint16_t pn = (in_byte >> bitshift) & bitmask;
					whitish = mono_palette_buffer[pn / 8] & (0x1 << pn % 8);
					colored = color_palette_buffer[pn / 8] & (0x1 << pn % 8);
					in_byte <<= depth;
					in_bits -= depth;
					}
					break;
			}

			if (whitish) {
				// keep white
			}
			else if (colored && with_color) 	{
				out_color_byte &= ~(0x80 >> col % 8); // colored
			} else {
				out_byte &= ~(0x80 >> col % 8); // black
			}

			if ((7 == col % 8) || (col == w - 1)) {
				// write that last byte! (for w%8!=0 border)

				output_row_color_buffer[out_idx] = out_color_byte;
				output_row_mono_buffer[out_idx++] = out_byte;
				out_byte = 0xFF; // white (for w%8!=0 border)
				out_color_byte = 0xFF; // white (for w%8!=0 border)
			}
		} // end pixel


		int16_t yrow = (flip ? h - row - 1 : row);

		// Save the row to the screen buffer
		int current_index = yrow * display_m_width;
		memcpy(mono_buffer + current_index, output_row_mono_buffer, display_m_width);
	}

	// Processing finished!

	Serial.print("downloaded in "); Serial.print(millis() - startTime); Serial.println(" ms");
	Serial.print("bytes read "); Serial.println(bytes_read);

	http.end();

	
	if (!valid) {
		Serial.println("bitmap format not handled.");
		return false;
	}


  return true;
}

bool configureClient(WiFiClientSecure &client) {
	Serial.print("connecting to "); Serial.println(rsb_host);

	
	Serial.println("connecting to server");
	client.setInsecure();
	
	Serial.println("connecting to server");
	Serial.println(ESP.getFreeHeap());
	if (!client.connect(rsb_host, httpsPort)) {
		Serial.println("connection failed");
		return false;
	}
	Serial.println("connected!");
	return true;
}