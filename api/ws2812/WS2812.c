#include "WS2812.h"

uint8_t LED_i;

void initLED(){
  LEDDDR |= (1<<LEDPIN);
}
/*
void writeByte(uint8_t val){
  for(LED_i=0;LED_i<8;LED_i++){
    if(val & (1<<(7-LED_i))){
  LED_PORT |= (1<<LED_PIN);
	_delay_us(0.9);
  LED_PORT &= ~(1<<LED_PIN);
  _delay_us(0.2);
    }
    else{
  LED_PORT |= (1<<LED_PIN);
	_delay_us(0.2);
  LED_PORT &=~(1<<LED_PIN);
	_delay_us(0.9);
    }
  }
}
*/


void writeByte(uint8_t val){
        uint8_t i=0;
  for(i=0;i<8;i++){
    if(val & (1<<(7-i))){
        LEDPORT |= (1<<LEDPIN);
        _delay_us(0.2);
        LEDPORT &= ~(1<<LEDPIN);
        _delay_us(0.1);
    }
    else{
        LEDPORT |= (1<<LEDPIN);
//        _delay_us(0.2);
        LEDPORT &= ~(1<<LEDPIN);
        _delay_us(0.2);
        DDRD|=0x02;
        PORTD|=0x02;
    }
  }
}




void writeColor(uint8_t r, uint8_t g, uint8_t b){
  writeByte(g);
  writeByte(r);
  writeByte(b);
}
