#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "led_matrix_limpar.h"
#include "ws2818b.pio.h"
#include "teclado.h"
#include "exibir_animação.h"
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
        npSetLED(index, 255, 0, 0);
    }
}

int main()
{
    char modo = "L"; // "S" para Serial, "T" para Teclado Matricial
    // Inicializa entradas e saídas.
    stdio_init_all();

    // Inicializa a matriz de LEDs NeoPixel.
    npInit(LED_PIN);
    // inicializa o teclado
    initKeypad();

    // Desenha o coração
    drawHeart();

    // Envia os dados do coração para os LEDs
    npWrite();

    while (true)
    {
        char key[1];
        if(modo == "T"){
            key[0] = getKey();
        } else if(modo == "S") {
            key[0] = getchar_timeout_us(10000); // Lê a tecla pressionada a partir da entrada serial
        }
        if (key)
        {
            printf("Tecla pressionada: %c\n", key);

            if (key == 'A')
            {
                // Chama a função para limpar a matriz de LEDs
                printf("Desligando todas os leds da matriz\n");
                LimparLEDMatrix();
            }
            else if (key == '1')
            {
                printf("...\n");
                playAnimation();
            }
        }
    }

    // Loop infinito sem mais ações
    while (true)
    {
        sleep_ms(1000);
    }
}
