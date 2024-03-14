#include<REGX52.h>

void Delay(int t) {
	while (t--);
}

void Display() {
	
	//Sang dan
	P2 = 0;
	
	P2_0 = 1;

	Delay(200000);
	P2_1 = 1;

	Delay(200000);
	P2_2 = 1;

	Delay(200000);
	P2_3 = 1;

	Delay(200000);	
	P2_4 = 1;

	Delay(200000);	
	P2_5 = 1;

	Delay(200000);	
	P2_6 = 1;

	Delay(200000);
	P2_7 = 1;
	
	Delay(300000);
	
	// Tat dan
	
	P2_0 = 0;
	Delay(200000);
	
	P2_1 = 0;
	Delay(200000);
	
	P2_2 = 0;
	Delay(200000);
	
	P2_3 = 0;
	Delay(200000);
	
	P2_4 = 0;
	Delay(200000);
	
	P2_5 = 0;
	Delay(200000);
	
	P2_6 = 0;
	Delay(200000);
	
	P2_7 = 0;
	
	Delay(300000);

}

void CtrlLed() {
		P2 = 0;
		if(P1_0 == 1){
				P2_0 = 1;
		}  if(P1_1 == 1){
				P2_1 = 1;
		}  if(P1_2 == 1){
				P2_2 = 1;
		}  if(P1_3 == 1){
				P2_3 = 1;
		}  if(P1_4 == 1){
				P2_4 = 1;
		}  if(P1_5 == 1){
				P2_5 = 1;
		}  if(P1_6 == 1){
				P2_6 = 1;
		}  if(P1_7 == 1){
				P2_7 = 1;
		}
}

void main() {
    if (P1_0 == 1 || P1_1 == 1 || P1_2 == 1 || P1_3 == 1 || P1_4 == 1 || P1_5 == 1 || P1_6 == 1 || P1_7 == 1) {
        CtrlLed();
    } else {
        Display();
    }
}


