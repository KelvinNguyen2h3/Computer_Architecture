#include<REGX52.h>


sbit Led1  = P2^0;  
sbit Led2  = P2^1;
sbit Led3  = P2^2;
sbit Led4  = P2^3;
sbit Led5  = P2^4;
sbit Led6  = P2^5;
sbit Led7  = P2^6;
sbit Led8  = P2^7;

void Delay(int t) {
   while(t--);
}


void Display() {
	
	//Sang dan
	P2 = 0;
	P2_0 = 1;

	Delay(10000);
	P2_1 = 1;

	Delay(10000);
	P2_2 = 1;

	Delay(10000);
	P2_3 = 1;

	Delay(10000);	
	P2_4 = 1;

	Delay(10000);	
	P2_5 = 1;

	Delay(10000);	
	P2_6 = 1;

	Delay(10000);
	P2_7 = 1;
	
	Delay(50000);
	
	// Tat dan
	
	P2_0 = 0;
	Delay(10000);
	
	P2_1 = 0;
	Delay(10000);
	
	P2_2 = 0;
	Delay(10000);
	
	P2_3 = 0;
	Delay(10000);
	
	P2_4 = 0;
	Delay(10000);
	
	P2_5 = 0;
	Delay(10000);
	
	P2_6 = 0;
	Delay(10000);
	
	P2_7 = 0;
	
	Delay(50000);

}

void CtrlLed() {
		if(P3_0 == 0){
			P2_1 = 0 ;
		}  else if(P3_1 == 0){
			P2_0 = 0 ;
		}  

}

void main() {
	 if (P3_0 == 0 || P3_1 == 0) {
        CtrlLed();
    } else {
        Display();
    }
	}

