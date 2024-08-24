#include <ScreenBuffer.h>

// struct ScreenBuffer* initScreenBuffer() {
//     ScreenBuffer *sb;
//     sb->output_row_mono_buffer = (uint8_t **) malloc(display_m_height * display_m_width * sizeof(uint8_t));
//     sb->output_row_color_buffer = (uint8_t **) malloc(display_m_height * display_m_width * sizeof(uint8_t));
//     sb->defined = false;
//     return sb;
// }

void freeScreenBuffer(ScreenBuffer* sb) {
    Serial.println("Freeing screen buffer???");
    for(int i = 0; i < display_height; i++){
        free(sb->output_row_mono_buffer[i]);
        free(sb->output_row_color_buffer[i]);
    }
    free(sb->output_row_mono_buffer);
    free(sb->output_row_color_buffer);
    free(sb);
}