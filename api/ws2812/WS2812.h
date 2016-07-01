#ifndef F_CPU
  #define F_CPU (16000000UL)
#endif
#include <avr/io.h>
#include <util/delay.h>
#define LEDPORT PORTD
#define LEDPIN PD2
#define LEDDDR DDRD

void initLED(void);
void writeColor(uint8_t, uint8_t, uint8_t);
