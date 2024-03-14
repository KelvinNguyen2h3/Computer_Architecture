#include <stdlib.h>
#include <REGX52.H>
#include "HC595.H"
#include "Delay.H"
#include "MatrixKey.H"
#include "Timer0.H"
unsigned char Dire,KeyNum,length,foodx,foody;
char Snakex[30]={0};
char Snakey[30]={0};
unsigned char code Coorx[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
unsigned char code Coory[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
void SnakeMove()
{	unsigned char i;
    for (i=length+1;i>0;i--)
    {
        Snakex[i]=Snakex[i-1];
        Snakey[i]=Snakey[i-1];
    }	
	switch(Dire)
	{
		case 1:(Snakex[0])--;if((Snakex[0])<0){(Snakex[0])=7;}break;
		case 2:(Snakex[0])++;(Snakex[0])%=8;break;
		case 3:(Snakey[0])++;(Snakey[0])%=8;break;
		case 4:(Snakey[0])--;if((Snakey[0])<0){(Snakey[0])=7;}break;
	}
}
void Scan_Key()
{
	if(KeyNum)
	{
		switch(KeyNum)
		{
			case 1:if(Dire!=3)Dire=4;break;
			case 2:if(Dire!=4)Dire=3;break;
			case 3:if(Dire!=2)Dire=1;break;
			case 4:if(Dire!=1)Dire=2;break;
		}
	}
}
void food()
{	
	foodx=(rand()+Snakex[length-1])%8;
	foody=(rand()+Snakex[length-1])%8;
}
void vatcan(char m, char n){
	MatrixLed(Coorx[m],Coory[n]);
}
void PlaySnakeAC()
{
	unsigned char i;
	for(i=0;i<length;i++)
	{
	MatrixLed(Coorx[Snakex[i]],Coory[Snakey[i]]);
	MatrixLed(Coorx[foodx],Coory[foody]);
	}
}
void Snakedead(unsigned char a,unsigned char b,unsigned char c,unsigned char d,unsigned char e,unsigned char f)
{	unsigned char i;
	for(i=3;i<length;i++)
	{
		if((Snakex[0]==Snakex[i] && Snakey[0]==Snakey[i]) || (Snakex[0]==a && Snakey[0]==b) || (Snakex[0]==c && Snakey[0]==d) || (Snakex[0]==e && Snakey[0]==f))
		{
			P0=0xFF;
			while(1);		
		}
	}
}
void Play_Game(unsigned char a,unsigned char b,unsigned char c,unsigned char d,unsigned char e,unsigned char f)
{	unsigned char i;
	Scan_Key();
	PlaySnakeAC();
	Snakedead(a,b,c,d,e,f);
	for(i=0;i<length;i++)
	{	
		if(foodx==Snakex[i] && foody==Snakey[i])
		{
			length++;
			food();
		}
	}
}
void main()
{	
	unsigned char a,b,c,d,e,f;
	Timer0_Init();
	length=1;
	Dire=3;
	a = 2;
	b = 2;
	c = 2;
	d = 3;
	e = 3;
	f = 2;
	while(1)
	{	rand();
		KeyNum=Key();
		Play_Game(a,b,c,d,e,f);
		vatcan(a, b);
		vatcan(c, d);
		vatcan(e, f);
	}
}

void Routine_Timer0()interrupt 1
{
	static unsigned char T0Count1,T0Count2;
	TL0 = 0xCD;		
	TH0 = 0xD4;			
	T0Count1++;
	if(T0Count1>=15)
	{
		T0Count1=0;
		Loop_MatrixKey();
	}
	T0Count2++;
	if(T0Count2>30)
	{	
		T0Count2=0;
		SnakeMove();
	}

}
