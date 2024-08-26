#include <Arduino.h>
#include "DisplayController.h"
#include "WifiController.h"
#include <ScreenBuffer.h>
#include <UserInfo.h>
#include <soc/rtc_cntl_reg.h>
#include <ImageLoader.h>
#include <Buzzer.h>


static constexpr int BUTTON_INPUT = 4; // GPIO4 (P4)
// Bounce2::Button button = Bounce2::Button();




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
    playStartupTune();

    Serial.println("Initialising Display...");

    displayInit();

    Serial.println("Initialising PSRAM Image Loader...");

    initialiseImageLoader();

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

    setClock();

    Serial.println("Time to test: ");

    Serial.println("Time to test: ");
    Serial.println(display_m_height * display_m_width * sizeof(uint8_t));

    Serial.println(ESP.getFreeHeap());
    Serial.println(ESP.getHeapSize());
    Serial.println(ESP.getMinFreeHeap());


    bool res = getUserInfo(getApiToken(), &userInfo);
    if (!res) {
        Serial.println("Failed to get user info");
        displayError("Failed connection, trying anyway....");
        delay(1000);
        return;
    }

    lastRenderedTimestamp = userInfo.last_message_at;
    max_page_num = userInfo.total_pages;
    downloadAllImages(&userInfo, 0, userInfo.total_pages);

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
        bool res = getUserInfo(getApiToken(), &userInfo);
        if (!res) {
            return;
        }
        max_page_num = userInfo.total_pages;

        lastCheckedTimestamp = millis();

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

