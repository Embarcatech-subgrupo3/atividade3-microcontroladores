#include "buzzer.h"
#include "hardware/clocks.h"

const uint song_of_storms_notes[SONG_OF_STORMS_NOTES_COUNT] = {
    294, 440, 440, 0, 330, 494, 349, 523, 523, 0, 330, 494, 294, 440, 440, 0, 
    330, 494, 349, 523, 523, 0, 330, 494, 294, 349, 587, 294, 349, 587, 659, 
    698, 659, 659, 659, 523, 440, 440, 294, 349, 392, 440, 440, 294, 349, 392,
    330, 349, 587, 294, 349, 587, 659, 698, 659, 659, 659, 523, 440, 440, 294, 
    349, 392, 440, 440
};

const uint song_of_storms_durations[SONG_OF_STORMS_NOTES_COUNT] = {
    250, 250, 250, 500, 125, 500, 250, 250, 250, 500, 125, 500, 250, 250, 250, 500, 
    125, 500, 250, 250, 250, 500, 125, 500, 125, 125, 500, 125, 125, 500, 500, 
    125, 125, 125, 125, 500, 250, 250, 250, 125, 125, 500, 500, 250, 125, 125,
    500, 125, 125, 500, 500, 125, 125, 125, 125, 500, 250, 250, 250, 125, 125, 
    500, 500, 500
};


void pwm_init_buzzer(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.0f); // Ajusta divisor de clock
    pwm_init(slice_num, &config, true);
    pwm_set_gpio_level(pin, 0); // Desliga o PWM inicialmente
}

// Toca uma nota com a frequência e duração especificadas
void play_tone(uint pin, uint frequency, uint duration_ms) {
    uint slice_num = pwm_gpio_to_slice_num(pin);
    uint32_t clock_freq = clock_get_hz(clk_sys);
    uint32_t top = clock_freq / frequency - 1;

    pwm_set_wrap(slice_num, top);
    pwm_set_gpio_level(pin, top / 2); // 50% de duty cycle

    sleep_ms(duration_ms);

    pwm_set_gpio_level(pin, 0); // Desliga o som após a duração
    sleep_ms(50); // Pausa entre notas
}

void buzzer_tone(int frequency, int duration_ms) {
    if (frequency == 0) {
        sleep_ms(duration_ms);  // Se for um "REST" (pausa), apenas aguarde
        return;
    }

    int delay_us = 1000000 / (frequency * 2); // Meio ciclo
    int cycles = (frequency * duration_ms) / 1000; // Total de ciclos

    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);

    for (int i = 0; i < cycles; i++) {
        gpio_put(BUZZER_PIN, 1);
        sleep_us(delay_us);
        gpio_put(BUZZER_PIN, 0);
        sleep_us(delay_us);
    }
}
const uint star_wars_notes[] = {
    330, 330, 330, 262, 392, 523, 330, 262,
    392, 523, 330, 659, 659, 659, 698, 523,
    415, 349, 330, 262, 392, 523, 330, 262,
    392, 523, 330, 659, 659, 659, 698, 523,
    415, 349, 330, 523, 494, 440, 392, 330,
    659, 784, 659, 523, 494, 440, 392, 330,
    659, 659, 330, 784, 880, 698, 784, 659,
    523, 494, 440, 392, 659, 784, 659, 523,
    494, 440, 392, 330, 659, 523, 659, 262,
    330, 294, 247, 262, 220, 262, 330, 262,
    330, 294, 247, 262, 330, 392, 523, 440,
    349, 330, 659, 784, 659, 523, 494, 440,
    392, 659, 784, 659, 523, 494, 440, 392
};

// Duração das notas em milissegundos
const uint note_duration[] = {
    500, 500, 500, 350, 150, 300, 500, 350,
    150, 300, 500, 500, 500, 500, 350, 150,
    300, 500, 500, 350, 150, 300, 500, 350,
    150, 300, 650, 500, 150, 300, 500, 350,
    150, 300, 500, 150, 300, 500, 350, 150,
    300, 650, 500, 350, 150, 300, 500, 350,
    150, 300, 500, 500, 500, 500, 350, 150,
    300, 500, 500, 350, 150, 300, 500, 350,
    150, 300, 500, 350, 150, 300, 500, 500,
    350, 150, 300, 500, 500, 350, 150, 300,
};

void play_star_wars(uint pin) {
    for (int i = 0; i < sizeof(star_wars_notes) / sizeof(star_wars_notes[0]); i++) {
        if (star_wars_notes[i] == 0) {
            sleep_ms(note_duration[i]);
        } else {
            play_tone(pin, star_wars_notes[i], note_duration[i]);
        }
    }
}

// void play_song_of_storms(uint pin) {
//     for (int i = 0; i < sizeof(song_of_storms_notes) / sizeof(song_of_storms_notes[0]); i++) {
//         if (song_of_storms_notes[i] == 0) {
//             sleep_ms(song_of_storms_durations[i]); // Pausa entre notas
//         } else {
//             play_tone(pin, song_of_storms_notes[i], song_of_storms_durations[i]);
//         }
//     }
// }

void play_song_of_storms() {
    for (int i = 0; i < sizeof(song_of_storms_notes) / sizeof(song_of_storms_notes[0]); i++) {
        buzzer_tone(song_of_storms_notes[i], song_of_storms_durations[i]);
    }
}