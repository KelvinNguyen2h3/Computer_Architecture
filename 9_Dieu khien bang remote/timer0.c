#include <REGX52.H>


void timer0_init(void)
{
    TMOD &= 0xF0;
    TMOD |= 0x01;
    TL0 = 0;
    TH0 = 0;
    TF0 = 0;
    TR0 = 0;
}

void timer0_SetCounter(unsigned int value)
{
    TH0=value/256;
    TL0=value%256;
}

unsigned int timer0_GetCounter(void)
{
    return (TH0<<8)|TL0;
}

void timer0_Run(unsigned char Flag)
{
    TR0=Flag;
}