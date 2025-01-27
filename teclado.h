
#include "pico/stdlib.h"

// Definições de pinos e mapeamento das teclas
#define ROWS_COUNT 4
#define COLS_COUNT 4

extern const uint8_t ROWS[];
extern const uint8_t COLS[];
extern char keys[ROWS_COUNT][COLS_COUNT];

// Funções do teclado matricial
void initKeypad();
char getKey();