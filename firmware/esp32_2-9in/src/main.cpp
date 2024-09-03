#include <Arduino.h>
#include "DisplayController.h"
#include "WifiController.h"
#include <ScreenBuffer.h>
#include <UserInfo.h>
#include <soc/rtc_cntl_reg.h>
#include <ImageLoader.h>
#include <Buzzer.h>
#include <ota/OTA.h>
#include <ota/OtaUI.h>




uint8_t page_num = 0;
uint8_t max_page_num = 5;

UserInfo userInfo;
ulong lastCheckedTimestamp = 0;
uint64_t lastRenderedTimestamp = 0;


ulong lastButtonPress = 0;
bool buttonWasPressed = false;



void buttonPres() {
    if (millis() - lastButtonPress > 250) {
        lastButtonPress = millis();
        buttonWasPressed = true;
    }
}
void setup() {
    Serial.begin(115200);

    // Disable brownout detector
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // "Solution"

    // button.attach( BUTTON_INPUT, INPUT_PULLUP );
    // button.interval(5); 
    // button.setPressedState(LOW); 
    // button.update();

    pinMode(BUTTON_INPUT, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BUTTON_INPUT), buttonPres, FALLING);

    setupBuzzer(true);

    Serial.println("Initialising Display...");
    long display_startup_time = millis();
    displayInit();
    Serial.print("Display initialised in ");
    long time_taken = millis() - display_startup_time;
    Serial.print(time_taken);
    Serial.println("ms");
    // If the display "initialises" in less than 150ms, it's probably not actually initialising
    // Thus play sad tune :(
    playStartupTune(time_taken > 150);

    prompt_for_update("v0.2.1");
    Serial.println("Initialising Heap Image Loader...");

    initialiseImageLoader();

    Serial.printf("Heap available memory:     %8d bytes\n", ESP.getFreeHeap());
    Serial.println("Initialising Wifi...");

    bool buttonState = digitalRead(BUTTON_INPUT) == LOW;
    Serial.print("Button state: ");
    Serial.println(buttonState); 

    if (!wifiInit(buttonState)) {
        Serial.println("Failed to connect to WiFi");
        Serial.println("Restarting in 5s...");
        delay(5000);
        ESP.restart();
    }
    Serial.printf("Heap available memory:     %8d bytes\n", ESP.getFreeHeap());


    setClock();

    Serial.printf("Heap available memory:     %8d bytes\n", ESP.getFreeHeap());
    
    Serial.println("Checking for updates...");
    OTA_Initialise();



    Serial.println("Getting user info...");

    bool res = getUserInfo(getApiToken(), &userInfo);
    Serial.printf("Heap available memory:     %8d bytes\n", ESP.getFreeHeap());

    if (!res) {
        Serial.println("Failed to get user info");
        displayError("Failed connection, trying anyway....");
        delay(1000);
        return;
    }

    lastRenderedTimestamp = userInfo.last_message_at;
    max_page_num = userInfo.total_pages;
    downloadAllImages(&userInfo, 0, userInfo.total_pages);
    Serial.printf("Heap available memory:     %8d bytes\n", ESP.getFreeHeap());

    // Reset before starting
    buttonWasPressed = false;

    Serial.print("Waiting for updates");
}

void loop() {
    if (buttonWasPressed) {
        buttonWasPressed = false;
        playInputFeedback();

        Serial.print("\nMax_page_num:");
        Serial.println(max_page_num);
        page_num = (page_num + 1) % max_page_num;

        openImage(&userInfo, page_num);
        Serial.print("Loaded from button push");
    }

    if (millis() - lastCheckedTimestamp > 30*1000) {
        lastCheckedTimestamp = millis();


        bool res = getUserInfo(getApiToken(), &userInfo);
        if (!res) {
            Serial.println("Failed to get user info");
            return;
        }
        max_page_num = userInfo.total_pages;


        Serial.print(".");

        if (userInfo.last_message_at != lastRenderedTimestamp) {
            Serial.println();

            Serial.print("New message at: ");
            Serial.println(userInfo.last_message_at);
            Serial.print("Old message at: ");
            Serial.println(lastRenderedTimestamp);

            downloadAllImages(&userInfo, 0, userInfo.total_pages);
            
            lastRenderedTimestamp = userInfo.last_message_at;
            Serial.print("Waiting for updates");
        }
    }
}

