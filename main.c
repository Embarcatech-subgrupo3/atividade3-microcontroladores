//#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "led_matrix_limpar.h"
#include "ws2818b.pio.h"
#include "teclado.h"
#include "exibir_animação.h"
//#include "buzzer.h"
// Buffer de LEDs e variáveis PIO
npLED_t leds[LED_COUNT];
PIO np_pio;
uint sm;
// Definição do número de LEDs e pino.
#define LED_COUNT 25
#define LED_PIN 7
#define BUZZER_PIN 21  // Pino para o buzzer

#define FRAME_COUNT_3 6
#define FRAME_WIDTH_3 5
#define FRAME_HEIGHT_3 5

uint8_t image[FRAME_COUNT_3][FRAME_HEIGHT_3][FRAME_WIDTH_3][3] = {
    {
        {{0, 0, 0}, {0, 0, 255}, {255, 255, 255}, {0, 0, 255}, {0, 0, 0}},
        {{255, 255, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {255, 255, 255}},
        {{0, 0, 0}, {249, 249, 249}, {249, 249, 249}, {249, 249, 249}, {0, 0, 0}},
        {{0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}},
        {{0, 0, 0}, {249, 249, 249}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}}
    },
    {
        {{0, 0, 0}, {255, 0, 0}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}},
        {{255, 255, 255}, {255, 255, 255}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}},
        {{0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {255, 255, 255}, {255, 255, 255}},
        {{0, 255, 0}, {0, 255, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}},
    },
    {
        {{0, 0, 0}, {0, 0, 255}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}},
        {{255, 255, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {255, 255, 255}},
        {{0, 0, 0}, {249, 249, 249}, {249, 249, 249}, {249, 249, 249}, {0, 0, 0}},
        {{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}},
        {{0, 0, 0}, {255, 255, 255}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}}
    },
    {
        {{0, 0, 0}, {0, 0, 255}, {255, 255, 255}, {0, 0, 255}, {0, 0, 0}},
        {{213, 186, 152}, {0, 0, 255}, {255, 255, 255}, {0, 0, 255}, {213, 186, 152}},
        {{0, 0, 0}, {213, 186, 152}, {213, 186, 152}, {213, 186, 152}, {0, 0, 0}},
        {{255, 0, 0}, {255, 255, 255}, {255, 255, 255}, {255, 0, 0}, {255, 0, 0}},
        {{0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}}
    },
    {
        {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}},
        {{255, 255, 255}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {255, 255, 255}},
        {{0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}},
        {{255, 255, 255}, {0, 255, 0}, {255, 255, 255}, {0, 255, 0}, {255, 255, 255}},
        {{0, 255, 0}, {255, 255, 255}, {0, 255, 0}, {255, 255, 255}, {0, 255, 0}}
    }
};
// Definindo a melodia
#define NOTE_A7  3520
#define NOTE_F7  2794
#define NOTE_E7  2637
#define NOTE_C7  2093
#define NOTE_G7  3136
#define NOTE_G6  1568
#define NOTE_E6  1319
#define NOTE_A6  1760
#define NOTE_B6  1976
#define NOTE_AS6 1865
#define NOTE_D7  2349
#define NOTE_B6  1976
#define NOTE_C5  523
#define NOTE_G4  392
#define NOTE_E4  330
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_GS4 415
#define NOTE_AS4 466
#define NOTE_D4  294
#define REST      0


