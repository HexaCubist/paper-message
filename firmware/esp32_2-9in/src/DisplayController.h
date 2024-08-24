#pragma once

#include <Arduino.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <Config.h>
#include <FetchBMP.h>

#include <DisplayDefinitions.h>



void displayInit();

void showBitmapFrom_HTTPS(const char* host, const char* path, const char* filename, const char* fingerprint, int16_t x, int16_t y, bool with_color);

void renderScreen(uint8_t output_row_mono_buffer[display_m_height][display_m_width], uint8_t output_row_color_buffer[display_m_height][display_m_width]);