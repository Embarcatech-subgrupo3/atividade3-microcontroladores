#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define BUZZER_PIN 21

// Inicializa o PWM para o buzzer
void pwm_init_buzzer(uint pin);

// Toca o buzzer com uma frequência e duração específicas
void playTone(uint frequency, uint duration_ms);
// void buzzer_tone(int frequency, int duration_ms);
void play_star_wars(uint pin);