float melody[] = {
    NOTE_E7, NOTE_E7, 0, NOTE_E7,
    0, NOTE_C7, NOTE_E7, 0,
    NOTE_G7, 0, 0, 0,
    NOTE_G6, 0, 0, 0,

    NOTE_C7, 0, 0, NOTE_G6,
    0, 0, NOTE_E6, 0,
    0, NOTE_A6, 0, NOTE_B6,
    0, NOTE_AS6, NOTE_A6, 0,

    NOTE_G6, NOTE_E7, NOTE_G7,
    NOTE_A7, 0, NOTE_F7, NOTE_G7,
    0, NOTE_E7, 0, NOTE_C7,
    NOTE_D7, NOTE_B6, 0, 0,

    NOTE_C7, 0, 0, NOTE_G6,
    0, 0, NOTE_E6, 0,
    0, NOTE_A6, 0, NOTE_B6,
    0, NOTE_AS6, NOTE_A6, 0,

    NOTE_G6, NOTE_E7, NOTE_G7,
    NOTE_A7, 0, NOTE_F7, NOTE_G7,
    0, NOTE_E7, 0, NOTE_C7,
    NOTE_D7, NOTE_B6, 0, 0,

    NOTE_E7, NOTE_E7, 0, NOTE_E7,
    0, NOTE_C7, NOTE_E7, 0,
    NOTE_G7, 0, 0, 0,
    NOTE_G6, 0, 0, 0,

    NOTE_C7, 0, 0, NOTE_G6,
    0, 0, NOTE_E6, 0,
    0, NOTE_A6, 0, NOTE_B6,
    0, NOTE_AS6, NOTE_A6, 0,

    NOTE_G6, NOTE_E7, NOTE_G7,
    NOTE_A7, 0, NOTE_F7, NOTE_G7,
    0, NOTE_E7, 0, NOTE_C7,
    NOTE_D7, NOTE_B6, 0, 0, REST, REST,


};

int noteDurations[] = {
    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,

    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,

    9, 9, 9,
    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,

    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,

    9, 9, 9,
    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,

    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,

    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12,

    9, 9, 9,
    12, 12, 12, 12,
    12, 12, 12, 12,
    12, 12, 12, 12, 0

};
// Função para definir a cor de um LED
void npSetLED(uint index, uint8_t r, uint8_t g, uint8_t b);
// Função para atualizar os LEDs
void npWrite();
// Função para acender os LEDs de acordo com o frame, tocando uma nota a cada LED aceso
// Declaração correta da função
void npDisplayFrameWithSound(const uint8_t frame[FRAME_HEIGHT][FRAME_WIDTH][3], int* melodyIndex);
// Função para tocar uma nota musical no buzzer
void playTone(uint frequency, uint duration);
// Função para tocar a animação com som
void npPlayAnimation();
// Função para acender os LEDs de acordo com o frame, tocando uma nota a cada LED aceso
void npDisplayFrameWithSound(const uint8_t frame[5][5][3], int* melodyIndex) {
    int index = 0;
    for (uint i = 0; i < 5; i++) {
        for (uint j = 0; j < 5; j++) {
            leds[index].R = frame[i][j][0];
            leds[index].G = frame[i][j][1];
            leds[index].B = frame[i][j][2];
            playTone(melody[*melodyIndex], noteDurations[*melodyIndex] * 100);
            (*melodyIndex)++;
            npWrite();
            index++;
        }
    }
}
// Função para tocar uma nota musical no buzzer
#define TEMPO_BASE 250000  // Duração da semínima em ms 

void playTone(uint frequency, uint duration) {
    uint Duration = TEMPO_BASE / duration;  // Calcula a duração real da nota
    uint delay = 400000 / frequency;           // Calcula o tempo de delay baseado na frequência
    uint cycles = frequency * Duration / 900;  // Número de ciclos para a duração em ms

    for (uint i = 0; i < cycles; i++) {
        gpio_put(BUZZER_PIN, 1);  // Liga o buzzer
        sleep_us(delay);
        gpio_put(BUZZER_PIN, 0);  // Desliga o buzzer
        sleep_us(delay);
    }
}


void npPlayAnimation() {
    int melodyIndex = 0;
    for (uint frame = 0; frame < FRAME_COUNT_3; frame++) {
        npDisplayFrameWithSound(image[frame], &melodyIndex);
        sleep_ms(300);  // Tempo entre frames
    }
}

/**
 * Inicializa a máquina PIO para controle da matriz de LEDs.
 */
