#include "key4x4.h"
unsigned char  KEY_4X4[4][4]={'7','8','9','_',
						      '4','5','6','_',
							  '1','2','3','_',
						      '0','+','-','='};
unsigned char  KEY4X4_Push(void)
{

	if((ROW1==0)|(ROW2==0)|(ROW3==0)|(ROW4==0))
		return 1;
	else 
		return 0;
}

void KEY4X4_CheckCol(unsigned char Col)
{
	  	COL1=1;
		COL2=1;
		COL3=1;
		COL4=1;
	if(Col==0)
	{
		COL1=0;
	}
	else if(Col==1)
	{
		COL2=0;
	}
	else if(Col==2)
	{
		COL3=0;
	}
	else if(Col==3)
	{
		COL4=0;
	}
}

unsigned char KEY4X4_GetKey(void)
{
	unsigned char i;
	//cho COL1 den COL4 =0
	  	COL1=0;
		COL2=0;
		COL3=0;
		COL4=0;
	if(KEY4X4_Push()==1)//phat hien co phim nhan
	{
		delay_ms(1);//chong nhieu
		if(KEY4X4_Push()==1)//xac dinh chac chan co nhan
		{			
			for(i=0;i<4;i++)//quet COL1 den COL3
			{				
				KEY4X4_CheckCol(i);
				
				if(ROW1==0)//neu hang thu 1 co nhan (ROW1)
					{
						return KEY_4X4[0][i];	//tra ve ky tu nhan o ROW1 va COL quet tu COL1 den COL4
					}
				else if(ROW2==0)//neu hang thu 2 co nhan (ROW2)
					{
						return KEY_4X4[1][i];//tra ve ky tu nhan o ROW2 va COL quet tu COL1 den COL4
					}
				else if(ROW3==0)//neu hang thu 2 co nhan (ROW2)
					{	
						return KEY_4X4[2][i];//tra ve ky tu nhan o ROW3 va COL quet tu COL1 den COL4
					}
						
				else if(ROW4==0)//neu hang thu 2 co nhan (ROW2)
					{
						return KEY_4X4[3][i];//tra ve ky tu nhan o ROW4 va COL quet tu COL1 den COL4
					}
			}			
		}
	}
	return 0;//khong co nhan
}
void Keypad_Init()
	{
		COL1=0;
		COL2=0;
		COL3=0;
		COL4=0;
		ROW1=1;
		ROW2=1;
		ROW3=1;
		ROW4=1;
	}