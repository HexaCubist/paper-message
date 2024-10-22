#pragma once

#include <stdint.h>
#include <stdlib.h>
#include "esp32-hal-psram.h"
#include <Arduino.h>

#define display_height 296
#define display_width 128
#define display_m_height display_height
#define display_m_width display_width/8


struct ScreenBuffer {
    uint8_t output_row_mono_buffer[display_m_height][display_m_width];
    uint8_t output_row_color_buffer[display_m_height][display_m_width];
    bool defined;
};

// struct ScreenBuffer* initScreenBuffer();
void freeScreenBuffer(struct ScreenBuffer* sb);
