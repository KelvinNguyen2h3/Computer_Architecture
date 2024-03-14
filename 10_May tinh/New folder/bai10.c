#include "reg52.h"

typedef unsigned int     u16;
typedef unsigned char    u8;
 
#define KEY_MATRIX_PORT     P1
#define SMG_SEG_PORT        P0

u8 gsmg_code[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
                 0x7f,0x6f,0x3f,0x7c,0x39,0x46,0x40,0x48};



void delay_10us(u16 ten_us)
{
     while(ten_us--);
} 

u8 key_matrix_ranks_scan(void)
{
u8 key_value=0;

     KEY_MATRIX_PORT=0xf7;
     if(KEY_MATRIX_PORT!=0xf7)
     {
          delay_10us(1000);
         switch(KEY_MATRIX_PORT)
    {
             case 0x77: key_value=1;break;
             case 0xb7: key_value=4;break;
             case 0xd7: key_value=7;break;
             case 0xe7: key_value=10;break;
         }
     }
     while(KEY_MATRIX_PORT!=0xf7);

    KEY_MATRIX_PORT=0xfb;
     if(KEY_MATRIX_PORT!=0xfb)
     {
          delay_10us(1000);
     switch(KEY_MATRIX_PORT)
         {
             case 0x7b: key_value=2;break;
             case 0xbb: key_value=5;break;
             case 0xdb: key_value=8;break;
             case 0xeb: key_value=13;break;//+
        }
     }
    while(KEY_MATRIX_PORT!=0xfb); 

     KEY_MATRIX_PORT=0xfd;
     if(KEY_MATRIX_PORT!=0xfd)
			 {
          delay_10us(1000);
         switch(KEY_MATRIX_PORT)
         {
             case 0x7d: key_value=3;break;
             case 0xbd: key_value=6;break;
             case 0xdd: key_value=9;break;
             case 0xed: key_value=14;break;//-
         }
     }
     while(KEY_MATRIX_PORT!=0xfd);
 
     KEY_MATRIX_PORT=0xfe;
     if(KEY_MATRIX_PORT!=0xfe)
     {
          delay_10us(1000);
         switch(KEY_MATRIX_PORT)
         {
             //case 0x7e: key_value=4;break;
             //case 0xbe: key_value=7;break;
             //case 0xde: key_value=12;break;
             case 0xee: key_value=15;break;//=
         }
     }
     while(KEY_MATRIX_PORT!=0xfe);


     return key_value;
 }
 
 
 
 
 void main()
 {
      u8 key=0;
     while(1)
     {
          key=key_matrix_ranks_scan();
         if(key!=0)
             SMG_SEG_PORT=gsmg_code[key];
     }
}