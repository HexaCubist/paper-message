#pragma once

#include <WiFiClient.h>
#include <WiFiClientSecure.h>

#define FORMAT_SPIFFS_IF_FAILED true

#include <SPIFFS.h>
#include <ArduinoJson.h>

#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

#include <EEPROM.h>
#include <DisplayController.h>
#include <images/wifi.h>


void configModeCallback (WiFiManager *myWiFiManager);

void saveConfigCallback();

bool wifiInit(bool force_config);

void setClock();

char* getApiToken();