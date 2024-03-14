#include <reg52.h>


sbit SEG_A = P0^0;
sbit SEG_B = P0^1;
sbit SEG_C = P0^2;
sbit SEG_D = P0^3;
sbit SEG_E = P0^4;
sbit SEG_F = P0^5;
sbit SEG_G = P0^6;
sbit SEG_DP = P0^7;


sbit DIGIT_1 = P2^0;
sbit DIGIT_2 = P2^1;
sbit DIGIT_3 = P2^2;
sbit DIGIT_4 = P2^3;


unsigned int hour = 0;
unsigned int minute = 0;
unsigned int second = 0;


void delay(unsigned int msec) {
    unsigned int i, j;
    for (i = 0; i < msec; i++)
        for (j = 0; j < 120; j++);
}


void displayDigit(unsigned char digit) {
    switch (digit) {
        case 0: P0 = 0x3f; break; 
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

void displayTime() {
		// Gio
    DIGIT_1 = 1;
    DIGIT_2 = 0;
    displayDigit(hour / 10);
    delay(5);
    
    DIGIT_1 = 0;
    DIGIT_2 = 1;
    displayDigit(hour % 10);
    delay(5);
    
    // Phut
    DIGIT_2 = 0;
    DIGIT_3 = 1;
    displayDigit(minute / 10);
    delay(5);
    
    DIGIT_2 = 1;
    DIGIT_3 = 0;
    displayDigit(minute % 10);
    delay(5);
    
    // Giay
    DIGIT_3 = 0;
    DIGIT_4 = 1;
    displayDigit(second / 10);
    delay(5);
    
    DIGIT_3 = 1;
    DIGIT_4 = 0;
    displayDigit(second % 10);
    delay(5);
}



void main() {
    TMOD = 0x01;
    TH0 = 0xFC;
    TL0 = 0x18;
    TR0 = 1;
    ET0 = 1;


		// Gia tri ban dau
    hour = 12;
    minute = 0;
    second = 0;

	
    P0 = 0x00;
    P1 = 0x00;
    P2 = 0x00;

	
    EA = 1;

    while (1) {
        displayTime();
    }
}


void timer0_isr() interrupt 1 {
    TH0 = 0xFC;
    TL0 = 0x18;
    
    second++;

    if (second == 60) {
        second = 0;
        minute++;
        if (minute == 60) {
            minute = 0;
            hour++;
            if (hour == 24) {
                hour = 0;
            }
        }
    }
}
