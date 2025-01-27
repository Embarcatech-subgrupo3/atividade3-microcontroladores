#include "teclado.h"

// Definição dos pinos e mapeamento das teclas
const uint8_t ROWS[] = {18, 19, 20, 4}; // Linhas
const uint8_t COLS[] = {16, 17, 9, 8};  // Colunas
char keys[ROWS_COUNT][COLS_COUNT] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

// Inicializa o teclado matricial
void initKeypad()
{
    for (int i = 0; i < ROWS_COUNT; i++)
    {
        gpio_init(ROWS[i]);
        gpio_set_dir(ROWS[i], GPIO_OUT);
        gpio_put(ROWS[i], 1);

        gpio_init(COLS[i]);
        gpio_set_dir(COLS[i], GPIO_IN);
        gpio_pull_up(COLS[i]);
    }
}

// Lê uma tecla pressionada
char getKey()
{
    for (int row = 0; row < ROWS_COUNT; row++)
    {
        gpio_put(ROWS[row], 0);
        for (int col = 0; col < COLS_COUNT; col++)
        {
            if (!gpio_get(COLS[col]))
            {
                while (!gpio_get(COLS[col]))
                    ; // Aguarda até que a tecla seja solta
                gpio_put(ROWS[row], 1);
                return keys[row][col];
            }
        }
        gpio_put(ROWS[row], 1);
    }
    return 0; // Retorna 0 se nenhuma tecla foi pressionada
}
