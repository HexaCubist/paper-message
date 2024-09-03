#pragma once
#include <Arduino.h>

static constexpr int BUZZER_OUTPUT = 16; // GPIO16 (P16)

static constexpr int TONE_BASE_FREQ = 1200;
static constexpr int TONE_HIGH_FREQ = 1600;


void setupBuzzer(bool buzzerEnable);

void playStartupTune(bool successful);
void playInputFeedback();
void playTone(int freq, int ms);
void playTone(int freq, int ms, uint32_t volume_profile);
void playUpdateAvailableTune();