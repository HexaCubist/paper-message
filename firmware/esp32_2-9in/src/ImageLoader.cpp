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
    Serial.println("Creating client..");

    // loadBitmap(grid_mono_buffer, grid_color_buffer, page_num, getApiToken(), false, &max_page_num);
    
    // FANCY LOADING BAR TRICK
    // Show image without left bar, store the full image in buffer, and slowly reveal the left bar
    Serial.println("Loading bar trick");


    DISPLAY_TYPE* display = getRawDisplay();

    // Check for null pointer
    if (display == nullptr) {
        Serial.println("Display is null");
        return false;
    }

    display->setRotation(0);
    display->drawBitmap(0,0,IMAGE_DOWNLOAD, display_width, display_height, GxEPD_WHITE, GxEPD_BLACK);
    display->setRotation(3);

    display->fillRect(0, 0, SIDEBAR_WIDTH, display_width, GxEPD_WHITE);
    

    Serial.println("Loading bar trick ready!");

    WiFiClientSecure wifi_client;

    if (!configureClient(wifi_client)) {
        Serial.println("Failed to configure client");
        displayError("SSL CONNECTION FAILED");
        return false;
    }


    int pixels_covered = 0;
    for (int i = 0; i < page_count && i < MAX_PAGES; i++) {
        int progress_bar_length = ((i+1) * (display_width)) / (page_count+1);
        int new_region = progress_bar_length - pixels_covered;
        Serial.printf("Progress bar length: %d\n", progress_bar_length);
        Serial.printf("New region: %d\n", new_region);
        Serial.printf("X: %d, Y: %d, W: %d, H: %d\n", display_width-progress_bar_length, display_height-SIDEBAR_WIDTH, new_region, SIDEBAR_WIDTH);
        
        // Progressive redraw sidebar
        display->fillRoundRect(0, 0, SIDEBAR_WIDTH, (progress_bar_length), SIDEBAR_ROUND, GxEPD_BLACK);
        
        // First round, we need to draw the bitmap in full
        if (i == 0) {
            display->display(true);
        } else {
            // But after, we only need to update the sidebar
            display->displayWindow(0,0, SIDEBAR_WIDTH, display_height);
        }

        if (!wifi_client.connected()) {
            Serial.println("Connection lost, reconnecting..");

            if (!configureClient(wifi_client)) {
                Serial.println("Failed to configure client");
                displayError("SSL CONNECTION LOST");
                return false;
            }

        } else {
            Serial.println("Reusing SSL connection..");

        }


        bool res = loadBitmap(wifi_client, many_image_buffer[i], i, getApiToken(), true);
        if (!res) {
            Serial.println("Failed to download image");
            displayError("MESSAGE DOWNLOAD FAILED");
            delay(1000);
        }


        pixels_covered = progress_bar_length;
    }
    renderBuffer(IMAGE_DOWNLOAD, UpdateMode::LiveUpdate);

    wifi_client.stop();


    return openImage(userInfo, page_num);
}

bool openImage(UserInfo* userInfo, uint8_t page_num) {
    renderBuffer(many_image_buffer[page_num], UpdateMode::LiveUpdate);
    Serial.printf("Heap available memory:     %8d bytes\n", ESP.getFreeHeap());

    return false;
}
