#include <reg51.h>
void serial_init();
unsigned char c;

void main() {
    serial_init();
    
    while(1) {
        while (RI == 0); // Wait for reception
        c = SBUF;        // Read received byte
        RI = 0;          // Clear receive interrupt flag
        
        SBUF = c;        // Transmit received byte
        while (TI == 0); // Wait for transmission
        TI = 0;          // Clear transmit interrupt flag
    }
}

void serial_init() {
    TMOD = 0x20; // Timer mode select
    TH1 = 0xFD;  // Baud rate select for 9600 baud
    SCON = 0x50; // Serial mode 1, 8-bit UART, enable receiver
    TR1 = 1;     // Start timer 1
}
