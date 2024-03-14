#include<REGX52.h>

unsigned char code Code8Led[] = {0xFF, 0x7F, 0x3F, 0x1F, 0xF, 0x7, 0x3, 0x1, 0x00};

unsigned char code Code7Seg[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};


sbit Led1  = P2^0;  
sbit Led2  = P2^1;
sbit Led3  = P2^2;
sbit Led4  = P2^3;
sbit Led5  = P2^4;
sbit Led6  = P2^5;
sbit Led7  = P2^6;
sbit Led8  = P2^7;

void Delay(int time) {
	while(time--);
}


void CtrlLed() {
	int counter;
	//light up
	for(counter=0; counter<=8; counter++) {
		P2 = Code8Led[counter];;
		Delay(3000);
	}
	//light down
	for(counter=8; counter>=0; counter--) {
		P2 = Code8Led[counter];;
		Delay(3000);
	} 
}

void OnOffLed() {
	if(P3_0 == 0) {
		while(1){
			Led1 = 0;
	}
	} else if(P3_1 == 0){
		while(1){
			Led2 = 0;
	}
	} else if(P3_2 == 0){
		while(1){
			Led3 = 0;
	}
	} else if(P3_3 == 0){
		while(1){
			Led4 = 0;
	}
	}
}

//Thiet lap ham hien thi bang Led 7 doan
void Display() {
	unsigned char chuc, dvi;
	int counter;
	int delayDisplay;
	for(counter = 0 ; counter <= 99 ; counter ++) {
		
		chuc = counter/10;	
		dvi = counter%10;
		
		P0 = Code7Seg[chuc];
		P2_1 = 0;
		Delay(30000);
		P2_1 = 1;

		P0 = Code7Seg[dvi];
		P2_5 = 0;
		Delay(30000);
		P2_5 = 1;}
			
	
	
}

void main() {
	Display();
}
