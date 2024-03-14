#include <REGX52.H>
#include"ds1302.h"

sbit DS1302_SCLK    = P3^6;
sbit DS1302_IO        = P3^4;
sbit DS1302_CE        = P3^5;

#define DS1302_SECOND_ADDR    0x80    
#define DS1302_MINUTE_ADDR    0x82   
#define DS1302_HOUR_ADDR    0x84   
#define DS1302_DATE_ADDR    0x86   
#define DS1302_MONTH_ADDR    0x88  
#define DS1302_DAY_ADDR        0x8A 
#define DS1302_YEAR_ADDR    0x8C 
#define DS1302_WP_ADDR        0x8E   

unsigned char DS1302_Time[]={22,8,7,20,8,55,7};
// Nam, thang, ngay, gio, phut, giay, tuan


void DS1302_Init(void)
{
    DS1302_CE = 0;
    DS1302_SCLK = 0;
}

void DS1302_WriteByte(unsigned char Command,Data)
{
    unsigned char i;
    DS1302_CE = 1;
    
    for(i=0;i<8;i++)
    {
        DS1302_IO = Command & (0x01<<i); 
        DS1302_SCLK = 1;
        DS1302_SCLK = 0;
    }
    
    for(i=0;i<8;i++)
    {
        DS1302_IO = Data & (0x01<<i);
        DS1302_SCLK = 1;
        DS1302_SCLK = 0;
    }
    
    DS1302_CE = 0;
}


unsigned char DS1302_ReadByte(unsigned char Command)
{
    unsigned char i;
    unsigned char Data = 0x00;
    
    Command = Command | 0x01;
    
    DS1302_CE = 1;
    
    for(i=0;i<8;i++)
    {
        DS1302_IO = Command & (0x01<<i);
        DS1302_SCLK = 0;
        DS1302_SCLK = 1;      
    }
    
    for(i=0;i<8;i++)
    {
        DS1302_SCLK = 1;
        DS1302_SCLK = 0;
        if(DS1302_IO) {Data = Data | (0x01<<i);}
    }
    
    DS1302_CE = 0;
    DS1302_IO = 0;
    return Data;
}


void DS1302_SetTime(void)
{
    DS1302_WriteByte(DS1302_WP_ADDR,0x00);   
    DS1302_WriteByte(DS1302_YEAR_ADDR,        DS1302_Time[0]/10*16+DS1302_Time[0]%10);    //nam
    DS1302_WriteByte(DS1302_MONTH_ADDR,        DS1302_Time[1]/10*16+DS1302_Time[1]%10);   //thang
    DS1302_WriteByte(DS1302_DATE_ADDR,        DS1302_Time[2]/10*16+DS1302_Time[2]%10);    
    DS1302_WriteByte(DS1302_HOUR_ADDR,        DS1302_Time[3]/10*16+DS1302_Time[3]%10);   
    DS1302_WriteByte(DS1302_MINUTE_ADDR,    DS1302_Time[4]/10*16+DS1302_Time[4]%10);    
    DS1302_WriteByte(DS1302_SECOND_ADDR,    DS1302_Time[5]/10*16+DS1302_Time[5]%10);    
    DS1302_WriteByte(DS1302_DAY_ADDR,        DS1302_Time[6]/10*16+DS1302_Time[6]%10);    
    DS1302_WriteByte(DS1302_WP_ADDR,0x80);
}


void DS1302_ReadTime(void)
{
    unsigned char Temp;
    Temp = DS1302_ReadByte(DS1302_YEAR_ADDR);     DS1302_Time[0]=Temp/16*10+Temp%16;
    Temp = DS1302_ReadByte(DS1302_MONTH_ADDR);     DS1302_Time[1]=Temp/16*10+Temp%16;
    Temp = DS1302_ReadByte(DS1302_DATE_ADDR);     DS1302_Time[2]=Temp/16*10+Temp%16;
    Temp = DS1302_ReadByte(DS1302_HOUR_ADDR);     DS1302_Time[3]=Temp/16*10+Temp%16;
    Temp = DS1302_ReadByte(DS1302_MINUTE_ADDR); DS1302_Time[4]=Temp/16*10+Temp%16;
    Temp = DS1302_ReadByte(DS1302_SECOND_ADDR);    DS1302_Time[5]=Temp/16*10+Temp%16;
    Temp = DS1302_ReadByte(DS1302_DAY_ADDR);     DS1302_Time[6]=Temp/16*10+Temp%16;
}