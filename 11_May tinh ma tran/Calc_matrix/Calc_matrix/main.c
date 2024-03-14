#include<main.h>
unsigned char key=0;
void Send_data_cot(unsigned char _data);
sbit SH_CP=P3^6;	//dinh nghia chan SH_CP o P0^0
sbit DS=P3^4;			//dinh nghia chan DS o P0^1
sbit ST_CP=P3^5;	//dinh nghia chan ST_CP o P0^2
//============================khai bao bien va hang==========================//
unsigned char a[80]= {0xFF,0x81,0xBD,0x81,
											0xFF,0xBF,0x81,0xBD,
											0xFF,0xB1,0xB5,0x85,
											0xFF,0x81,0xB5,0xB5,
											0xFF,0x81,0xF7,0xF1,
											0xFF,0x85,0xB5,0xB1,
											0xFF,0x85,0xB5,0x81,
											0xFF,0x81,0xFD,0xFD,
											0xFF,0x81,0xB5,0x81,
											0xFF,0x81,0xB5,0xB1};
unsigned char b[8]= {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};//ma quét COT : C1 den C8, COT nao o gia tri =1 thì COT dó duoc sáng.
unsigned char i=0;
int num = 0;
int num1 = 0;
int cong,tru;
int chuc,donvi;
int main() 
{
		Keypad_Init();
		while(1)
		{
				key = KEY4X4_GetKey();//nhan thu tu phím nhan
				if (key!=0)//phat hien co phim nhan
				{
					switch (key)
					{
						case '0':
							num = num*10 + 0;
							break;

						case '1':
							num = num*10 + 1;							
							break;

						case '2':
							num = num*10 + 2;
							break;

						case '3':
							num = num*10 + 3;
							break;

						case '4':
							num = num*10 + 4;
						 	break;

						case '5':
							num = num*10 + 5;
							break;
		
						case '6':
							num = num*10 + 6;
							break;

						case '7':
							num = num*10 + 7;
							break;
		
						case '8':
							num = num*10 + 8;
							break;

						case '9':
							num = num*10 + 9;
							break;
						
						case '+':
							num1 = num;
							num = 0;
							cong = 1;
							break;

						case '-':
							num1 = num;
							num = 0;
							tru = 1;
							break;

						case '=':
							if (tru == 1) 
								{
									num = num1 - num;
									tru = 0;
								}
							if (cong == 1) 
								{
									num = num1 + num;
									cong = 0;
								}
							break;

						default:
							break;
					}
					key = 0;
					delay_ms(100);
				}
				while (num > 99) {
						num = num/10;
				}					
				chuc = num/10;
				donvi = num%10;
				for(i=0;i<4;i++)//quet COT thu 1 den thu 8, cho COT=1 roi goi du lieu ra cot do
          {
            P0=a[i + donvi*4];      				// goi du lieu tai vi tri o ma tran a[] ra hang 1->8
            Send_data_cot(b[i]);  // goi ma quet ma tran b[] ra COT 1->8
            delay_ms(1);  				// thoi gian quet led
            Send_data_cot(0x00);  // ma quet=0=>tat het LED chong lem
          }
				for(i=4;i<8;i++)//quet COT thu 1 den thu 8, cho COT=1 roi goi du lieu ra cot do
          {
            P0=a[i - 4 + chuc*4];      				// goi du lieu tai vi tri o ma tran a[] ra hang 1->8
            Send_data_cot(b[i]);  // goi ma quet ma tran b[] ra COT 1->8
            delay_ms(1);  				// thoi gian quet led
            Send_data_cot(0x00);  // ma quet=0=>tat het LED chong lem
          }
		}
}

void Send_data_cot(unsigned char _data)
{
unsigned char n,tam;
 
         ST_CP=0;//cho chan ST cua 74HC595 xuong muc 0
         SH_CP=0;//cho chan SH cua 74HC595 xuong muc 0
         DS=0;	//cho chan DS cua 74HC595 xuong muc 0
   for(n=0;n<8;n++)//goi 8 bit lan luoc ra 8 cot
   {
				tam=_data&0x80;
       _data = _data<<1;//dich trai 1 bit de goi bit can goi ra cot      
      
      if(tam==0x80)//goi bit cao ra truoc (bit o cot thu 8 truoc)
      {
        DS=1;// cho LED sang COT =1
      }
      else                                 
      {
        DS=0;//cho LED tat COT =0
      }
      //tao xung dich du lieu   
      SH_CP=1;
      SH_CP=0;  
   }
    //tao xung chot du lieu
      ST_CP=1;
      ST_CP=0;  
}
