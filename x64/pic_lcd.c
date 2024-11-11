#include <htc.h> // Header File
#define _XTAL_FREQ 20000000 // Device Crystal Frequency
__CONFIG(0x1F7A); // Configuration Bits refer to the Datasheet

#define lcd PORTB // Assign LCD_Data_Pins as PORTB
#define RS RD6 // Assign LCD_RS_Pin as PORTD_RD6 Pin
#define EN RD7 // Assign LCD_EN_Pin as PORTD_RD7 Pin

void cmd(char);
char msg[32] = "KCT EEE DEPARTMENT"; // To Display the text
int d = 0; // Correctly declare the variable type for `d`

void main() {
    TRISB = 0; // Configure LCD_Data_Port as Output
    TRISD6 = 0; // Configure LCD_RS_Pin as Output
    TRISD7 = 0; // Configure LCD_EN_Pin as Output
    PORTB = 0;
    RS = 0;
    EN = 0; // Changed from RD7 to EN
    __delay_ms(100); // Added delay for initialization

    // Initialization commands for the LCD
    cmd(0x38); // Command for 2 Lines 5x7 dots
    cmd(0x01); // Command for Clear Screen
    cmd(0x0C); // Command for Display On Cursor Off
    cmd(0x06); // Command for Increment Cursor Position

    while(1) {
        RS = 0; // Command Mode
        cmd(0x80); // Command for Position (0,0)
        RS = 1; // Data Mode
        
        for(d = 0; d < 16; d++) {
            cmd(msg[d]); // Text Display
        }
        
        RS = 0; // Command Mode
        cmd(0xC0); // Command for Position (1,0) - corrected from 0xC3
        RS = 1; // Data Mode
        
        for(d = 16; d < 32; d++) { // Changed to 32 to avoid out of bounds
            cmd(msg[d]); // Text Display
        }
    }
}

void cmd(char s) {
    lcd = s; // Write command/data to the LCD data port
    EN = 1; // Enable the LCD
    __delay_ms(30); // Wait for the command to execute
    EN = 0; // Disable the LCD
}
