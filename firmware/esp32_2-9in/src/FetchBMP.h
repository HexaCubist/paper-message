#pragma once

#include <Arduino.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <Config.h>
#include <ScreenBuffer.h>

uint16_t read16(WiFiClient& client);
uint32_t read32(WiFiClient& client);
uint32_t skip(WiFiClient& client, int32_t bytes);
uint32_t read8n(WiFiClient& client, uint8_t* buffer, int32_t bytes);

// struct ScreenBuffer {
//     uint8_t **output_row_mono_buffer;
//     uint8_t **output_row_color_buffer;
//     bool defined;
// };

// struct ScreenBuffer* initScreenBuffer();
// void freeScreenBuffer(struct ScreenBuffer* sb);
    // ScreenBuffer() {
        // memset(output_row_mono_buffer, 0, sizeof(uint8_t) * display_height * display_width);
        // memset(output_row_color_buffer, 0, sizeof(uint8_t) * display_height * display_width);
        // for (int i = 0;  i<10; i++) {
        //     for (int j = 0; j < 10; j++) {
        //         output_row_mono_buffer[i][j] = 0;
        //         output_row_color_buffer[i][j] = 0;
        //     }
        // }
        // defined = false;
    // }


bool loadBitmap(ScreenBuffer *screenBuffer, uint8_t page_num, char* api_token, bool with_color);