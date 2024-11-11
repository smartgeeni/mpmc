#include<htc.h> // Header File
#define _XTAL_FREQ 20000000 // Device Crystal Frequency
__CONFIG(0x1F7A); // Configuration Bits refer Datasheet
#define lcd PORTB // Assign LCD_Data_Pins as PORTB
#define RS RD6 // Assign LCD_RS_Pin as PORTD_RD6Pin
#define EN RD7 // Assign LCD_EN_Pin as PORTD_RD7 
unsigned int b,c,d,e,f,g,h,i,j,k;
void cmd(char );
void LCD_Init();
void ADC_Init()
{
ADCON0 = 0x81; // Configure the Clock Conversion, 
//ADCChannel,A/D Module
ADCON1 = 0xCE; // Configure the A/D Port Configuration ControlBits
}
unsigned int ADC_Read(unsigned char Channel)
{
if(Channel>7) // Select the ADC Channel
return 0;
__delay_ms(2);
GODONE = 1; // Set Go/DONE Bit
while(GODONE); // Wait for AD Conversion to complete the
//process
return((ADRESH<<8)+ADRESL); // Read AD Result Register Pair
}
void LCD_Init()
{
RS = 0; // Command Mode
cmd(0x38); // Command for 2Lines 5x7 dots
cmd(0x0C); // Command for Display On Cursor Off
cmd(0x06); // Command for Increment Cursor Position
cmd(0x80); // Command for Position(0,0)RS=1; //Data Mode
}
void cmd(char s)
{
lcd = s;
EN = 1;
__delay_ms(20);
EN = 0;
}
void main()
{
unsigned int a;
TRISA = 0x01; // Assign PORTA_AN0 Pin as Analog Input
TRISB = 0x00; // Configure LCD_Data_Pins as Output
TRISD = 0x00; // Configure LCD_RS,LCD_EN Pin as Output
PORTA = 0x00;
PORTB = 0x00;
PORTD = 0x00;
LCD_Init();
ADC_Init();
do
{
a = ADC_Read(0);
PORTB = a;
b = a/10;
c = a%10;
d = b/10;
e = b%10;
f = d/10;
g = d%10;
RS = 0;
cmd(0x80);
RS = 1;
h = f+0x30;
cmd(h);
i = g+0x30;
cmd(i);
j = e+0x30;
cmd(j);
k = c+0x30;
cmd(k);
__delay_ms(100);
}
while(1);
}
