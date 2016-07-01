  // UART

#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include <avr/interrupt.h>
 

FILE uart_file = FDEV_SETUP_STREAM(uart_write,uart_read, _FDEV_SETUP_RW);


volatile char uart_string[UART_MAXSTRLEN +1] ="";
volatile uint8_t uart_str_count = 0;

void uartInit(void){
  UBRR0H =(uint8_t) (UART_BAUD_CALC(UART_BAUD_RATE,F_CPU)>>8);
  UBRR0L =(uint8_t) UART_BAUD_CALC(UART_BAUD_RATE,F_CPU);

  UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE) ;  // enable receiver and transmitter, RX Complete Interrupt, 
  UCSR0C = (3<<UCSZ00);        // 8 bit (default: asynchronous, no parity,1stop-bit)
}

ISR(USART_RXC_vect)
{
  unsigned char myChar;
  myChar=UDR;
  if(myChar!='\n' && myChar != '\r' && uart_str_count < UART_MAXSTRLEN){
    uart_string[uart_str_count]=myChar;
    uart_str_count++;
  }else{
    uart_string[uart_str_count]='\0';
    uart_str_count=0;
  }  
}
  
