#include "WS2812_speed.h"

uint8_t LED_PIN;
volatile uint8_t* LED_PORT;
uint8_t LED_PINMASK;
uint8_t LED_NPINMASK;
//#define *LED_PORT |= LED_PINMASK (*LED_PORT |= (uint8_t) LED_PINMASK)
//#define *LED_PORT &= LED_NPINMASK (*LED_PORT &= (uint8_t) ~LED_PINMASK)

//#define *LED_PORT |= LED_PINMASK (PORTD |= LED_PINMASK)
//#define *LED_PORT &= LED_NPINMASK (PORTD &= LED_NPINMASK)

void setLEDPort(volatile uint8_t* port, uint8_t pin){
  LED_PORT = port;
  LED_PIN=pin;
  LED_PINMASK=(1<<pin);
  LED_NPINMASK=~LED_PINMASK;
}
uint8_t LED_i;
uint8_t LED_val;
void writeByte(uint8_t val){
  for(LED_i=0;LED_i<8;LED_i++){
    if(val & (1<<(7-LED_i))){
  *LED_PORT |= LED_PINMASK;
	_delay_us(0.2);
  *LED_PORT &= LED_NPINMASK;
  _delay_us(0.3);
    }
    else{
  LED_val=*LED_PORT;
  *LED_PORT |= LED_PINMASK;
//	_delay_us(0.00001);
//  PORTD &= LED_NPINMASK;
  *LED_PORT=LED_val;
	_delay_us(0.3);
    }
  }
}

void writeColor(uint8_t r, uint8_t g, uint8_t b){
  writeByte(g);
  writeByte(r);
  writeByte(b);
}
