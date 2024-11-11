#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(0x1F7A);

#define seg PORTB
const char num[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void main() {
    TRISB = 0x00;
    PORTB = 0x00;

    while(1) {
        for(int a = 0; a < 10; a++) {
            seg = num[a];
            __delay_ms(1000);
        }
    }
}
