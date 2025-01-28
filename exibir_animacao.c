#include "exibir_animação.h"
#include "led_matrix_limpar.h"

void displayFrame(const uint32_t *frame)
{
    // Varre a matriz de LEDs
    for (int y = 0; y < FRAME_HEIGHT; ++y)
    { // Linhas da matriz
        for (int x = 0; x < FRAME_WIDTH; ++x)
        { // Colunas da matriz
            // Extrai a cor do frame atual
            uint32_t color = frame[y * FRAME_WIDTH + x];
            uint8_t r = (color >> 16) & 0xFF; // Componente vermelho
            uint8_t g = (color >> 8) & 0xFF;  // Componente verde
            uint8_t b = color & 0xFF;         // Componente azul

            // Calcula o índice correto para o LED na matriz
            int index = getIndex(x, y);

            // Define a cor no LED específico
            npSetLED(index, r, g, b);
        }
    }
    // Atualiza a matriz de LEDs
    npWrite();
}

// Reproduz a animação completa
void playAnimation()
{
    for (int frame = 0; frame < FRAME_COUNT; ++frame)
    {
        displayFrame(cobrinha[frame]); // Exibe o frame atual
        sleep_ms(1000);                // Pausa entre frames
    }
}
