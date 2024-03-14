#include <REGX52.H>
#include <intrins.H>

void delay100ms(unsigned int x)
{
    unsigned char i;
    while(x--)
    {
        _nop_();
        i = 43;
        while (--i);
    }
}