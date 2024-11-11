#include <reg51.h>
#include <string.h>
#include <stdio.h>

unsigned char c;

void serial_init()
{
    TMOD = 0x20;
    TH1 = 0xFD;
    TL1 = 0xFD;
    TI = 1;
    TR1 = 1;
    SCON = 0x53;
}

void delay(int m)
{
    int i, j;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < m; j++)
        {
        }
    }
}

void main()
{
    serial_init();
    while (1)
    {
        RI = 0;
        while (RI == 0);
        c = SBUF;
        TI = 0;
        SBUF = c;
        while (TI == 0);
    }
}
