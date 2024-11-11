#include<htc.h> //Header File
#define _XTAL_FREQ 20000000 //Device Crystal Frequency
__CONFIG(0x1F7A); //Configuration Bits refer Datasheetvoid
main()
{
ADCON1 = 0x06; //Changes PORT A to Digital
CMCON = 0x07; //Disable Analog Comparator
TRISA = 0x00; //Configure PORT A as Output
TRISB = 0x00; //Configure PORT B as Output
TRISC = 0x00; //Configure PORT C as Output
TRISD = 0x00; //Configure PORT D as Output
TRISE = 0x00; //Configure PORT E as Output
PORTA = 0;
PORTB = 0;
PORTC = 0;
PORTD = 0;
PORTE = 0;
while(1)
{ PORTA =~ PORTA;
PORTB =~ PORTB;
PORTC =~ PORTC; //Toggle the All PORTS
PORTD =~ PORTD;
PORTE =~ PORTE;
__delay_ms(500); //Delay 500 milliseconds
}
}
