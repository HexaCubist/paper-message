#include <ota/OtaUI.h>

void update_started() {
  Serial.printf("update_started; HTTP update process started\n");
}

void update_finished() {
  Serial.printf("update_finished; HTTP update process finished\n");
  renderBuffer(IMAGE_UPDATECOMPLETE, UpdateMode::LiveUpdate);
  delay(1500);
  ESP.restart();

}

unsigned long last_update_progress = 0;
unsigned long last_received_bytes = 0;


void update_progress(int currentlyReceived, int totalBytes) {
  Serial.printf("update_progress; Data received, Progress: %.2f %%\r", 100.0 * currentlyReceived / totalBytes);

  DISPLAY_TYPE* display = getRawDisplay();

  display->setRotation(3);
  
  // Progress Bar

  uint16_t start_x = PAGE_PADDING + SIDEBAR_WIDTH + PAGE_PADDING*3;
  uint16_t total_length = display_height - start_x - PAGE_PADDING*3;
  uint16_t start_y = display_width - PAGE_PADDING*2 - SIDEBAR_WIDTH;
  uint16_t bar_height = SIDEBAR_WIDTH;


  uint16_t progress_length = (total_length * currentlyReceived) / totalBytes;

  Serial.printf("Progress Length: %d\n", progress_length);

  display->drawRoundRect(start_x, start_y, total_length, bar_height, SIDEBAR_ROUND, GxEPD_BLACK);
  display->fillRoundRect(start_x, start_y, progress_length, bar_height, SIDEBAR_ROUND, GxEPD_BLACK);

  float time_diff = (millis() - last_update_progress) / 1000.0;
  float byte_diff = (float)currentlyReceived - (float)last_received_bytes;

  // Draw Size Text - Right Aligned
  char size_text[32];
  snprintf(size_text, 32, "%.2f/%.2f MB", (float)currentlyReceived / 1024.0 / 1024.0, (float)totalBytes / 1024.0 / 1024.0);
  Serial.println(size_text);

  int16_t t_tbx, t_tby; uint16_t t_tbw, t_tbh;
  display->getTextBounds(size_text, 0, 0, &t_tbx, &t_tby, &t_tbw, &t_tbh);

  uint16_t size_x = start_x + total_length - t_tbw - PAGE_PADDING;
  uint16_t size_y = start_y - bar_height - PAGE_PADDING - t_tby;

  display->fillRect(size_x, size_y-t_tbh, t_tbw*2, t_tbh*1.2, GxEPD_WHITE);
  display->setCursor(size_x, size_y);
  display->print(size_text);



  if (last_update_progress > 0 && byte_diff > 0) {
    
    
    // Speed Text
    char speed_text[32];
    snprintf(speed_text, 32, "%.0f KB/s", ((byte_diff/time_diff) / 1024.0));
    Serial.println(speed_text);

    int16_t s_tbx, s_tby; uint16_t s_tbw, s_tbh;
    display->getTextBounds(speed_text, 0, 0, &s_tbx, &s_tby, &s_tbw, &s_tbh);


    uint16_t speed_x = start_x + PAGE_PADDING - s_tbx;
    uint16_t speed_y = start_y - bar_height - PAGE_PADDING - s_tby;

    display->fillRect(speed_x, speed_y-s_tbh, s_tbw*2, s_tbh*1.2, GxEPD_WHITE);
    display->setCursor(speed_x, speed_y);
    display->print(speed_text);
  }

  last_update_progress = millis();
  last_received_bytes = currentlyReceived;



  // Partial window update
  // display->displayWindow(start_x, start_y, progress_length, bar_height);
  display->display(true);

}

void update_error(int err) {
  Serial.printf("update_error; HTTP update fatal error code %d\n", err);

  char error_message[32];
  snprintf(error_message, 32, "UPDATE ERR: %d", err);

  displayError(error_message);
  delay(1500);
}



uint32_t long_press = 3000;
uint32_t short_press = 1000;
uint32_t no_press = 50;

bool prompt_for_update(const char* version_text) {
  
  Serial.println("Update available, prompting for update");
  playUpdateAvailableTune();

  DISPLAY_TYPE* display = getRawDisplay();
  // Check for null pointer
  if (display == nullptr) {
      Serial.println("Display is null");
      return false;
  }


  display->setRotation(0);
  display->drawBitmap(0,0,IMAGE_UPDATEAVAILABLE, display_width, display_height, GxEPD_WHITE, GxEPD_BLACK);
  
  // Draw text underneath QR Code
  display->setRotation(3);
  
  display->setFont(&Dogica_Pixel5pt7b);
	display->setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;

	display->getTextBounds(version_text, 0, 0, &tbx, &tby, &tbw, &tbh);

  Serial.print("tbx: ");
  Serial.println(tbx);
  Serial.print("tby: ");
  Serial.println(tby);

  Serial.print("tbw: ");
  Serial.println(tbw);
  Serial.print("tbh: ");
  Serial.println(tbh);


  uint16_t qr_code_px = 42;
  uint16_t qr_code_x = PAGE_PADDING + SIDEBAR_WIDTH + PAGE_PADDING*4 + qr_code_px/2;

  uint16_t x = (qr_code_x - tbw/2) + tbx;
	uint16_t y = display_width/2 + qr_code_px/2 + tbh + PAGE_PADDING;

	display->setCursor(x, y);
  display->print(version_text);
  display->display(true);



  // Wait for button press and unpress
  while (digitalRead(BUTTON_INPUT) == HIGH) {
    delay(1);
    yield();
  }

  // Simple debounce
  unsigned long press_start = millis();
  playInputFeedback();
  
  while ((digitalRead(BUTTON_INPUT) == LOW && millis() - press_start < long_press) || millis() - press_start < no_press) {
    delay(1);
    yield();
  }

  unsigned long time_pressed = millis() - press_start;
  if (time_pressed < short_press) {
    Serial.println("Skipping update");
    return false;
  }
  Serial.println("Starting update...");
  playInputFeedback();

  

  display->setRotation(0);
  display->drawBitmap(0,0,IMAGE_UPDATEDOWNLOADING, display_width, display_height, GxEPD_WHITE, GxEPD_BLACK);

  display->display(true);

  return true;


}