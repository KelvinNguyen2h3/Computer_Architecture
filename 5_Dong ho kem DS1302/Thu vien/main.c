#include<reg51.h>
#include"lcd.h"
#include"temp.h"
#include"ds1302.h"



typedef unsigned char uint8;
typedef unsigned int uint16;
typedef unsigned long uint32;

sbit K1=P3^1;
sbit K2=P3^0;
sbit K3=P3^2;
sbit K4=P3^3;
sbit beep=P1^5;


void Int0Configuration();
unsigned char SetState,SetPlace;
void Delay10ms(void);

uchar CNCHAR[6] = "E";
void LcdDisplay(int);
void UsartConfiguration();




void main()
{
	unsigned char i;
	
	Int0Configuration();
	UsartConfiguration();
	Ds1302Init();
	LcdInit();			
	LcdWriteCom(0x8F+0x40);
	LcdWriteData('C'); 
	while(1)
	{
		if(SetState==0)
		{
			Ds1302ReadTime();
		}
		else
		{
			if(K1==0)	
			{
				Delay10ms();
				if(K1==0)
				{
					SetPlace++;
					if(SetPlace>=7)
						SetPlace=0;					
				}

				while((i<50)&&(K1==0))
				{
					Delay10ms();
					i++;
				}
				i=0;
			}
			if(K2==0)	
			{
				Delay10ms();
				if(K2==0)
				{
					TIME[SetPlace]++;
					if((TIME[SetPlace]&0x0f)>9)	
					{
						TIME[SetPlace]=TIME[SetPlace]+6;
					}
					if((TIME[SetPlace]>=0x60)&&(SetPlace<2))
					{
						TIME[SetPlace]=0;
					}
					if((TIME[SetPlace]>=0x24)&&(SetPlace==2))
					{
						TIME[SetPlace]=0;
					}
					if((TIME[SetPlace]>=0x32)&&(SetPlace==3))
					{
						TIME[SetPlace]=0;	
					}
					if((TIME[SetPlace]>=0x13)&&(SetPlace==4))
					{
						TIME[SetPlace]=0;
					}	
					if((TIME[SetPlace]>=0x7)&&(SetPlace==5))
					{
						TIME[SetPlace]=1;
					}		
				}
				
				while((i<50)&&(K2==0))
				{
					Delay10ms();
					i++;
				}
				i=0;
		
	}
}
		
		LcdDisplay(Ds18b20ReadTemp());
    

	}
	
}


void LcdDisplay(int temp)
{
    unsigned int tempbeem;
  	unsigned char i, datas[] = {0, 0, 0, 0, 0};
	float tp;
	if(temp< 0)
  	{
	  	LcdWriteCom(0x89+0x40);
		SBUF='-';
		while(!TI);
		TI=0;
	    LcdWriteData('-');
		temp=temp-1;
		temp=~temp;
		tp=temp;
		temp=tp*0.0625*100+0.5;	
 
  	}
 	else
  	{			
	  	LcdWriteCom(0x89+0x40);
	    LcdWriteData('+');
		SBUF='+';
		while(!TI);
		TI=0;
		tp=temp;
		temp=tp*0.0625*100+0.5;	
	}		

	datas[0] = temp % 10000 / 1000;
	datas[1] = temp % 1000 / 100;
	datas[2] = temp % 100 / 10;
	datas[3] = temp % 10 / 1;
	
	
	LcdWriteCom(0x8A+0x40);	
	LcdWriteData('0'+datas[0]);
	SBUF = '0'+datas[0];
	while (!TI);
	TI = 0;

	LcdWriteCom(0x8B+0x40);
	LcdWriteData('0'+datas[1]);
	SBUF = '0'+datas[1];
	while (!TI);
	TI = 0;

	LcdWriteCom(0x8C+0x40);
	LcdWriteData('.');
	SBUF = '.';
	while (!TI);
	TI = 0;

	LcdWriteCom(0x8D+0x40);
	LcdWriteData('0'+datas[2]);
	SBUF = '0'+datas[2];
	while (!TI);
	TI = 0;
	
	LcdWriteCom(0x8E+0x40);
	LcdWriteData('0'+datas[3]); 
	SBUF = '0'+datas[3];
	while (!TI);
	TI = 0;

	for(i=0; i<6; i++)
	{
	 	SBUF = CNCHAR[i];
		while (!TI);
		TI = 0;
	}
	 
	 LcdWriteCom(0x80+0X40);
	LcdWriteData('0'+TIME[2]/16);
	LcdWriteData('0'+(TIME[2]&0x0f));				 
	LcdWriteData(':');
	LcdWriteData('0'+TIME[1]/16);
	LcdWriteData('0'+(TIME[1]&0x0f));	
	LcdWriteData(':');
	LcdWriteData('0'+TIME[0]/16);
	LcdWriteData('0'+(TIME[0]&0x0f));
	
	LcdWriteCom(0x83);
	LcdWriteData('2');
	LcdWriteData('0');
	LcdWriteData('0'+TIME[6]/16);
	LcdWriteData('0'+(TIME[6]&0x0f));
	LcdWriteData('-');
	LcdWriteData('0'+TIME[4]/16);
	LcdWriteData('0'+(TIME[4]&0x0f));
	LcdWriteData('-');
	LcdWriteData('0'+TIME[3]/16);
	LcdWriteData('0'+(TIME[3]&0x0f));
	
	   tempbeem=temp / 100;
	   if(tempbeem>22&&tempbeem<32)
	 {
	beep = ~beep;
		 
	 }
}


void UsartConfiguration()
{
	SCON=0X50;
	TMOD=0X20;
	PCON=0X80;
	TH1=0XF3;
	TL1=0XF3;
	TR1=1;
}



void Int0Configuration()
{
	IT0=1;
	EX0=1;
	EA=1;
}

void Int0() interrupt 0		 
{
	Delay10ms();
	if(K3==0)
	{
		SetState=~SetState;
		SetPlace=0;
		Ds1302Init();	
	}
}

void Delay10ms(void)
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}
