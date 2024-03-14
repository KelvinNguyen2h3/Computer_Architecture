#ifndef _timer0_h_
#define _timer0_h_

void timer0_init(void);
void timer0_SetCounter(unsigned int value);
unsigned int timer0_GetCounter(void);
void timer0_Run(unsigned char Flag);

#endif