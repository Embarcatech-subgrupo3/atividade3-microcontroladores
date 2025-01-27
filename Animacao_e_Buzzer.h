/* Animação de varredura dos LEDs */
    
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2818b.pio.h"
#include "hardware/timer.h"

// Definição do número total de LEDs e do pino onde a matriz está conectada
#define Nleds 25
#define MATRIZ_LEDS 7
#define BUZZER 21

// Configuração do teclado matricial
#define LINHAS 4
#define COLS 4


// Pinos das linhas e colunas do teclado matricial
int linhas[4] = {16, 17, 18, 19}; // Pinos das linhas
int coluns[4] = {20, 8, 9, 28};   // Pinos das colunas


// Mapeamento de teclas para o teclado matricial
const char teclado[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};


// Estrutura que define a cor dos LEDs (RGB)
struct pixel_t {
    uint8_t G, R, B;
};
typedef struct pixel_t npLED_t;
npLED_t leds[Nleds];


// Variáveis para controle do PIO e da máquina de estado
PIO np_pio;
uint sm;


// Função para inicializar os pinos do teclado matricial
void iniciar_teclado() {
    // Configura os pinos das linhas como saída e em estado alto
    for (int i = 0; i < LINHAS; i++) {
        gpio_init(linhas[i]);
        gpio_set_dir(linhas[i], GPIO_OUT);
        gpio_put(linhas[i], 1);
    }


    // Configura os pinos das colunas como entrada com pull-up
    for (int j = 0; j < COLS; j++) {
        gpio_init(coluns[j]);
        gpio_set_dir(coluns[j], GPIO_IN);
        gpio_pull_up(coluns[j]);
    }
}

// Função para inicializar o buzzer
void ativar_buzzer(){
    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);
    gpio_put(BUZZER, 0); // Inicialmente desligado
}


// Função para capturar a tecla pressionada no teclado matricial
char ler_tecla() {
    for (int row = 0; row < LINHAS; row++) {
        gpio_put(linhas[row], 0); // Ativa a linha atual


        for (int col = 0; col < COLS; col++) {
            if (!gpio_get(coluns[col])) { // Detecta a tecla pressionada
                sleep_ms(50); // Debounce simples
                while (!gpio_get(coluns[col])); // Aguarda liberação
                gpio_put(linhas[row], 1); // Desativa a linha
                return teclado[row][col]; // Retorna a tecla pressionada
            }
        }


        gpio_put(linhas[row], 1); // Desativa a linha
    }
    return '\0'; // Nenhuma tecla pressionada
}


// Função para inicializar o controle dos LEDs
void npInit(uint pin) {
    uint offset = pio_add_program(pio0, &ws2818b_program); // Adiciona o programa PIO
    np_pio = pio0;
    sm = pio_claim_unused_sm(np_pio, true); // Reserva uma máquina de estado
    ws2818b_program_init(np_pio, sm, offset, pin, 800000.f); // Inicializa a PIO


    // Inicializa o buffer de LEDs com todos apagados
    for (uint i = 0; i < Nleds; ++i) {
        leds[i].R = leds[i].G = leds[i].B = 0;
    }
}


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

// Gera um tom no buzzer
void buzzer(int frequencia, int duracao_ms) {
    int delay_us = 1000000 / (frequencia * 2); // Tempo de meio ciclo
    int ciclos = (frequencia * duracao_ms) / 1000; // Número de ciclos

    for (int i = 0; i < ciclos; i++) {
        gpio_put(BUZZER, 1);
        sleep_us(delay_us);
        gpio_put(BUZZER, 0);
        sleep_us(delay_us);
    }
}

// Função para gerar o som no buzzer
void pan_pan_pan() {
    int frequencia_pan = 1050;  // Frequência em Hz
    int duracao_pan = 200;     // Duração em ms
    buzzer(frequencia_pan, duracao_pan);
}


// Função para tocar uma melodia crescente
void tocar_melodia(int linha) {
    // Notas que crescem em frequência e decrescem em duração
    int frequencia_inicial = 800;  // Frequência inicial em Hz
    int duracao_inicial = 200;     // Duração inicial em ms
    int frequencia_atual = frequencia_inicial + (30 * linha);
    int duracao_atual = duracao_inicial - (20 * linha);
    buzzer(frequencia_atual, duracao_atual);     


} // Fim da função de toque do buzzer

// Função para realizar a animação
void animacao1() {
    for (int linha = 0; linha < 5; linha++) {
        tocar_melodia(linha);
        desliga(); // Apaga todos os LEDs 
        for (int i = linha * 5; i < (linha + 1) * 5; i++) {
            cor(i, 255, 255, 0); // Ativa os LEDs R+G
        }
        buffer();
        sleep_ms(800); // Pausa
        
    }
    

    for (int j = 0; j < 3; j++){
        desliga();
        buffer(); 
        sleep_ms(500); // Pausa
        for (int i = 0; i < 25; i++) {
            cor(i, 0, 0, 255); // Ativa os LEDs B
        }
        pan_pan_pan();
        buffer(); 
        sleep_ms(800); // Pausa 
    }
    desliga();
    buffer();
}


// Função com o padrão
void padrao(char tecla) {
    desliga();
    switch (tecla) {
        case '3':
            printf("Animação de varredura \n"); //So para controle
            animacao1();
            break;
        default:
            printf("Tecla %c não é válida \n", tecla); //So para controle
            break;
    }
    buffer();
}


//Função main
int main() {
    stdio_init_all(); 
    iniciar_teclado();    
    npInit(MATRIZ_LEDS);
    ativar_buzzer(); 

    printf("Aperte a tecla 3!\n"); //So para controle

    while (true) {
        char tecla = ler_tecla(); // Lê a tecla pressionada
        if (tecla) {
            padrao(tecla); // Desenha o padrão correspondente
        }
        sleep_ms(200); 
    }

    return 0;
}



