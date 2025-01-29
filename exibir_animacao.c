#include "exibir_animação.h"
#include "led_matrix_limpar.h"
#include "buzzer.h"
#include <stdio.h>
#define MAX_MUSIC_TIME 20000 // Tempo maximo de reproducao da musica em ms

int getIndex(int x, int y); // Declaração explícita
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
    int total_notes;
    int frame = 0;
    int total_time_ms = 0; // Tempo total acumulado (em milissegundos)
    const uint *music_notes;
    const uint *music_durations;
    int frame_count;

    // Escolhe a música e animação correta
    switch (nAnimacao)
    {
    case 1: // Song of Storms + Animação 1
        total_notes = SONG_OF_STORMS_NOTES_COUNT;
        music_notes = song_of_storms_notes;
        music_durations = song_of_storms_durations;
        frame_count = FRAME_COUNT_1;
        break;

    case 3: // Super Mario Bros + Animação 3
        total_notes = SUPER_MARIO_NOTES_COUNT;
        music_notes = super_mario_notes;
        music_durations = super_mario_durations;
        frame_count = FRAME_COUNT_3;
        break;

    default:
        printf("Animação inválida ou não associada a uma música.\n");
        return;
    }

    // Reproduz a música e animação simultaneamente
    for (int i = 0; i < total_notes; i++)
    {
        // Verifica se o tempo total excedeu 20 segundos (20.000 ms)
        if (total_time_ms > MAX_MUSIC_TIME)
        {
            printf("Tempo limite de 20 segundos atingido.\n");
            break;
        }

        // Exibe o frame atual da animação
        if (nAnimacao == 1)
            displayFrame(animacao_1[frame]);
        else if (nAnimacao == 3)
            displayFrame(animacao_3[frame]);

        // Toca a nota correspondente
        buzzer_tone(music_notes[i], music_durations[i]);

        // Soma o tempo de execução da nota ao tempo total
        total_time_ms += music_durations[i];

        // Avança para o próximo frame (loop circular)
        frame = (frame + 1) % frame_count;
    }
}

// Reproduz a animação completa

void playAnimation(int nAnimacao)
{
    switch (nAnimacao)
    {
    case 1:
        displayFrameMusic(1); // Executa a animação e a música ao mesmo tempo
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
            displayFrameMusic(3); // Executa a animação e a música ao mesmo tempo
        }
        break;
    case 4:
        for (int frame = 0; frame < FRAME_COUNT_4; ++frame)
        {
            displayFrame(animacao_4[frame]); // Exibe o frame atual
            sleep_ms(500);                   // Pausa entre frames
        }
        break;
    case 5:
        for (int frame = 0; frame < FRAME_COUNT_5; ++frame)
        {
            displayFrame(animacao_5[frame]); // Exibe o frame atual
            sleep_ms(750);                   // Pausa entre frames
        }
        break;
    case 6:
        for (int frame = 0; frame < FRAME_COUNT_6; ++frame)
        {
            displayFrame(animacao_6[frame]); // Exibe o frame atual
            sleep_ms(750);                   // Pausa entre frames
        }
        break;
        case 7:
        for (int frame = 0; frame < FRAME_COUNT_7; ++frame)
        {
            displayFrame(animacao_7[frame]); // Exibe o frame atual
            sleep_ms(750);                   // Pausa entre frames
        }
        break;
        case 8:
        for (int frame = 0; frame < FRAME_COUNT_8; ++frame)
        {
            displayFrame(animacao_8[frame]); // Exibe o frame atual
            sleep_ms(750);                   // Pausa entre frames
        }
        break;

    default:
        break;
    }
}