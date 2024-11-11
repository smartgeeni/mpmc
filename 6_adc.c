#include <htc.h>               // Header File
#define _XTAL_FREQ 20000000    // Device Crystal Frequency

__CONFIG(0x1F7A);              // Configuration bits for PIC16F877A

#define lcd PORTB              // Assign LCD data pins to PORTB
#define RS RD6                 // Assign LCD RS pin to RD6
#define EN RD7                 // Assign LCD EN pin to RD7

void cmd(char command);        // Function prototype for sending commands
void LCD_Init();               // Function prototype for LCD initialization
void ADC_Init();               // Function prototype for ADC initialization
unsigned int ADC_Read(unsigned char channel);  // Function prototype for ADC read

void main() {
    unsigned int adc_result;
    unsigned int thousands, hundreds, tens, units;
    
    TRISA = 0x01;             // Configure RA0 as analog input
    TRISB = 0x00;             // Set PORTB as output for LCD data
    TRISD = 0x00;             // Set PORTD as output for RS and EN
    PORTA = PORTB = PORTD = 0x00;

    LCD_Init();               // Initialize the LCD
    ADC_Init();               // Initialize the ADC

    while(1) {
        adc_result = ADC_Read(0);  // Read ADC value from channel 0

        // Convert the ADC value to individual digits
        thousands = (adc_result / 1000) % 10;
        hundreds  = (adc_result / 100) % 10;
        tens      = (adc_result / 10) % 10;
        units     = adc_result % 10;

        // Display the result on the LCD
        RS = 0;               // Set to command mode
        cmd(0x80);            // Set cursor position to the beginning of the first line
        RS = 1;               // Set to data mode
        
        // Send each digit to LCD
        cmd(thousands + 0x30);  // Thousands place
        cmd(hundreds + 0x30);   // Hundreds place
        cmd(tens + 0x30);       // Tens place
        cmd(units + 0x30);      // Units place

        __delay_ms(100);       // Small delay before next update
    }
}

void LCD_Init() {
    RS = 0;                  // Command mode
    cmd(0x38);               // 2-line, 5x7 matrix
    cmd(0x0C);               // Display ON, Cursor OFF
    cmd(0x06);               // Entry mode set, cursor moves right
    cmd(0x01);               // Clear display
}

void cmd(char command) {
    lcd = command;
    EN = 1;
    __delay_ms(2);
    EN = 0;
}

void ADC_Init() {
    ADCON0 = 0x81;           // Enable ADC, set clock conversion
    ADCON1 = 0xCE;           // Set PORT configuration
}

unsigned int ADC_Read(unsigned char channel) {
    if (channel > 7) return 0;  // Ensure channel is valid

    ADCON0 &= 0xC5;             // Clear the channel selection bits
    ADCON0 |= (channel << 3);   // Set the desired channel
    __delay_ms(2);              // Acquisition time

    GODONE = 1;                 // Start conversion
    while (GODONE);             // Wait until conversion is complete

    return ((ADRESH << 8) + ADRESL);  // Return 10-bit ADC result
}
