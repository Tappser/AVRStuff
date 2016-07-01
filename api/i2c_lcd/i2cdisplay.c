#include "i2cdisplay.h"
#include <util/delay.h>
#define backlight 1

void lcdWriteByte(uint8_t id, bool zielReg, uint8_t data){
	twiStart((id<<1));
// erst die oberen 4 bits
	twiWrite((data & 0xf0)|(zielReg<<RSPIN)|(backlight<<BLPIN)|(1<<EPIN));
	twiWrite((data & 0xf0)|(zielReg<<RSPIN)|(backlight<<BLPIN));
	_delay_us(100);
// dann die unteren
  twiWrite(((data & 0x0f)<<4)|(zielReg<<RSPIN)|(backlight<<BLPIN)|(1<<EPIN));
  twiWrite(((data & 0x0f)<<4)|(zielReg<<RSPIN)|(backlight<<BLPIN));
	_delay_us(100);
  twiStop();
}

void lcdWrite(bool zielReg, uint8_t data){
// erst die oberen 4 bits
  twiWrite((data & 0xf0)|(zielReg<<RSPIN)|(backlight<<BLPIN)|(1<<EPIN));
  twiWrite((data & 0xf0)|(zielReg<<RSPIN)|(backlight<<BLPIN));
	_delay_us(100);
// dann die unteren
  twiWrite(((data & 0x0f)<<4)|(zielReg<<RSPIN)|(backlight<<BLPIN)|(1<<EPIN));
  twiWrite(((data & 0x0f)<<4)|(zielReg<<RSPIN)|(backlight<<BLPIN));
	_delay_us(100);
}

void lcdWriteB(uint8_t id, bool zielReg, uint8_t data){
  if(id==0){
    lcdWrite(zielReg,data);
  }else{
    lcdWriteByte(id,zielReg,data);
  }
}

void lcdClear(uint8_t id){
    lcdWriteB(id,LCD_COMMANDREG,0x01);
}

void lcdSetFunction(uint8_t id, bool dl, bool lines,bool font){
  /* N  F   Lines  Font
     0  0   1      5x8
     0  1   1      5x10
     1  *   2      5x8   */
  //DL: 1->8bit 0->4bit !!! über den i2c-adapter 4bit-mode, daher nicht beachtet !!!
  //N : number of display lines
  //F : Character font
  // RS RW DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
  // 0  0  0   0   1   DL  N   F   *   *
    lcdWriteB(id, LCD_COMMANDREG, ((1<<5)|(dl<<LCD_DLBIT)|(lines<<LCD_LINEBIT)|(font<<LCD_FONTBIT)) );
}

void lcdSetOn(uint8_t id, bool status, bool cursor, bool blink){
    lcdWriteB(id, LCD_COMMANDREG, ((1<<3)|(status<<LCD_DISPLAYONBIT)|(cursor<<LCD_CURSORBIT)|(blink<<LCD_BLINKBIT)));
}

void lcdSetDDAddr(uint8_t id, uint8_t addr){
    lcdWriteB(id,LCD_COMMANDREG, ((1<<7)|addr));
}

void lcdSetCGAddr(uint8_t id, uint8_t addr){
    lcdWriteB(id,LCD_COMMANDREG, ((1<<6)|addr));
}

void lcdReturnHome(uint8_t id){
    lcdWriteB(id,LCD_COMMANDREG, (1<<1));
}

void lcdSetEntryMode(uint8_t id, bool dir, bool dShift){
  lcdWriteB(id, LCD_COMMANDREG, ((dir<<LCD_IDBIT)|(dShift<<LCD_SBIT)|(1<<2)));
}

void lcdInit(uint8_t id){
  if(twiStart((id<<1))){
		for(uint8_t i=0; i<3;i++){
			twiWrite(0x3C);
			_delay_us(100);
			twiWrite(0x38);
			_delay_ms(5);
		}
		twiWrite(0x2C);
		twiWrite(0x28);
		_delay_ms(1);
//	  lcdSetFunction(0,EIGHTMODE,TWOLINES,SMALLFONT);
//	  lcdSetFunction(0,EIGHTMODE,TWOLINES,SMALLFONT);
//	  lcdSetFunction(0,EIGHTMODE,TWOLINES,SMALLFONT);
//	  lcdSetFunction(0,FOURMODE,TWOLINES,SMALLFONT);
	  lcdClear(0);
		_delay_ms(1);
		lcdSetDDAddr(0,0);
		_delay_ms(1);
	  lcdSetFunction(0,LCD_FOURMODE,LCD_TWOLINES,LCD_SMALLFONT);
		_delay_ms(1);
	  lcdSetOn(0,true,false,true);
		_delay_ms(1);
	  lcdSetEntryMode(0,LCD_INCREMENT,LCD_CURSORMOVE);
		_delay_ms(1);
	  twiStop();
  }
}
