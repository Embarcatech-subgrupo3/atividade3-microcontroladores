#include "exibir_animação.h"
#include "led_matrix_limpar.h"
#include "buzzer.h"

int getIndex(int x, int y);   // Declaração explícita
void npSetLED(int index, uint8_t r, uint8_t g, uint8_t b);
void npWrite(void);
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

// reproduz o frame com a musica
void displayFrameMusic(int nAnimacao)
{
    int total_notes = SONG_OF_STORMS_NOTES_COUNT;
    int frame = 0;
    if (nAnimacao == 4)
    {
        for (int i = 0; i < total_notes; i++)
        {
            // Exibe o frame atual da animação

            displayFrame(animacao_4[frame]);

            // Toca a nota correspondente
            buzzer_tone(song_of_storms_notes[i], song_of_storms_durations[i]);

            // Avança para o próximo frame (loop circular)
            frame = (frame + 1) % FRAME_COUNT_4;
        }
    }
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
            sleep_ms(500);                   // Pausa entre frames
        }
        break;
    case 2:
        for (int frame = 0; frame < FRAME_COUNT_2; ++frame)
        {
            displayFrame(animacao_2[frame]); // Exibe o frame da animação 2
            sleep_ms(250);                   // Pausa entre os frames
        }
        break;
    case 3:
        for (int frame = 0; frame < FRAME_COUNT_3; ++frame)
        {
            displayFrame(animacao_3[frame]); // Exibe o frame da animação 3
            sleep_ms(1000);                  // Pausa entre os frames
        }
        break;
    case 4:
        for (int frame = 0; frame < FRAME_COUNT_4; ++frame)
        {
            displayFrameMusic(4); // Executa a animação e a música ao mesmo tempo
            sleep_ms(500);        // Pausa entre os frames
        }
        break;
    default:
        break;
    }
}