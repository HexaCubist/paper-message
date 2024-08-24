#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <Config.h>


struct UserInfo {
    char version[8];
    uint64_t last_message_at;
    uint8_t message_count;
    uint8_t total_pages;
    char userID[36];
};

UserInfo parseUserInfo(const char* json);

UserInfo getUserInfo(const char* api_token);