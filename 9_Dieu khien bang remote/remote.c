#include <REGX52.H>
#include "timer0.h"
#include "exint0.h"

unsigned int     IR_time;
unsigned char     IR_state;
unsigned char     IR_data[4];
unsigned char    IR_pdata;

unsigned char     IR_dataflag;
unsigned char     IR_repeatflag;
unsigned char     IR_address;
unsigned char     IR_command;

void IR_init(void)
{
    exint0_init();
    timer0_init();
}

unsigned char IR_getdataflag(void)
{
    if(IR_dataflag)
    {
        IR_dataflag=0;
        return 1;
    }
    else
        return 0;
}


unsigned char IR_getrepeatflag(void)
{
    if(IR_repeatflag)
    {
        IR_repeatflag=0;
        return 1;
    }
    else
        return 0;
}

unsigned char IR_getaddress(void)
{
    return IR_address;
}


unsigned char IR_getcommand(void)
{
    return IR_command;
}


void int0_routine(void) interrupt 0
{
    if(IR_state==0)
    {
        timer0_SetCounter(0);
        timer0_Run(1);
        IR_state=1;
    }
    else if(IR_state==1)
    {
        IR_time=timer0_GetCounter();
        timer0_SetCounter(0);
        if(IR_time>12442-500 && IR_time<12442+500)
        {
            IR_state=2;
        }
        else if(IR_time>10368-500 && IR_time<10368+500)
        {
            IR_repeatflag=1;
            timer0_Run(0);
            IR_state=0;
        }
        else  IR_state=1;
    }
    else if(IR_state==2)
    {
        IR_time=timer0_GetCounter();
        timer0_SetCounter(0);
        if(IR_time>1032-500 && IR_time<1032+500)
        {
            IR_data[IR_pdata/8] &= ~(0x01<<(IR_pdata%8));
            IR_pdata++;
        }
        else if(IR_time>2074-500 && IR_time<2074+500)
        {
            IR_data[IR_pdata/8] |= (0x01<<(IR_pdata%8));
            IR_pdata++;
        }
    }
    else
    {
        IR_pdata=0;
        IR_state=1;
    }
    if(IR_pdata>=32)
    {
        IR_pdata=0;
        if((IR_data[0]==~IR_data[1])&&(IR_data[2]==~IR_data[3]))    
        {
            IR_address=IR_data[0];
            IR_command=IR_data[2];
            IR_dataflag=1;
        }
        timer0_Run(0);
        IR_state=0;
    }        
}