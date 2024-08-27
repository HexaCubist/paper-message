#pragma once
#include <Arduino.h>

void setupBuzzer(bool buzzerEnable);

void playStartupTune(bool successful);
void playInputFeedback();
void playTone(int freq, int ms);