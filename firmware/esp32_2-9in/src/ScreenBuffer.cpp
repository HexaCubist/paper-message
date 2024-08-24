#include <ScreenBuffer.h>

struct ScreenBuffer* initScreenBuffer() {
    struct ScreenBuffer* sb = (ScreenBuffer*)malloc(sizeof *sb);
    sb->output_row_mono_buffer = (uint8_t**)malloc(display_height * sizeof(uint8_t*));
    sb->output_row_color_buffer = (uint8_t**)malloc(display_height * sizeof(uint8_t*));
    for(int i = 0; i < display_height; i++){
        sb->output_row_mono_buffer[i] = (uint8_t*)malloc(display_width * sizeof(uint8_t));
        sb->output_row_color_buffer[i] = (uint8_t*)malloc(display_width * sizeof(uint8_t));
    }
    sb->defined = false;
    return sb;
}

void freeScreenBuffer(struct ScreenBuffer* sb) {
    for(int i = 0; i < display_height; i++){
        free(sb->output_row_mono_buffer[i]);
        free(sb->output_row_color_buffer[i]);
    }
    free(sb->output_row_mono_buffer);
    free(sb->output_row_color_buffer);
    free(sb);
}