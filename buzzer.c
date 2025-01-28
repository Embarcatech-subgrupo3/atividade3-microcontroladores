#include "buzzer.h"
#include "hardware/clocks.h"

void initBuzzer(uint pin) {
    // Configura o pino como saída de PWM
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);

    // Configura o PWM com divisor genérico
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.0f); // Divisor genérico
    pwm_init(slice_num, &config, true);

    pwm_set_gpio_level(pin, 0); // Duty cycle inicial em 0
}

void playTone(uint frequency, uint duration_ms) {
    // Configura o PWM para gerar a frequência desejada
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);
    uint clock_div = clock_get_hz(clk_sys) / (frequency * 4096); // Calcula divisor

    pwm_set_wrap(slice_num, 4095); // Define o ciclo completo
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 2048); // Duty cycle de 50%
    pwm_set_enabled(slice_num, true); // Habilita o PWM

    sleep_ms(duration_ms); // Duração do som

    pwm_set_enabled(slice_num, false); // Desativa o PWM
    pwm_set_gpio_level(BUZZER_PIN, 0); // Garante que o pino está em 0
}

void buzzer_tone(int frequency, int duration_ms) {
    // Gera som com toggling direto no GPIO
    int delay_us = 1000000 / (frequency * 2); // Meio ciclo
    int cycles = (frequency * duration_ms) / 1000; // Total de ciclos

    gpio_init(BUZZER_PIN); // Inicializa o pino
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);

    for (int i = 0; i < cycles; i++) {
        gpio_put(BUZZER_PIN, 1);
        sleep_us(delay_us);
        gpio_put(BUZZER_PIN, 0);
        sleep_us(delay_us);
    }
}
