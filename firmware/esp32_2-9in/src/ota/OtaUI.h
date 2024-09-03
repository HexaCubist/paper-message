#pragma once

#include <Arduino.h>
#include <DisplayController.h>
#include <images/updateavailable.h>
#include <images/updatedownloading.h>
#include <images/updatecomplete.h>


#include <Config.h>
#include <Buzzer.h>

void update_started();
void update_finished();
void update_progress(int currentlyReceiced, int totalBytes);
void update_error(int err);

bool prompt_for_update(char* version_text);
