#include "i2cdisplay.h"

/*
     Pinbelegung
     Bit  -  Display
     
     0  -  RS
     1  -  RW
     2  -  E
     3  -  Licht?
     4  -  d4
     5  -  d5
     6  -  d6
     7  -  d7
     */


  MOLCD::MOLCD(){}
  MOLCD::MOLCD(int id,int lines,int chars){
    this->id = id;
    this->lines = lines;
    this->chars = chars;
    setup();
  }

  void MOLCD::setup(){    
    Wire.begin();
    init();
  }
  
  void MOLCD::init(){
    pos=0;
    line=0;
    Wire.beginTransmission (id);
    //init: set 3 times to 8 bit mode
    for(int i=0;i<3;i++){
      Wire.write(0x3C);
      delay(1);
      Wire.write(0x38);
      delay(5); 
    } 
    //set to 4 bit mode
    Wire.write(0x2C);
    delay(1);
    Wire.write(0x28);
    delay(1);
    Wire.endTransmission();       
    //clear display
    clearLCD();
    delay(1);    
    //set functions  
    setFunc(0,1,1);     
    delay(1);
    //set on
    setOn(1,0,1);
    delay(1);   
    //set mode
    setMode(1,0);
    delay(1);
  }

  void MOLCD::setMode(bool curInc, bool pushCont){
    write(0,(4|(curInc<<1)|(pushCont)));
  } 
  
  //on: 1=display on, 0=display off
  //cur: 1=block , 0=underline
  //curOn: 1=on, 0=off
  void MOLCD::setOn(bool on,bool curOn, bool cur){
    write(0,(8 | (on <<  2) | (curOn << 1) | cur)); 
  }
  
  //sets dd-address
  // addr : address 0-0x7F
  void MOLCD::setDDAddr(int addr){
    addr &= 0x7F;
    write(0,0x80|addr);  
  }
  
  
  void MOLCD::clearLCD(){
    write(0,0x01);
    setDDAddr(0x00);
    pos=0;
  }
  
  void MOLCD::chgLine(){
    if(line==0){
      line=1;
      setDDAddr(0x40);
    }
    else{
      line=0;
      setDDAddr(0x00);
    }
    pos=0;
  }

  //iface: 1 = 8bit, 0 = 4bit
  //lines: 1= 2/4 lines, 0 = 1 line
  //font:  1 = 5x10, 0 = 5x7
  void MOLCD::setFunc(bool iface, bool lines, bool font){
    write(0,(32|(iface << 4)|(lines << 3 | font << 2)));
  }

  void MOLCD::writeChar(char c){ 
    this->write(1,c);
    pos++;
    if(pos%chars==0 && pos>0){
      this->write(0,0x02);
      delay(1);
      chgLine();
    }
  }

  // writes a byte to the display
  // cmd: 0= Command-Register, 1 = Data-Register
  void MOLCD::write(bool cmd, char data){
    Wire.beginTransmission(this->id);
    Wire.write((data & 0xf0)|(cmd)|(backlight << 3)|4);
    // Serial.write(((data & 0xf0)|(cmd)|(backlight << 3)|4));
    delay(1);
    Wire.write((data & 0xf0)|(cmd)|(backlight<<3));
    delay(1);
    Wire.write(((data & 0x0f) << 4)|(cmd)|(backlight<<3)|4);
    //  Serial.write(((data & 0x0f) << 4)|(cmd)|(backlight<<3)|4);
    delay(1);
    Wire.write(((data & 0x0f) << 4)|(cmd)|(backlight<<3));
    delay(1);
    Wire.endTransmission();
  }


