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

void playAnimation(int nAnimacao)
{
    switch (nAnimacao)
    {
    case 1:
    for (int frame = 0; frame < FRAME_COUNT_1; ++frame)
    {
        displayFrame(animacao_1[frame]); // Exibe o frame atual
        sleep_ms(500);                // Pausa entre frames
    }
        break;
    case 2:
        for (int frame = 0; frame < FRAME_COUNT_2; ++frame)
        {
            displayFrame(animacao_2[frame]); // Exibe o frame da animação 2
            sleep_ms(250);                      // Pausa entre os frames
        }
        break;
    case 3:
        for (int frame = 0; frame < FRAME_COUNT_3; ++frame)
        {
            displayFrame(animacao_3[frame]); // Exibe o frame da animação 3
            sleep_ms(1000);                      // Pausa entre os frames
        }
        break;
    default:
        printf("Animação inválida: %d\n", nAnimacao);
        break;
    }
}