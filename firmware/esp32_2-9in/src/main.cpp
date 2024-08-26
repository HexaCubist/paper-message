#include <Arduino.h>
#include "DisplayController.h"
#include "WifiController.h"
#include <ScreenBuffer.h>
#include "Bounce2.h"
#include <UserInfo.h>
#include <soc/rtc_cntl_reg.h>
#include <ImageLoader.h>


static constexpr int BUTTON_INPUT = 4; // GPIO4 (P4)
Bounce2::Button button = Bounce2::Button();


static constexpr int BUZZER_OUTPUT = 16; // GPIO16 (P16)


uint8_t page_num = 0;
uint8_t max_page_num = 5;

UserInfo userInfo;
ulong lastCheckedTimestamp = 0;
uint64_t lastRenderedTimestamp = 0;


void doubleClick() {
  Serial.println("x2");
}


#define SOUND_PWM_CHANNEL   0
#define SOUND_RESOLUTION    8 // 8 bit resolution
#define SOUND_ON            (1<<(SOUND_RESOLUTION-1)) // 50% duty cycle
#define SOUND_OFF           0                         // 0% duty cycle

void setup() {
    Serial.begin(115200);

    // Disable brownout detector
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // "Solution"

    button.attach( BUTTON_INPUT, INPUT_PULLUP );
    button.interval(5); 
    button.setPressedState(LOW); 
    button.update();

    // pinMode(BUZZER_OUTPUT, OUTPUT);
    // // Passive buzzer, so pwm output
    // ledcSetup(SOUND_PWM_CHANNEL, 1000, SOUND_RESOLUTION);  // Set up PWM channel
    // ledcAttachPin(BUZZER_OUTPUT, SOUND_PWM_CHANNEL);                      // Attach channel to pin
    // ledcWrite(SOUND_PWM_CHANNEL, SOUND_ON);
    // delay(1000);
    // ledcWrite(SOUND_PWM_CHANNEL, SOUND_OFF);    delay(1000);

    Serial.println("Initialising Display...");

    displayInit();

    Serial.println("Initialising PSRAM Image Loader...");

    initialiseImageLoader();

    Serial.println("Initialising Wifi...");

    bool buttonState = button.isPressed();
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

    Serial.print("Waiting for updates");
}

void loop() {
    button.update();
    if (button.pressed()) {
        Serial.print("\nMax_page_num:");
        Serial.println(max_page_num);
        page_num = (page_num + 1) % max_page_num;

        openImage(&userInfo, page_num);
        Serial.print("Loaded from button push");
    }

    if (millis() - lastCheckedTimestamp > 1500) {
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

