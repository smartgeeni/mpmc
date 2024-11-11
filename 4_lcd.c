#include <htc.h>
#define _XTAL_FREQ 20000000  // Set crystal frequency
__CONFIG(0x1F7A);
#define LCD_DATA PORTB       // Define LCD data pins
#define RS RD6               // Define RS pin
#define EN RD7               // Define EN pin

void lcd_cmd(char cmd);
void lcd_data(char data);

void main() {
    TRISB = 0x00;              // Configure PORTB as output for LCD
    TRISD6 = 0; TRISD7 = 0;    // Set RS and EN as outputs

    lcd_cmd(0x38);             // 2-line, 5x7 matrix
    lcd_cmd(0x01);             // Clear display
    lcd_cmd(0x0C);             // Display ON, Cursor OFF

    // Print "EEE" as a string
    char str[] = "EEE";        // String to display
    while (*str) {
        lcd_data(*str++);      // Display each character in the string
    }

    while(1);                  // Infinite loop
}

void lcd_cmd(char cmd) {
    LCD_DATA = cmd;
    RS = 0; EN = 1;            // Command mode
    __delay_ms(20);
    EN = 0;
}

void lcd_data(char data) {
    LCD_DATA = data;
    RS = 1; EN = 1;            // Data mode
    __delay_ms(20);
    EN = 0;
}
