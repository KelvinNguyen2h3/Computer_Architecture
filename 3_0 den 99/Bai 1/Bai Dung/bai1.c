#include <REGX52.h>

void delay (int t) {
	while (t--);
}

int i,j,a,b;
char so[] = {0x3f, 0x06,0x5b, 0x4f, 0x66,0x6d, 0x7d, 0x07,0x7f,0x6f};

void main() {
while (1) {
    for (i = 0;i<100; i++){
			a = i/10;
			b = i%10;
			for (j = 0; j < 200; j++){
				P2_2 = 1;
				P0 = so[a];
				delay(100);
				P0 = so[0];
				
				P2_2 = 0;
				P0 = so[b];
				delay(100);
				P0 = so[0];
			}
		}
	}
}