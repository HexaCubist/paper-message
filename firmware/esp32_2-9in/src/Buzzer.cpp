#include <Buzzer.h>


#define SOUND_PWM_CHANNEL   0
#define SOUND_RESOLUTION    8 // 8 bit resolution
#define SOUND_ON            (1<<(SOUND_RESOLUTION-1)) // 50% duty cycle
#define SOUND_ON_QUIET            (1<<(SOUND_RESOLUTION-5)) // Low duty cycle
#define SOUND_OFF           0                         // 0% duty cycle




bool buzzer_enabled = false;

void setupBuzzer(bool buzzerEnable) {
    buzzer_enabled = buzzerEnable;
    if (!buzzer_enabled) {return;}

    pinMode(BUZZER_OUTPUT, OUTPUT);


    // // Passive buzzer, so pwm output
    ledcSetup(SOUND_PWM_CHANNEL, TONE_BASE_FREQ, SOUND_RESOLUTION);  // Set up PWM channel
    ledcAttachPin(BUZZER_OUTPUT, SOUND_PWM_CHANNEL);                      // Attach channel to pin
    ledcWrite(SOUND_PWM_CHANNEL, SOUND_OFF);

}

void playStartupTune(bool successful) {
    if (successful) {
        playTone(TONE_BASE_FREQ, 100);
        delay(100);
        playTone(TONE_HIGH_FREQ, 100);
    } else {
        // Error code should always be audible

        playTone(TONE_HIGH_FREQ, 100, SOUND_ON);
        delay(100);
        playTone(TONE_BASE_FREQ, 100, SOUND_ON);
        delay(100);
        playTone(TONE_BASE_FREQ, 200, SOUND_ON);

    }

}
void playInputFeedback() {
    playTone(TONE_BASE_FREQ, 50);
}

void playTone(int freq, int ms) {
    playTone(freq, ms, SOUND_ON_QUIET);
}

void playTone(int freq, int ms, uint32_t volume_profile) {
    if (!buzzer_enabled) {return;}

    ledcChangeFrequency(SOUND_PWM_CHANNEL, freq, SOUND_RESOLUTION);
    ledcWrite(SOUND_PWM_CHANNEL, volume_profile);
    delay(50);
    ledcWrite(SOUND_PWM_CHANNEL, SOUND_OFF);
}

void playUpdateAvailableTune() {
    playTone(TONE_BASE_FREQ, 100, SOUND_ON);
    delay(100);
    playTone(TONE_HIGH_FREQ, 100, SOUND_ON);
    delay(100);
    playTone(TONE_HIGH_FREQ, 200, SOUND_ON);
}