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

void update_progress(int currentlyReceiced, int totalBytes) {
  Serial.printf("update_progress; Data received, Progress: %.2f %%\r", 100.0 * currentlyReceiced / totalBytes);
}

void update_error(int err) {
  Serial.printf("update_error; HTTP update fatal error code %d\n", err);
  renderBuffer(IMAGE_UPDATECOMPLETE, UpdateMode::LiveUpdate);
  char error_message[32];
  snprintf(error_message, 32, "UPDATE ERR: %d", err);

  displayError(error_message);
}



uint32_t long_press = 3000;
uint32_t short_press = 1000;
uint32_t no_press = 50;

bool prompt_for_update(char* version_text) {
  
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
  
  display->setFont(&FreeMonoBold9pt7b);
	display->setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;

	display->getTextBounds(version_text, 0, 0, &tbx, &tby, &tbw, &tbh);

  uint16_t qr_code_px = 42;
  uint16_t qr_code_x = SIDEBAR_WIDTH + PAGE_PADDING + (qr_code_px / 2);

  uint16_t x = (qr_code_x - tbw/2);
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


  display->setRotation(0);
  display->drawBitmap(0,0,IMAGE_UPDATEAVAILABLE, display_width, display_height, GxEPD_WHITE, GxEPD_BLACK);

  display->display(true);
  renderBuffer(IMAGE_UPDATEAVAILABLE, UpdateMode::LiveUpdate);

  return true;


}