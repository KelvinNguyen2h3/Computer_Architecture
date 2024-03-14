#include <REGX52.H>

void exint0_init(void)
{
    IT0=1;
    IE0=0;
    EX0=1;
    EA=1;
    PX0=1;
}