#include <reg51.h>

void Delay(void);

void main(void)
{
    while (1)
    {
        P1 = 0x55;  // Send 0x55 to P1 (binary: 01010101)
        Delay();   // Delay
        P1 = 0xAA;   // Send 0xAA to P1 (binary: 10101010)
        Delay();   // Delay
    }
}

void Delay()
{
    TMOD = 0x01;      // Timer 0 in mode 1 (16-bit mode)
    TL0 = 0x00;       // Initialize low byte of Timer 0
    TH0 = 0x35;       // Initialize high byte of Timer 0 for the required delay
    TR0 = 1;          // Start Timer 0

    // Wait for the overflow flag (TF0) to be set
    while (TF0 == 0); // Wait until TF0 is set (Timer 0 overflow)

    TR0 = 0;          // Stop Timer 0
    TF0 = 0;          // Clear the overflow flag
}
