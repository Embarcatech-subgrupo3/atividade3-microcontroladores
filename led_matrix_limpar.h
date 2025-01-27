
#include <stdint.h>
#include "hardware/pio.h"

// Número de LEDs e pino de controle
#define LED_COUNT 25
#define LED_PIN 7

// Estrutura de pixel GRB
typedef struct
{
    uint8_t G, R, B;
} npLED_t;

extern npLED_t leds[LED_COUNT];
extern PIO np_pio;
extern uint sm;

// Declaração da função para desligar todos os LEDs
void LimparLEDMatrix();
