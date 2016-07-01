#include "i2c.h"
#include <util/twi.h>
#include <util/delay.h>
/*
Baudrate auf 400kHz setzen
TWPS = letzte 2 Bit aus TWSR
TWPS (Prescaler) auf 0
Baudrate = FREQ / ( 16 + 2(PWBR) * 4^TWPS)
400000 = 16000000 / ( 16 + 2(PWBR) )
400000 * 16 + 400000 * 2PWBR = 16000000
640000 + 800000 * PWBR = 16000000
80000 PWBR = 9600000
PWBR = 12
*/
void twiInit(void){
// für 200KHz bei 16MHz
// TWPS=2  TWBR=2


//	TWSR = 0x03;
// 	TWBR = 0x04; // 12
	TWSR|=0x02;
	TWBR=2;

// im Kontrollregister aktivieren
	TWCR = (1<<TWEN);
}

void twiStartCond(){
  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while ( ! (TWCR & (1<<TWINT)))	
		;
}

unsigned char twiStart(unsigned char addr){
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while ( ! (TWCR & (1<<TWINT)))	
		;
	if( (TWSR & 0xF8) != START) 
		return 0;
	_delay_us(100);
	TWDR=addr;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while ( ! (TWCR & (1<<TWINT)))
		;
	if( (TWSR & 0xF8) != MT_SLA_ACK) 
		return 0;
	return 1;
}

void twiStop(){
	TWCR =(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
// TWSTO wird automatisch gelöscht
}

void twiWrite(unsigned char data){
	TWDR=data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while((TWCR & (1<<TWINT)) == 0 );
}

unsigned char twiReadACK(){
	TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	while((TWCR & (1<<TWINT))==0);
	return TWDR;	
}

unsigned char twiReadNACK(){
	TWCR = (1<<TWINT)|(1<<TWEN); // |(0<<TWEA) (TwoWireEnableACK)
	while((TWCR & (1<<TWINT))==0);
	return TWDR;	
}

void twiWriteArr(unsigned char addr, unsigned char data[], unsigned char length){
	twiStart(addr);
//	twiWrite(addr);
	unsigned char i;
	for(i=0;i<length;i++){
		twiWrite(data[i]);
	}
	twiStop();
}

void twiWriteByte(unsigned char addr, unsigned char byte){
	twiStart(addr);
//	twiWrite(addr);
	twiWrite(byte);
	twiStop();
}
