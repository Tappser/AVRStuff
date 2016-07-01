#include <avr/io.h>
#include <util/twi.h>

#define MT_SLA_ACK 0x18
#define MT_DATA_ACK 0x28
#define START 0x08
#define REP_START 0x10

void twiInit(void);
void twiStartCond(void);
unsigned char twiStart(unsigned char);
void twiStop(void);
void twiWrite(unsigned char);
unsigned char twiReadACK(void);
unsigned char twiReadNACK(void);
void twiWriteArr(unsigned char, unsigned char[], unsigned char);
void twiWriteByte(unsigned char, unsigned char);
