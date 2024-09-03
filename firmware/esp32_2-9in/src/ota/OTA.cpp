#include <ota/OTA.h>

GitHubOTA OsOta(FIRMWARE_VERSION_CODE, RELEASE_URL, "esp32-" FIRMWARE_VERSION_VARIANT "-firmware.bin", true);


void OTA_Initialise() {
    // Will need to mod libary to add the ability to skip, progress onscreen etc
    OsOta.handle();
}


