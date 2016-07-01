#include "16x2_lcd.h"
#include <util/delay.h>

void lcd1602_Init(uint8_t id){
  lcdInit(id);
  lcd_x=1;
  lcd_y=0;
}

void lcd1602_WriteChar(uint8_t id,char c){
  lcdWriteB(id,LCD_DATAREG,c);
  lcd_x++;
  if(lcd_x==LCD_CHARS){
    lcd1602_SwitchLine(id);
  }
  _delay_us(50);
}

void lcd1602_FillLine(uint8_t id){
  while(lcd_x > 1){
    lcd1602_WriteChar(id, ' ');
  }
}

void lcd1602_SwitchLine(uint8_t id){
  lcd_x=1;
  if(lcd_y==0){
    lcdSetDDAddr(id,0x40);
    lcd_y=1;
  }else{
  lcd_y=0;
  lcdSetDDAddr(id,0x00);
  }
  _delay_us(100);
} 

void lcd1602_WriteString(uint8_t id,char* string){
  twiStart((id<<1));
  _delay_us(100);
  uint8_t i=0;
  while(string[i] != '\0'){
    lcd1602_WriteChar(0,string[i]);
    i++;
  }
  twiStop();
}

void lcd1602_Clear(uint8_t id){
  lcd_x=1;
  lcd_y=0;
  lcdClear(id);
  _delay_us(200);
}
