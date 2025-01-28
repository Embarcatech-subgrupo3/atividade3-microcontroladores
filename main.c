#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "led_matrix_limpar.h"
#include "ws2818b.pio.h"
#include "teclado.h"
#include "exibir_animação.h"
#include "buzzer.h"
// Buffer de LEDs e variáveis PIO
npLED_t leds[LED_COUNT];
PIO np_pio;
uint sm;

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
     pwm_init_buzzer(BUZZER_PIN);
    // Desenha o coração
    drawHeart();

    // Envia os dados do coração para os LEDs
    npWrite();

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
            else if (key >= '1' && key <= '9') // Garante que o caractere está entre '1' e '9'
            {
                // printf("Tocando buzzer\n");
                // play_tone(1000, 500);
                printf("Tocando buzzer SEM PWM\n");
                // play_star_wars(BUZZER_PIN);
                int animacao = key - '0'; // Converte o caractere para o número correspondente
                printf("Exibindo a animação %d\n", animacao);
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
