#include "LCD.h"

void initLCD(void)
{
  DATADIR |= DATABITS; 
  MODEDIR |= MODESEL;
  ENDIR   |= ENBIT;
}

void setupLCD(Bool displayOn, Bool showCursor, Bool blinkCursor)
{
  MODEOUT &= ~MODESEL;
  unsigned char start = BIT3;    // Command for start      00001xxx
  
  if(displayOn)
    start |= BIT2;              // Command for display on 000011xx
  
  if(showCursor)                // Command for cursor on  00001x1x
    start |= BIT1;      
  
  if(blinkCursor)               // Command for blink on   00001xx1
    start |= BIT0;
  
  //sendCommand(start);
  //sendEnableCycle();
}

void sendCommand(unsigned char c)
{}


void sendEnableCycle(void)
{
  ENOUT |= ENBIT;
  ENOUT &= ~ENBIT;
  ENOUT |= ENBIT;
  ENOUT &= ~ENBIT;
}