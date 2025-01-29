#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2818b.pio.h" 

#define LED_COUNT 25
#define LED_PIN 7

// Estrutura para armazenar as cores de um LED no formato GRB
typedef struct {
    uint8_t G, R, B;
} npLED_t;

// Buffer para armazenar o estado de todos os LEDs
npLED_t leds[LED_COUNT];

// Variáveis para controle da máquina de estado PIO
PIO np_pio; 
uint sm;   

// Função para inicializar a matriz de LEDs
void npInit(uint pin) {
    uint offset = pio_add_program(pio0, &ws2818b_program); // Adiciona o programa PIO
    np_pio = pio0; // Usa o PIO0
    sm = pio_claim_unused_sm(np_pio, true); 
    ws2818b_program_init(np_pio, sm, offset, pin, 800000.f); // Inicializa o programa PIO
    memset(leds, 0, sizeof(leds)); // Inicializa todos os LEDs como apagados
}

// Função para definir a cor de um LED específico
void npSetLED(uint index, uint8_t r, uint8_t g, uint8_t b) {
    if (index < LED_COUNT) { // Verifica se o índice é válido
        leds[index].R = r;
        leds[index].G = g;
        leds[index].B = b;
    }
}

// Função para apagar todos os LEDs
void npClear() {
    memset(leds, 0, sizeof(leds)); 
    npWrite(); // Envia os dados para os LEDs
}

// Função para enviar os dados de cor para os LEDs
void npWrite() {
    for (uint i = 0; i < LED_COUNT; ++i) {
        pio_sm_put_blocking(np_pio, sm, leds[i].G); // Envia o valor de verde
        pio_sm_put_blocking(np_pio, sm, leds[i].R); // Envia o valor de vermelho
        pio_sm_put_blocking(np_pio, sm, leds[i].B); // Envia o valor de azul
    }
    sleep_us(100); 
}

// Definição dos pinos do teclado matricial
const uint8_t ROWS[] = {18, 19, 20, 4}; // Pinos das linhas
const uint8_t COLS[] = {16, 17, 9, 8};  // Pinos das colunas

// Mapeamento das teclas do teclado 4x4
char keys[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Função para ler a tecla pressionada no teclado matricial
char getKey() {
    for (int row = 0; row < 4; row++) {
        gpio_put(ROWS[row], 0); 
        for (int col = 0; col < 4; col++) {
            if (!gpio_get(COLS[col])) { 
                while (!gpio_get(COLS[col])) {} 
                gpio_put(ROWS[row], 1); 
                return keys[row][col]; 
            }
        }
        gpio_put(ROWS[row], 1); 
    }
    return 0; 
}

// Função para configurar os pinos do teclado matricial
void setupMatrixKeyboard() {
    for (int i = 0; i < 4; i++) {
        gpio_init(ROWS[i]); 
        gpio_set_dir(ROWS[i], GPIO_OUT);
        gpio_put(ROWS[i], 1);

        gpio_init(COLS[i]);
        gpio_set_dir(COLS[i], GPIO_IN);
        gpio_pull_up(COLS[i]);
    }
}

int main() {
    stdio_init_all();
    setupMatrixKeyboard();
    npInit(LED_PIN);

    while (true) {
        char key = getKey();
        if (key == '#') {
            npClear();
            for (uint i = 0; i < LED_COUNT; ++i) {
                npSetLED(i, 51, 51, 51); // Ligar todos os LEDs na cor branca com 20% de intensidade
            }
            npWrite();
        }
        sleep_ms(100);
    }

    return 0;
}