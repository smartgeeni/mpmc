#include<htc.h> // Header File
#define _XTAL_FREQ 20000000 // Device Crystal Frequency
 __CONFIG(0x1F7A); // Configuration Bits refer Datasheet forPIC16F877A
#define seg PORTB //Assign Seg as PORTB char 
num[10]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
unsigned int a;void main()
{
TRISB = 0x00; //Configure PORTB_Segment_Data as Output
TRISD7 = 0; //Configure PORTD_ as Output
TRISD6 = 0;
TRISD5 = 0;
TRISD4 = 0;
 PORTB = 0x00; //Initial PORT Values are Zero.
RD7 = 0;
 RD6 = 0;
 RD5 = 0;
RD4 = 0; 
 PORTB = 0xFF; //For Segment Testing assign High
PORTD = 0xF0;
 __delay_ms(500);
 PORTB = 0x00;
 __delay_ms(500);while(1)
{
for(a=0; a<10; a++)
{
seg = num[a];
__delay_ms(1000);
}
}
}
