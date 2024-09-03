#pragma once

#include <Arduino.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <Config.h>
#include <FetchBMP.h>
#include <images/boot.h>
#include <images/fail.h>

#include <DisplayDefinitions.h>
#include <Fonts/FreeMonoBold9pt7b.h>


#define SIDEBAR_WIDTH 25
#define SIDEBAR_ROUND 2
#define PAGE_PADDING 2


enum UpdateMode {
    FullRefresh,
    LiveUpdate,
    NoUpdate
};

void displayInit();


void renderLineByLine(uint8_t output_row_mono_buffer[display_m_height][display_m_width], uint8_t output_row_color_buffer[display_m_height][display_m_width]);

void renderBuffer(const unsigned char image_buffer[display_m_height * display_m_width], UpdateMode update_mode);

void displayError(char* message);

DISPLAY_TYPE* getRawDisplay();