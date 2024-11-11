#include <reg51.h>

void main(void)
{
    unsigned int i;  // Variable for delay loop

    // Infinite loop to repeat the LED toggle forever
    for (;;)
    //while(1)
    {
        P1 = 0x55;  // Set P1 to 0x55 (binary 01010101)
        // Create delay by looping 40000 times
        for (i = 0; i < 40000; i++);  

        P1 = 0xAA;  // Set P1 to 0xAA (binary 10101010)
        // Create delay by looping 40000 times
        for (i = 0; i < 40000; i++);
    }
}
