#ifndef I2CDISPLAY_H
#define I2CDISPLAY_H

//typedef uint8_t bool;
//#define true 1;
//#define false 0;
#include <stdbool.h>
#include "../i2c/i2c.h"

#define RSPIN 0
#define RWPIN 1
#define EPIN 2
#define BLPIN 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7

#define LCD_BLINKBIT 0
#define LCD_CURSORBIT 1
#define LCD_DISPLAYONBIT 2
#define LCD_DLBIT 4
#define LCD_LINEBIT 3
#define LCD_FONTBIT 2
#define LCD_IDBIT 1
#define LCD_SBIT 0

#define LCD_COMMANDREG false 
#define LCD_DATAREG true

#define LCD_TWOLINES true
#define LCD_ONELINE  false

#define LCD_SMALLFONT false
#define LCD_BIGFONT true

#define LCD_READ true
#define LCD_WRITE false

#define LCD_EIGHTMODE true
#define LCD_FOURMODE false

#define LCD_INCREMENT 1
#define LCD_DECREMENT 0

#define LCD_DISPLAYSHIFT 1
#define LCD_CURSORMOVE 0

void lcdInit(uint8_t);
void lcdWrite(bool, uint8_t);
void lcdWriteB(uint8_t,bool,uint8_t);
void lcdWriteByte(uint8_t, bool, uint8_t);
void lcdSetFunction(uint8_t, bool, bool, bool);
void lcdClear(uint8_t);
void lcdSetOn(uint8_t, bool, bool, bool);
void lcdSetCGAddr(uint8_t, uint8_t);
void lcdSetDDAddr(uint8_t, uint8_t);
void lcdReturnHome(uint8_t);
void lcdSetEntryMode(uint8_t, bool, bool);

#endif
