#include <reg51.h>
#include "stdutils.h"
#include "nec_ir.h"
#include "XPT2046.h"

sbit LED1=P2^0;
sbit LED2=P2^1;
sbit LED3=P2^2;
sbit LED4=P2^3;
sbit LED5=P2^4;
sbit LED6=P2^5;
sbit LED7=P2^6;
sbit LED8=P2^7;
sbit DIGIT_1 = P2^2;
sbit DIGIT_2 = P2^3;
sbit DIGIT_3 = P2^4;
typedef unsigned int     u16;
typedef unsigned int    u8;
 
#define KEY_MATRIX_PORT     P1
#define SMG_SEG_PORT        P0

u8 gsmg_code[16]={0x00,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
                 0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
void displayDigit(unsigned char digit) {
    switch (digit) {
        case 0: P0 = 0x00; break; 
        case 1: P0 = 0x06; break;
        case 2: P0 = 0x5b; break;
        case 3: P0 = 0x4f; break;
        case 4: P0 = 0x66; break;
        case 5: P0 = 0x6d; break;
        case 6: P0 = 0x7d; break;
        case 7: P0 = 0x07; break;
        case 8: P0 = 0x7f; break;
        case 9: P0 = 0x6f; break;
        default: P0 = 0x00; break;
    }
}

void delay_10us(int ten_us)
{
     while(ten_us--);
} 

int key_matrix_ranks_scan(int key)
{
u8 key_value;
     KEY_MATRIX_PORT=0xf7;
     if(KEY_MATRIX_PORT!=0xf7)
     {
          delay_10us(1000);
         switch(KEY_MATRIX_PORT)
			{
             case 0x77: key_value=8;break;
             case 0xb7: key_value=5;break;
             case 0xd7: key_value=2;break;
             case 0xe7: key_value=1;break;
         }
     }
    KEY_MATRIX_PORT=0xfb;
     if(KEY_MATRIX_PORT!=0xfb)
     {
          delay_10us(1000);
     switch(KEY_MATRIX_PORT)
         {
             case 0x7b: key_value=9;break;
             case 0xbb: key_value=6;break;
             case 0xdb: key_value=3;break;
             case 0xeb: key_value=14;break;
        }
     }

     KEY_MATRIX_PORT=0xfd;
     if(KEY_MATRIX_PORT!=0xfd)
			 {
          delay_10us(1000);
         switch(KEY_MATRIX_PORT)
         {
             case 0x7d: key_value=10;break;
             case 0xbd: key_value=7;break;
             case 0xdd: key_value=4;break;
             case 0xed: key_value=15;break;
         }
     }
     KEY_MATRIX_PORT=0xfe;
if(KEY_MATRIX_PORT!=0xfe || key != 0)
     {
          delay_10us(1000);
					key_value=12;
     }
     return key_value;
	 }

void main()
{
	
	  uint temp,count1;
    uint32_t key;
		u8 k;
		u8 count=0;
		u8 ledState1 = 0;
		u8 ledState2 = 0;
		u8 ledState3 = 0;
		u8 ledState4 = 0;
		u8 ledState5 = 0;
		u8 ledState6 = 0;
		u8 ledState7 = 0;
		u8 ledState8 = 0;
    IR_RemoteInit();
    while(1)
    {
			if(count1==50)
	  {
			count1=0; 
			temp = Read_AD_Data(0xA4);	
	  }
	  count1++;
			if (temp < 70)
					{
						P2 = 0x00;
					}
				key = IR_RemoteGetKey();
        switch(key)
        {
					case IR_CODE_1: 
                        if (ledState1 == 0) {
                            displayDigit(1); 
                            DIGIT_1 = 1; 
                            DIGIT_2 = 1; 
                            DIGIT_3 = 1; 
                            ledState1 = 1;
                        } else {
                            displayDigit(0);
                            ledState1 = 0;
                        }
                        break;
					case IR_CODE_2: 
                        if (ledState2 == 0) {
                            displayDigit(2); 
                            DIGIT_1 = 0; 
                            DIGIT_2 = 1; 
                            DIGIT_3 = 1; 
                            ledState2 = 1;
                        } else {
                            displayDigit(0); 
                            ledState2 = 0;
                        }
                        break;
					case IR_CODE_3: 
                        if (ledState3 == 0) {
                            displayDigit(3); 
                            DIGIT_1 = 1; 
                            DIGIT_2 = 0; 
                            DIGIT_3 = 1; 
                            ledState3 = 1;
                        } else {
                            displayDigit(0);
                            ledState3 = 0;
                        }
                        break;
					
												
					case IR_CODE_4: 
                        if (ledState4 == 0) {
                            displayDigit(4); 
                            DIGIT_1 = 0; 
                            DIGIT_2 = 0; 
                            DIGIT_3 = 1; 
                            ledState4 = 1;
                        } else {
                            displayDigit(0); 
                            ledState4 = 0;
                        }
                        break;
					case IR_CODE_5: 
                        if (ledState5 == 0) {
                            displayDigit(5);
                            ledState5 = 1;
                        } else {
                            displayDigit(0); 
                            DIGIT_1 = 0; 
                            DIGIT_2 = 0; 
                            DIGIT_3 = 0; 
                            ledState5 = 0;
                        }
                        break;
					case IR_CODE_6: 
                        if (ledState6 == 0) {
                            displayDigit(6); 
                            DIGIT_1 = 0; 
                            DIGIT_2 = 1; 
                            DIGIT_3 = 0; 
                            ledState6 = 1;
                        } else {
                            displayDigit(0);
                            ledState6 = 0;
                        }
                        break;
					case IR_CODE_7: 
                        if (ledState7 == 0) {
                            displayDigit(7); 
                            DIGIT_1 = 1; 
                            DIGIT_2 = 0; 
                            DIGIT_3 = 0; 
                            ledState7 = 1;
                        } else {
                            displayDigit(0);
                            ledState7 = 0;
                        }
                        break;
					case IR_CODE_8: 
                        if (ledState8 == 0) {
                            displayDigit(8); 
                            DIGIT_1 = 0; 
                            DIGIT_2 = 0; 
                            DIGIT_3 = 0; 
                            ledState8 = 1;
                        } else {
                            displayDigit(0);
                            ledState8 = 0;
                        }
                        break;
					default: break;
        }
				k = key_matrix_ranks_scan(key);
				switch(k-1)
        {
					case 1: displayDigit(1); DIGIT_1 = 1; DIGIT_2 = 1; DIGIT_3 = 1; break;
					case 2: displayDigit(2); DIGIT_1 = 0; DIGIT_2 = 1; DIGIT_3 = 1; break;
					case 3: displayDigit(3); DIGIT_1 = 1; DIGIT_2 = 0; DIGIT_3 = 1; break;
					case 4: displayDigit(4); DIGIT_1 = 0; DIGIT_2 = 0; DIGIT_3 = 1; break;
					case 5: displayDigit(5); DIGIT_1 = 1; DIGIT_2 = 1; DIGIT_3 = 0; break;
					case 6: displayDigit(6); DIGIT_1 = 0; DIGIT_2 = 1; DIGIT_3 = 0; break;
					case 7: displayDigit(7); DIGIT_1 = 1; DIGIT_2 = 0; DIGIT_3 = 0; break;
					case 8: displayDigit(8); DIGIT_1 = 0; DIGIT_2 = 0; DIGIT_3 = 0; break;
					case 9: LED1=1; LED2=1; LED3=1; LED4=1; LED5=1; LED6=1; LED7=1; LED8=1; break;
					default: break;
        }
    }		
}	  
