#include <Buzzer.h>


#define SOUND_PWM_CHANNEL   0
#define SOUND_RESOLUTION    8 // 8 bit resolution
#define SOUND_ON            (1<<(SOUND_RESOLUTION-1)) // 50% duty cycle
#define SOUND_ON_QUIET            (1<<(SOUND_RESOLUTION-6)) // 50% duty cycle
#define SOUND_OFF           0                         // 0% duty cycle


static constexpr int BUZZER_OUTPUT = 16; // GPIO16 (P16)

static constexpr int TONE_BASE_FREQ = 1200;
static constexpr int TONE_HIGH_FREQ = 1600;


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

void playStartupTune() {
    if (!buzzer_enabled) {return;}


    ledcChangeFrequency(SOUND_PWM_CHANNEL, TONE_BASE_FREQ, SOUND_RESOLUTION);
    ledcWrite(SOUND_PWM_CHANNEL, SOUND_ON_QUIET);
    delay(100);
    ledcWrite(SOUND_PWM_CHANNEL, SOUND_OFF);
    delay(100);
    ledcChangeFrequency(SOUND_PWM_CHANNEL, TONE_HIGH_FREQ, SOUND_RESOLUTION);
    ledcWrite(SOUND_PWM_CHANNEL, SOUND_ON_QUIET);
    delay(100);
    ledcWrite(SOUND_PWM_CHANNEL, SOUND_OFF);

}
void playInputFeedback() {
    if (!buzzer_enabled) {return;}

    ledcChangeFrequency(SOUND_PWM_CHANNEL, TONE_BASE_FREQ, SOUND_RESOLUTION);
    ledcWrite(SOUND_PWM_CHANNEL, SOUND_ON);
    delay(50);
    ledcWrite(SOUND_PWM_CHANNEL, SOUND_OFF);

}
