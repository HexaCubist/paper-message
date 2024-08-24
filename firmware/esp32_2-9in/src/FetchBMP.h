#pragma once

#include <Arduino.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <Config.h>

uint16_t read16(WiFiClient& client);
uint32_t read32(WiFiClient& client);
uint32_t skip(WiFiClient& client, int32_t bytes);
uint32_t read8n(WiFiClient& client, uint8_t* buffer, int32_t bytes);

struct ScreenBuffer {
    uint8_t output_row_mono_buffer[display_height][display_width];
    uint8_t output_row_color_buffer[display_height][display_width];
    bool defined;


    ScreenBuffer() {
        memset(output_row_mono_buffer, 0, sizeof(output_row_mono_buffer));
        memset(output_row_color_buffer, 0, sizeof(output_row_color_buffer));
        defined = false;
    }

};

ScreenBuffer loadBitmap(uint8_t page_num, char* api_token, bool with_color);