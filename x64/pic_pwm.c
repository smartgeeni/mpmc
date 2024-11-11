#include<htc.h> //Header File
#define _XTAL_FREQ 20000000 //Device Crystal Frequency
__CONFIG(0x1F7A); //Configuration Bits refer Datasheetvoid
ADC_Init()
{
ADCON0 = 0x81; //Configure the Clock Conversion, ADC Channel,A/D Module
ADCON1 = 0xCE; //Configure the A/D Port Configuration Control Bits
}
unsigned int ADC_Read(unsigned int Channel)
{
if(Channel>7) // Select the ADC Channel AN0return 0;
__delay_ms(2);
GODONE = 1; // Set Go/DONE Bit
while(GODONE); // Wait for AD Conversion to complete the process
return((ADRESH<<8)+ADRESL); // Read AD Result Register Pair
}
void PWM_Init(void);
void PWM_Dutycycle(unsigned int );void
main()
{
TRISC2 = 0; //Configure CCP1 Module as Output
RC2 = 0;
ADC_Init(); //ADC Initilization
PWM_Init(); //PWM Initilization
unsigned int a = 0;
while(1)
{
a = ADC_Read(0); //Read ADC_Value
__delay_ms(2);
PWM_Dutycycle(a); //PWM Dutycycle
__delay_ms(2);
}
}
void PWM_Init(void)
{
TRISC2 = 0;
CCP1CON = 0x0C; // Configure PWM Mode
PR2 = 0xFF; // Configure Period Register Maximum
T2CON = 0x01; // Prescaler
PWM_Dutycycle(0); // Set PWM_Dutycycle zero
T2CON |= 0x04; // Enable Timer 2
}
void PWM_Dutycycle(unsigned int Dutycycle)
{
CCPR1L = Dutycycle>>2; // MSB 8bits in CCPR1L
CCP1CON & = 0xCF; // Clear bits 5 and 4
CCP1CON | =(0x30&(Dutycycle<<4)); // Last 2 LSBs to CCP1CON
}
