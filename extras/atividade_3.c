#include <stdio.h>
#include "pico/stdlib.h"

// Definindo o teclado matricial
#define LINHAS 4
#define COLUNAS 4

int linhas[4] = {16, 17, 18, 19}; // Pinos das linhas
int colunas[4] = {20, 8, 9, 28};   // Pinos das colunas

// Teclas do teclado matricial correspondentes
const char teclado[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Configurações da matriz de LEDs
#define MATRIZ_LEDS 7
#define Nleds 25 // Número de LEDs
#define NEW_PISKEL_FRAME_COUNT 28
#define NEW_PISKEL_FRAME_WIDTH 5
#define NEW_PISKEL_FRAME_HEIGHT 5


// Inicializando o teclado matricial
void inicializar_teclado() {	for(int a=0; a< LINHAS;a++)
	{	
		gpio_init(linhas[a]);
		gpio_set_dir(linhas[a], GPIO_OUT);
    }
       
    for(int b=0; b < COLUNAS; b++)
    {
       	gpio_init(colunas[b]);
       	gpio_set_dir(colunas[b], GPIO_IN);
       	gpio_pull_up(colunas[b]);
    }
}

// Estrutura que define a cor dos LEDs (RGB)
struct pixel_t {
    uint8_t G, R, B;
};
typedef struct pixel_t npLED_t;
npLED_t leds[Nleds];

// Função para definir a cor dos LEDs
void cor(const uint index, const uint8_t r, const uint8_t g, const uint8_t b) {
    leds[index].R = r;
    leds[index].G = g;
    leds[index].B = b;
}

// Função para desligar os LEDs
void desliga() {
    for (uint i = 0; i < Nleds; ++i) {
        cor(i, 0, 0, 0); // Define todos os LEDs como apagados
    }
}

// Função para enviar os dados do buffer para os LEDs
void buffer() {
    for (uint i = 0; i < Nleds; ++i) {
        pio_sm_put_blocking(np_pio, sm, leds[i].G); // verde
        pio_sm_put_blocking(np_pio, sm, leds[i].R); // vermelho
        pio_sm_put_blocking(np_pio, sm, leds[i].B); // azul
    }
    sleep_us(100);
}

// Função que lê a tecla pressionada
char ler_tecla() {
    for (int i = 0; i < LINHAS; i++) {
        gpio_put(linhas[i], 0); // Ativa a linha atual


        for(int col = 0; col < COLUNAS; col++) {
            if (gpio_get(colunas[col]) == 0) { // Detecta se a coluna está ativa
                sleep_ms(50);
                gpio_put(linhas[i], 1); 
                return teclado[i][col]; // Retorna a tecla pressionada
            }
        }
        gpio_put(linhas[i], 1); // Desativa a linha atual
    }
    return 0; // Nenhuma tecla pressionada
}