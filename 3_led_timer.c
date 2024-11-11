#include <htc.h> // Header File

#define _XTAL_FREQ 20000000 // Device Crystal Frequency
__CONFIG(0x1F7A); // Configuration Bits refer to Datasheet

void main()
{
    ADCON1 = 0x06; // Change PORTA to Digital
    CMCON = 0x07;  // Disable Analog Comparator

    // Configure all ports as output
    TRISA = 0x00;
    TRISB = 0x00;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;

    // Initialize all ports to 0
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;

    while (1)
    {
        // Toggle all ports
        PORTA = ~PORTA;
        PORTB = ~PORTB;
        PORTC = ~PORTC;
        PORTD = ~PORTD;
        PORTE = ~PORTE;

        __delay_ms(500); // 500 ms delay
    }
}
