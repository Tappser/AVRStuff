  // UART

#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include "uart.h"

 

FILE uart_file = FDEV_SETUP_STREAM(uart_write,uart_read, _FDEV_SETUP_RW);

void uartInit(void){
  UBRR0H =(uint8_t) (UART_BAUD_CALC(UART_BAUD_RATE,F_CPU)>>8);
  UBRR0L =(uint8_t) UART_BAUD_CALC(UART_BAUD_RATE,F_CPU);

  UCSR0B = (1<<RXEN0) | (1<<TXEN0);  // enable receiver and transmitter
  UCSR0C = (3<<UCSZ00);        // 8 bit (default: asynchronous, no parity,1stop-bit)
}

void uart_puts (char *s)
{
    while (*s)
    {   /* so lange *s != '\0' also ungleich dem "String-Endezeichen(Terminator)" */
        uart_putc(*s);
        s++;
    }
}

void uart_putc( char c)
{
    while (!(UCSR0A & (1<<UDRE0)))  /* warten bis Senden moeglich */
    {
    }                              
    UDR0 = c;                      /* sende Zeichen */
}

// read serial
uint8_t uart_read() {
	// wait for byte
	while(!(UCSR0A&(1<<RXC0)) ){};

	return (uint8_t)UDR0;
}

void uart_set_stdin() {
	stdin = &uart_file;
}

// set serial as stdout
void uart_set_stdout() {
	 stdout = &uart_file;
}

void uart_write(uint8_t data) {
	// wait for empty transmit buffer
	while(!(UCSR0A&(1<<UDRE0))){};
		
	// send data
	UDR0 = data;
}
