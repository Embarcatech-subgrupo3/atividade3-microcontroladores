#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define BUZZER 21

// Função para inicializar o buzzer
void ativar_buzzer(){
    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);
    gpio_put(BUZZER, 0); // Inicialmente desligado
}

// Gera um tom no buzzer
void buzzer(int frequencia, int duracao_ms) {
    int delay_us = 1000000 / (frequencia * 2); // Tempo de meio ciclo
    int cycles = (frequencia * duracao_ms) / 1000; // Número de ciclos

    for (int i = 0; i < cycles; i++) {
        gpio_put(BUZZER, 1);
        sleep_us(delay_us);
        gpio_put(BUZZER, 0);
        sleep_us(delay_us);
    }
}

// Função para tocar uma melodia crescente
void tocar_melodia() {
    // Notas que crescem em frequência e duração
    int frequencia_inicial = 200;  // Frequência inicial em Hz
    int duracao_inicial = 200;     // Duração inicial em ms

    for (int i = 0; i < 20; i++) {
        int frequencia_atual = frequencia_inicial + (80 * i);
        int duracao_atual = duracao_inicial + (80 * i);
        buzzer(frequencia_atual, duracao_atual);        
        sleep_ms(100); // Pausa curta entre as notas
    }

} // Fim da função de toque do buzzer

int main() {

    stdio_init_all();
    ativar_buzzer(); // Inicializar o buzzer

    while (true) {
        tocar_melodia();
        sleep_ms(1000);
    }

    return 0;
}
