#include "exibir_animação.h"
#include "led_matrix_limpar.h"

// Exibe um frame da animação na matriz de LED
// void npWrite()
// {
//     for (uint i = 0; i < LED_COUNT; ++i)
//     {
//         pio_sm_put_blocking(np_pio, sm, leds[i].G);
//         pio_sm_put_blocking(np_pio, sm, leds[i].R);
//         pio_sm_put_blocking(np_pio, sm, leds[i].B);
//     }
// }

void displayFrame(const uint32_t *frame) {
    for (int y = 0; y < FRAME_HEIGHT; ++y) {
        for (int x = 0; x < FRAME_WIDTH; ++x) {
            uint32_t color = frame[y * FRAME_WIDTH + x];
            uint8_t r = (color >> 16) & 0xFF; // Extrai componente vermelho
            uint8_t g = (color >> 8) & 0xFF;  // Extrai componente verde
            uint8_t b = color & 0xFF;         // Extrai componente azul
            int index = getIndex(x, y);      // Calcula índice na matriz
            npSetLED(index, r, g, b);
        }
    }
    npWrite(); // Atualiza os LEDs
}

// Reproduz a animação completa
void playAnimation() {
    for (int frame = 0; frame < FRAME_COUNT; ++frame) {
        displayFrame(cobrinha[frame]); // Exibe o frame atual
        sleep_ms(1000);                // Pausa entre frames
    }
}
