#include "DisplayController.h"


// uint8_t input_buffer[3 * input_buffer_pixels]; // up to depth 24
// uint8_t output_row_mono_buffer[max_row_width / 8]; // buffer for at least one row of b/w bits
// uint8_t output_row_color_buffer[max_row_width / 8]; // buffer for at least one row of color bits
// uint8_t mono_palette_buffer[max_palette_pixels / 8]; // palette buffer for depth <= 8 b/w
// uint8_t color_palette_buffer[max_palette_pixels / 8]; // palette buffer for depth <= 8 c/w
// uint16_t rgb_palette_buffer[max_palette_pixels]; // palette buffer for depth <= 8 for buffered graphics, needed for 7-color display




DISPLAY_TYPE display(GxEPD2_DRIVER_CLASS(/*CS=5*/ 5, /*DC=*/ 0, /*RST=*/ 2, /*BUSY=*/ 15)); // my suggested wiring and proto board

const char BootText[] = FIRMWARE_VERSION;

void displayInit() {
	display.init(115200, true, 2, false); // USE THIS for Waveshare boards with "clever" reset circuit, 2ms reset pulse

	renderBuffer(IMAGE_BOOT, UpdateMode::FullRefresh);
	display.setCursor(0, 0);
	display.fillScreen(GxEPD_WHITE);
	display.setRotation(3);
	display.setFont(&FreeMonoBold9pt7b);
	display.setTextColor(GxEPD_BLACK);
	int16_t tbx, tby; uint16_t tbw, tbh;
	display.getTextBounds(BootText, 0, 0, &tbx, &tby, &tbw, &tbh);
	// center the bounding box by transposition of the origin:
	uint16_t x = ((display.width() - tbw) / 2) - tbx;
	uint16_t y = display.height() - tbh;
	display.setCursor(x, y);
    display.print(BootText);


	// Align to controller grid
	uint16_t x_r = (x/8) * 8;
	uint16_t y_r = ((y-tbh)/8) * 8;
	uint16_t w_r = tbw + (x - x_r);
	uint16_t h_r = tbh + (y - y_r);

	display.displayWindow(x_r,y_r,w_r,h_r);

}

void displayError(char* message) {

	// renderBuffer(IMAGE_FAIL, UpdateMode::LiveUpdate);
	display.setCursor(0, 0);
	display.fillScreen(GxEPD_WHITE);
	display.setRotation(0);

	display.drawBitmap(0,0,IMAGE_FAIL, display_width, display_height, GxEPD_WHITE, GxEPD_BLACK);
	display.setRotation(3);
	display.setFont(&FreeMonoBold9pt7b);
	display.setTextColor(GxEPD_BLACK);
	int16_t tbx, tby; uint16_t tbw, tbh;
	display.getTextBounds(message, 0, 0, &tbx, &tby, &tbw, &tbh);
	// center the bounding box by transposition of the origin:
	uint16_t x = SIDEBAR_WIDTH + 2 - tbx;
	uint16_t y = display.height() - tbh;
	display.setCursor(x, y);
    display.print(message);


	display.display(true);

}

void renderLineByLine(uint8_t output_row_mono_buffer[display_m_height][display_m_width], uint8_t output_row_color_buffer[display_m_height][display_m_width]) {

	// output_row_mono_buffer[height][width]
	// output_row_mono_buffer[128   ][296  ]
	
	uint8_t mother_buffer[display_m_height * display_m_width] = {};
	for (int y = 0; y < display_m_height; y++) {
		for (int x = 0; x < display_m_width; x++) {
			mother_buffer[y * display_m_width + x] = output_row_mono_buffer[y][x];
		}
	}


		// display.fillRect(0, 0, display_m_height, display_m_height, GxEPD_BLACK);
	display.drawImage(mother_buffer, 0, 0, display_width, display_height, false);
	Serial.println("Screen rendered!");
}

void renderBuffer(const unsigned char image_buffer[display_m_height * display_m_width], UpdateMode update_mode) {
	display.writeImage(image_buffer, 0, 0, display_width, display_height, false);
	if (update_mode == FullRefresh) {
		display.refresh(false);
	} else if (update_mode == LiveUpdate) {
		display.refresh(true);
	}
}


// Use with caution, returns a reference to the display class

DISPLAY_TYPE* getRawDisplay() {
	return &display;
}
