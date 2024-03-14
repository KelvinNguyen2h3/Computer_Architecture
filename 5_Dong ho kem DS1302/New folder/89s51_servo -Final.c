#include <REGX52.H>
#include <intrins.h>
#include"ds1302.h"

#define GPIO_DIG P0

sbit K1 = P3^1;
sbit K2 = P3^0;
sbit K3 = P3^3;
sbit K4 = P3^2; 

void delay(int t) {
    int j, y;
    for (j = 0; j <= t; j++) {
        for (y = 0; y < 123; y++);
    }
}

char Num[] = {0xff, 0xfb, 0xf7, 0xf3, 0xef, 0xeb, 0xe7, 0xe3};
unsigned char Led[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

void displayTime(unsigned char gio, unsigned char phut, unsigned char giay) {
    unsigned char chuc, donvi;

	chuc = gio / 10;
    donvi = gio % 10;
    P0 = Led[chuc];
    P2 = Num[0];
    delay(1);
    P0 = 0x00;

    P0 = Led[donvi];
    P2 = Num[1];
    delay(1);
    P0 = 0x00;

    chuc = phut / 10;
    donvi = phut % 10;
    P0 = Led[chuc];
    P2 = Num[3];
    delay(1);
    P0 = 0x00;

    P0 = Led[donvi];
    P2 = Num[4];
    delay(1);
    P0 = 0x00;

    chuc = giay / 10;
    donvi = giay % 10;
    P0 = Led[chuc];
    P2 = Num[6];
    delay(1);
    P0 = 0x00;

    P0 = Led[donvi];
    P2 = Num[7];
    delay(1);
    P0 = 0x00;
}

void main() {
    unsigned char gio = 10;
    unsigned char phut = 0;
    unsigned char giay = 0;
    unsigned char ngay = 25;
    unsigned char thang = 9;
    unsigned int nam = 2023;
    unsigned char ngan, tram, chuc, donvi;
    int i, tictac;
    bit isTimeDisplay = 1; 
    tictac = 0;

    while (1) {
        if (K4 == 0) {
            _nop_();
            if (K4 == 0) { 
                isTimeDisplay = !isTimeDisplay; 
                delay(200);  
            }
        }

        if (isTimeDisplay) {
            displayTime(gio, phut, giay);
        } else {
            
					//ngay
            chuc = ngay / 10;
            donvi = ngay % 10;
            P0 = Led[chuc];
            P2 = Num[0];
            delay(1);
            P0 = 0x00;

            P0 = Led[donvi];
            P2 = Num[1];
            delay(1);
            P0 = 0x00;

					//thang
            chuc = thang / 10;
            donvi = thang % 10;
            P0 = Led[chuc];
            P2 = Num[2];
            delay(1);
            P0 = 0x00;

            P0 = Led[donvi];
            P2 = Num[3];
            delay(1);
            P0 = 0x00;
						
					//nam
						ngan = nam / 1000;
						tram = (nam%1000)/100;
						chuc = (nam%100)/10;
						donvi = (nam%10);
						
            P0 = Led[ngan];
            P2 = Num[4];
            delay(1);
            P0 = 0x00;

            P0 = Led[tram];
            P2 = Num[5];
            delay(1);
            P0 = 0x00;
						
						P0 = Led[chuc];
            P2 = Num[6];
            delay(1);
            P0 = 0x00;
						
						P0 = Led[donvi];
            P2 = Num[7];
            delay(1);
            P0 = 0x00;
        }

        tictac++;
        if (tictac == 80) {
            tictac = 0;
            giay++;
            if (giay == 60) {
                giay = 0;
                phut++;
                if (phut == 60) {
                    phut = 0;
                    gio++;
                    if (gio == 24) {
                        gio = 0;
                    }
                }
            }
        }
    }
}
