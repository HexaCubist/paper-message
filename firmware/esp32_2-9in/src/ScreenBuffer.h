#pragma once

#include <stdint.h>
#include <stdlib.h>

#define display_height 128
#define display_width 296

struct ScreenBuffer {
    uint8_t **output_row_mono_buffer;
    uint8_t **output_row_color_buffer;
    bool defined;
};

struct ScreenBuffer* initScreenBuffer();
void freeScreenBuffer(struct ScreenBuffer* sb);
