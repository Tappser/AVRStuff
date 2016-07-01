//#define F_CPU 11059200UL

#define UART_BAUD_RATE 9600
#define UART_BAUD_CALC(UART_BAUD_RATE,F_OSC)((F_CPU)/((UART_BAUD_RATE)*16L)-1)

void uartInit(void);
void uart_puts(char *s);
void uart_putc( char c);
uint8_t uart_read(void);
void uart_set_stdin(void) ;
void uart_set_stdout(void);
void uart_write(uint8_t data);
