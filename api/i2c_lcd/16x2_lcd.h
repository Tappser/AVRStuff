#include "i2cdisplay.h"

#define LCD_CHARS 16 // 16  Zeichen, von 0 bis 15;

uint8_t lcd_x, lcd_y;
void lcd1602_FillLine(uint8_t);
void lcd1602_Init(uint8_t);
void lcd1602_WriteChar(uint8_t, char);
void lcd1602_SwitchLine(uint8_t);
void lcd1602_WriteString(uint8_t, char*);
void lcd1602_Clear(uint8_t);
