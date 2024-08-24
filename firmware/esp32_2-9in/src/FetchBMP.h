#pragma once

#include <Arduino.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>

uint16_t read16(WiFiClient& client);
uint32_t read32(WiFiClient& client);
uint32_t skip(WiFiClient& client, int32_t bytes);
uint32_t read8n(WiFiClient& client, uint8_t* buffer, int32_t bytes);