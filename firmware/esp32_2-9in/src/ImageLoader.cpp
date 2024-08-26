#include "ImageLoader.h"

// These images are effectively statically allocated,
// but we're out of space on the stack, so we have to use the heap so we can hold more than 10 pages 

// Images datastore
uint8_t** many_image_buffer;

void initialiseImageLoader() {
    Serial.println("Initialising Image Loader");
    Serial.printf("Heap size:     %8d bytes\n", ESP.getHeapSize());

    Serial.printf("Heap available memory:     %8d bytes\n", ESP.getFreeHeap());
    many_image_buffer = (uint8_t**)malloc(MAX_PAGES * sizeof(uint8_t*));
    for (int i = 0; i < MAX_PAGES; i++) {
        many_image_buffer[i] = (uint8_t*)malloc(display_m_height * display_m_width * sizeof(uint8_t));
    }
    Serial.printf("Heap available memory:     %8d bytes\n", ESP.getFreeHeap());
    many_image_buffer[0][0] = 69;
    Serial.printf("Test %d bytes\n", many_image_buffer[0][0]);
    
}

bool downloadAllImages(UserInfo *userInfo, uint8_t page_num, uint8_t page_count) {

    // loadBitmap(grid_mono_buffer, grid_color_buffer, page_num, getApiToken(), false, &max_page_num);
    renderBuffer(IMAGE_DOWNLOAD, UpdateMode::LiveUpdate);

    for (int i = 0; i < page_count; i++) {
        bool res = loadBitmap(many_image_buffer[i], i, getApiToken(), true);
    }



    return openImage(userInfo, page_num);
}

bool openImage(UserInfo* userInfo, uint8_t page_num) {
    renderBuffer(many_image_buffer[page_num], UpdateMode::LiveUpdate);
    Serial.printf("Heap available memory:     %8d bytes\n", ESP.getFreeHeap());

    return false;
}
