#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "led_matrix_limpar.h"
#include "ws2818b.pio.h"
#include "teclado.h"
#include "exibir_animação.h"
#include "buzzer.h"
// #include "pico/multicore.h"

// Buffer de LEDs e variáveis PIO
npLED_t leds[LED_COUNT];
PIO np_pio;
uint sm;

/**
 * Inicializa a máquina PIO para controle da matriz de LEDs.
 */

// void core1_entry() {
//     play_song_of_storms(); // Toca a música em um núcleo separado
// }

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
// Tecla C: Liga todos os LEDs na cor vermelha com 80% de intensidade
void tecla_C()
{
    for (uint i = 0; i < LED_COUNT; ++i)
    {
        npSetLED(i, 204, 0, 0); // Vermelho com 80% de intensidade
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
// tecla #
void tecla_especial_1(){
                for (uint i = 0; i < LED_COUNT; ++i) {
                npSetLED(i, 51, 51, 51); // Ligar todos os LEDs na cor branca com 20% de intensidade
            }
            npWrite();
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
            else if (key == 'C')
            {
                printf("Ligando todos os leds em vermelho com 80%% de intensidade\n");
                tecla_C();
            }
            else if (key == 'D')
            {
                printf("Ligando todos os leds em verde com 50%% de intensidade\n");
                tecla_D();
            }
            else if (key == '#')
            {
                printf("Ligando todos os leds em branco com 20%% de intensidade\n");
                tecla_especial_1();
            }
            else if (key >= '1' && key <= '9') // Garante que o caractere está entre '1' e '9'
            {
                int animacao = key - '0'; // Converte o caractere para o número correspondente
                printf("Exibindo a animação %d\n", animacao);
                playAnimation(animacao); // Passa o número como parâmetro para a função
                sleep_ms(1000);
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
