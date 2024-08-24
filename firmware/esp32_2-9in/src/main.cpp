#include <Arduino.h>
#include "DisplayController.h"
#include "WifiController.h"
#include <ScreenBuffer.h>
#include "OneButton.h"


static constexpr int BUTTON_INPUT = 4; // GPIO4 (P4)

OneButton main_button;

static constexpr int BUZZER_OUTPUT = 16; // GPIO16 (P16)

uint8_t grid_mono_buffer[display_m_height][display_m_width] = {{0}};
uint8_t grid_color_buffer[display_m_height][display_m_width] = {{0}};

const uint8_t page_num = 0;

void doubleClick() {
  Serial.println("x2");
}

#define SOUND_PWM_CHANNEL   0
#define SOUND_RESOLUTION    8 // 8 bit resolution
#define SOUND_ON            (1<<(SOUND_RESOLUTION-1)) // 50% duty cycle
#define SOUND_OFF           0                         // 0% duty cycle

void setup() {
    Serial.begin(115200);

    main_button.setup(BUTTON_INPUT, INPUT_PULLUP, true);
    main_button.attachDoubleClick(doubleClick);
    main_button.tick();


    // pinMode(BUZZER_OUTPUT, OUTPUT);
    // // Passive buzzer, so pwm output
    // ledcSetup(SOUND_PWM_CHANNEL, 1000, SOUND_RESOLUTION);  // Set up PWM channel
    // ledcAttachPin(BUZZER_OUTPUT, SOUND_PWM_CHANNEL);                      // Attach channel to pin
    // ledcWrite(SOUND_PWM_CHANNEL, SOUND_ON);
    // delay(1000);
    // ledcWrite(SOUND_PWM_CHANNEL, SOUND_OFF);    delay(1000);

    Serial.println("Initialising Display...");

    displayInit();

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








    // showBitmapFrom_HTTPS(rsb_host, full_path, strPageNum, fp_rawcontent,0,0, false);
    bool res = loadBitmap(grid_mono_buffer, grid_color_buffer, page_num, getApiToken(), false);
    if (res) {
        renderScreen(grid_mono_buffer, grid_color_buffer);
    } else {
        Serial.println("Failed to load bitmap");
    }
}

void loop() {
    main_button.tick();
    delay(10);
}

