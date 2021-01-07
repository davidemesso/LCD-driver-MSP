//#include "io430.h"
//#include "LCD.h"
//
//int main( void )
//{
//  // Stop watchdog timer to prevent time out reset
//  WDTCTL = WDTPW + WDTHOLD;
//
//  initLCD();
//  setupLCD(TRUE, TRUE, TRUE);
//  
//  P3OUT |= (BIT3 | BIT2 | BIT1 | BIT0);
//  sendEnableCycle();
//// &= ~ in 
//// |= out
//  
//  return 0;
//}

#include "io430.h"
#define DR P2OUT = P2OUT | BIT0 // define RS high
#define CWR P2OUT = P2OUT & (~BIT0) // define RS low
#define READ P2OUT = P2OUT | BIT2 // define Read signal R/W = 1 for reading
#define WRITE P2OUT = P2OUT & (~BIT2) // define Write signal R/W = 0 for writing
#define ENABLE_HIGH P2OUT = P2OUT | BIT3 // define Enable high signal
#define ENABLE_LOW P2OUT = P2OUT & (~BIT3) // define Enable Low signal
unsigned int i;
unsigned int j;
void delay(unsigned int k)
{
for(j=0;j<=k;j++)
{
for(i=0;i<1000;i++);

}

}
void data_write(void)
{
ENABLE_HIGH;
delay(2);
ENABLE_LOW;
}

void data_read(void)
{
ENABLE_LOW;
delay(2);
ENABLE_HIGH;
}

void check_busy(void)
{
P3DIR &= ~(BIT7); // make P2.3 as input
while((P3IN&BIT7)==1)
{
data_read();
}
P3DIR |= BIT7; // make P2.3 as output
}

void send_command(unsigned char cmd)
{
check_busy();
WRITE;
CWR;
P3OUT = (P3OUT & 0x00)|(cmd);
data_write(); // give enable trigger

}

void send_data(unsigned char data)
{
check_busy();
WRITE;
DR;
P3OUT = (P3OUT & 0x00)|(data);
data_write(); // give enable trigger
}

void send_string(char *s)
{
while(*s)
{
send_data(*s);
s++;
}
}

void lcd_init(void)
{
P2DIR |= 0xFF;
P3DIR |= 0xFF;
P2OUT &= 0x00;
P3OUT &= 0x00;
send_command(0x0C);
send_command(0xF0); // display on cursor on
}

void main(void)
{
WDTCTL = WDTPW + WDTHOLD; // stop watchdog timer
lcd_init();
send_string("Manpreet Singh");
send_command(0xC0);
send_string("Minhas");
while(1){}
}