#pragma once

#include <WiFiClient.h>
#include <WiFiClientSecure.h>

#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

#include <EEPROM.h>

void configModeCallback (WiFiManager *myWiFiManager);

void saveConfigCallback();

bool wifiInit();

void setClock();

char* getApiToken();