void npInit(uint pin)
{
    uint offset = pio_add_program(pio0, &ws2818b_program);
    np_pio = pio0;

    sm = pio_claim_unused_sm(np_pio, false);
    if (sm < 0)
    {
        np_pio = pio1;
        sm = pio_claim_unused_sm(np_pio, true);
    }

    ws2818b_program_init(np_pio, sm, offset, pin, 800000.f);

    for (uint i = 0; i < LED_COUNT; ++i)
    {
        leds[i].R = 0;
        leds[i].G = 0;
        leds[i].B = 0;
    }
}

void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b)
{
    leds[index].R = r;
    leds[index].G = g;
    leds[index].B = b;
}
void npWrite()
{
    for (uint i = 0; i < LED_COUNT; ++i)
    {
        pio_sm_put_blocking(np_pio, sm, leds[i].G);
        pio_sm_put_blocking(np_pio, sm, leds[i].R);
        pio_sm_put_blocking(np_pio, sm, leds[i].B);
    }
}
void tecla_B()
{
    for (uint i = 0; i < LED_COUNT; ++i)
    {
        npSetLED(i, 0, 0, 255); // Azul com 100% de intensidade
    }
    npWrite(); // Atualiza os LEDs
}

void tecla_D()
{
    for (uint i = 0; i < LED_COUNT; ++i)
    {
        npSetLED(i, 0, 128, 0); // Verde com 50% de intensidade
    }
    npWrite(); // Atualiza os LEDs
}

int getIndex(int x, int y)
{ // função para obter o index do LED, convertendo a linha e coluna.
    if (y % 2 == 0)
    {
        return y * 5 + x;
    }
    else
    {
        return y * 5 + (4 - x);
    }
}

void drawHeart()
{
    int heart[10][2] = {
        {1, 4}, {3, 4}, {0, 3}, {2, 3}, {4, 3}, {0, 2}, {4, 2}, {1, 1}, {3, 1}, {2, 0}};

    for (int i = 0; i < 10; i++)
    {
        int index = getIndex(heart[i][0], heart[i][1]);
        npSetLED(index, 50, 0, 0);
    }
}

int main()
{
    // Inicializa entradas e saídas.
    stdio_init_all();

    // Inicializa a matriz de LEDs NeoPixel.
    npInit(LED_PIN);
    // inicializa o teclado
    initKeypad();
    // inicializa o buzzer
        // pwm_init_buzzer(BUZZER_PIN);

    // Desenha o coração
    drawHeart();

    // Envia os dados do coração para os LEDs
    npWrite();
  // Configura o pino do buzzer
  gpio_init(BUZZER_PIN);
  gpio_set_dir(BUZZER_PIN, GPIO_OUT);
  gpio_put(BUZZER_PIN, 0); // Inicializa o buzzer desligado

    while (true)
    {
        int key = getKey();
        // getchar_timeout_us(10000); // Lê a tecla pressionada a partir da entrada serial
        // getKey(); // Lê a tecla pressionada a partir do teclado matricial
        if (key)
        {

            if (key == 'A')
            {
                // Chama a função para limpar a matriz de LEDs
                printf("Desligando todas os leds da matriz\n");
                LimparLEDMatrix();
            }
            else if (key == 'B')
            {
                printf("Ligando todos os leds em azul com 100%% de intensidade\n");
                tecla_B();
            }
            else if (key == 'D')
            {
                printf("Ligando todos os leds em verde com 50%% de intensidade\n");
                tecla_D();
            }
            else if (key == '3')
            {
                npPlayAnimation();
            }
            else if (key >= '1' && key <= '9') // Garante que o caractere está entre '1' e '9'
            {
                // printf("Tocando buzzer\n");
                // play_tone(1000, 500);
                // play_star_wars(BUZZER_PIN);
                int animacao = key - '0'; // Converte o caractere para o número correspondente
                playAnimation(animacao); // Passa o número como parâmetro para a função
                sleep_ms(2000);
                LimparLEDMatrix();
            }
        }
    }

    // Loop infinito sem mais ações
    while (true)
    {
        sleep_ms(1000);
    }
}
