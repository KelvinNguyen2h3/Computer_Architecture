#include<reg51.h>
#include<intrins.h>	

#define GPIO_DIG P0

sbit L1=P2^2;
sbit L2=P2^3;
sbit L3=P2^4;

sbit K1=P3^1;
sbit K2=P3^0;

unsigned char code DIG_CODE[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

void Delay10ms();  
void main(void)
{
	unsigned int i,j;
	L1=0;
	L2=0;
	L3=0;
	while(1)
	{			
		// tang
		if(K1==0)					
		{
			Delay10ms();
			if(K1==0)
			{
				j++;
				if(j>9)
					j=0;
			}		
			while((i<50)&&(K1==0))
			{
				Delay10ms();
				i++;
			}
			i=0;
		}
		// giam
		if(K2==0)			
		{
			Delay10ms();
			if(K2==0)
			{
				j--;
				if(j>9)
					j=9;				
			}
			while((i<50)&&(K2==0))
			{
				Delay10ms();
				i++;
			}
			i=0;
		}
		
		
		GPIO_DIG=DIG_CODE[j];
	}				
}
void Delay10ms(void)   
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}