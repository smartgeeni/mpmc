#include <htc.h>  // Include the HTC header file

#define _XTAL_FREQ 20000000  // Define the clock frequency as 20 MHz

// Configuration bits for the PIC microcontroller
__CONFIG(0x1F7A);  // Update based on your PIC's datasheet

// ADC Initialization
void ADC_Init() {
    ADCON0 = 0x81;  // Enable ADC and set clock
    ADCON1 = 0xCE;  // Set A/D port configuration
}

// Read ADC value from specified channel (0-7)
unsigned int ADC_Read(unsigned int channel) {
    if (channel > 7) return 0;  // Limit channel range to 0-7
    
    ADCON0 = (ADCON0 & 0xC5) | (channel << 3);  // Select ADC channel
    __delay_ms(2);  // Delay for ADC stability
    
    GODONE = 1;  // Start ADC conversion
    while (GODONE);  // Wait until conversion is complete
    
    return ((ADRESH << 8) + ADRESL);  // Return 10-bit ADC result
}

// PWM Initialization
void PWM_Init(void) {
    TRISC2 = 0;  // Set CCP1 pin as output
    CCP1CON = 0x0C;  // Configure CCP1 module in PWM mode
    PR2 = 0xFF;  // Set the PWM period
    T2CON = 0x01;  // Set Timer2 with prescaler
    PWM_Dutycycle(0);  // Set initial duty cycle to 0
    T2CON |= 0x04;  // Enable Timer2
}

// Set the PWM duty cycle (0-1023 for 10-bit resolution)
void PWM_Dutycycle(unsigned int dutycycle) {
    CCPR1L = dutycycle >> 2;  // Set the 8 MSBs of duty cycle
    CCP1CON &= 0xCF;  // Clear bits 5 and 4
    CCP1CON |= (0x30 & (dutycycle << 4));  // Set the 2 LSBs in CCP1CON
}

// Main function
void main() {
    unsigned int adc_value;

    ADC_Init();  // Initialize ADC
    PWM_Init();  // Initialize PWM

    while (1) {
        adc_value = ADC_Read(0);  // Read ADC value from channel 0
        __delay_ms(2);  // Small delay
        PWM_Dutycycle(adc_value);  // Set PWM duty cycle based on ADC reading
        __delay_ms(2);  // Small delay for stability
    }
}
