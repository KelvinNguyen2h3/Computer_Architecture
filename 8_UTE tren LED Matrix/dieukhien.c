#include <REGX52.H>
#include "delay100ms.h"

#define matrixled_col P0

sbit SER = P3^4; //74HC595
sbit RCK = P3^5;
sbit SCK = P3^6;


void hc74595_wrbyte(unsigned char byte)
{
    unsigned char i;
    for(i=0;i<8;i++)
    {
        SER = byte & (0x80>>i);
        SCK = 1;
        SCK = 0;
    }
    RCK = 1;
    RCK = 0;
}


void matrix_khoitao()
{
    SCK = 0;
    RCK = 0;
}


void matrix_show(unsigned char column,dat)
{
    hc74595_wrbyte(dat);
    matrixled_col = ~(0x80>>column);
    delay100ms(7);
    matrixled_col = 0xff;
}