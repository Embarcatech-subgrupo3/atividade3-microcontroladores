#include "pico/stdlib.h"
#include "hardware/pwm.h"
#define SONG_OF_STORMS_NOTES_COUNT 64
#define BUZZER_PIN 21
#define SUPER_MARIO_NOTES_COUNT 231
// Inicializa o PWM para o buzzer
void pwm_init_buzzer(uint pin);

// Toca o buzzer com uma frequência e duração específicas
void playTone(uint frequency, uint duration_ms);
void buzzer_tone(int frequency, int duration_ms);
void play_star_wars(uint pin);
void play_song_of_storms();
extern const uint song_of_storms_notes[SONG_OF_STORMS_NOTES_COUNT];
extern const uint song_of_storms_durations[SONG_OF_STORMS_NOTES_COUNT];
extern const uint super_mario_notes[SUPER_MARIO_NOTES_COUNT];
extern const uint super_mario_durations[SUPER_MARIO_NOTES_COUNT];