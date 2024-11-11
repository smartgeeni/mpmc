#include <reg51.h>
#include <string.h>
#include <stdio.h>
unsigned char c;
void serial_init()
{
TMOD = 0X20;
TH1 = 0XFD;
TI = 1;
TR1 = 1;
SCON = 0X53;
}
void delay(int m)
{
int i,j;
for (i=0; i<m; i++)
for (j=0; j<m; j++);
}
void main()
{
serial_init();
while(1)
{
RI = 0;
while(RI == 0);
c = SBUF;
TI = 0;
SBUF = c;
while(TI == 0);
}
}
