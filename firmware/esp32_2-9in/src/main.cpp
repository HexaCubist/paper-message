#include <Arduino.h>
#include "DisplayController.h"
#include "WifiController.h"

const char* rsb_host = "rsb.nz";
const char* path = "/api/";
const char* pagesEndpoint = "/pages/";
const char* fp_rawcontent = "EF:A9:7B:6E:EB:B2:31:B9:9B:2E:13:16:D8:A6:D8:42:4F:83:57:7E";  // SHA-1 as of 24 Aug 2024


const uint8_t page_num = 0;

void setup() {
    Serial.begin(115200);

    displayInit();

    if (!wifiInit()) {
        Serial.println("Failed to connect to WiFi");
        Serial.println("Restarting in 5s...");
        delay(5000);
        ESP.restart();
    }

    setClock();

    // path + user_token + pagesEndpoint
    char full_path [64];
    strcpy(full_path,path);
    strcat(full_path,getApiToken());
    strcat(full_path,pagesEndpoint);

    char strPageNum [10];
    itoa(page_num,strPageNum,10);

    showBitmapFrom_HTTPS(rsb_host, full_path, strPageNum, fp_rawcontent,0,0, false);

}

void loop() {
    
}