#include <Arduino.h>
#include "DisplayController.h"
#include "WifiController.h"



const uint8_t page_num = 0;

void setup() {
    Serial.begin(115200);

    Serial.println("Initialising Display...");

    displayInit();

    Serial.println("Initialising Wifi...");


    if (!wifiInit()) {
        Serial.println("Failed to connect to WiFi");
        Serial.println("Restarting in 5s...");
        delay(5000);
        ESP.restart();
    }

    setClock();

    // showBitmapFrom_HTTPS(rsb_host, full_path, strPageNum, fp_rawcontent,0,0, false);
    ScreenBuffer screenBuffer = loadBitmap(page_num, getApiToken(), false);
    // if (screenBuffer.defined) {
    //     renderScreen(screenBuffer);
    // } else {
    //     Serial.println("Failed to load bitmap");
    // }

}

void loop() {
    
}