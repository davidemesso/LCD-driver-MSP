#ifndef LCD_H
#define LCD_H

#include "io430.h"

// Consts to control data bits
#define DATABITS BIT0|BIT1|BIT2|BIT3|BIT4|BIT5|BIT6|BIT7
#define DATADIR  P3DIR
#define DATAOUT  P3OUT

// Consts to control mode ( data | instruction )
#define MODEDIR P4DIR
#define MODEOUT P4OUT
#define MODESEL BIT0

// Consts to control enable pin
#define ENDIR   P4DIR
#define ENOUT   P4OUT
#define ENBIT   BIT1

typedef enum Bool { FALSE, TRUE } Bool;

void initLCD(void);
void setupLCD(Bool displayOn, Bool showCursor, Bool blinkCursor);
void clearLCD(void);
void sendCommand(unsigned char c);
void sendChar(char c);
void sendString(char* s);
void moveCursor(Bool screen, Bool left);
void sendEnableCycle(void);

#endif