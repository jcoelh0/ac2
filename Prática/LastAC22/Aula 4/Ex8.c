#include <detpic32.h>

void main(void) 
{ 
	static const char display7Scodes[] = {0x3F,0x06,0x5B,0x4F,0x66,
	0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71};
 	int x;

        // configure RB0 to RB3 as inputs
	TRISB = (TRISB | 0x000F);

        // configure RB8 to RB15 as outputs7
	TRISB = (TRISB & 0x00FF);

	// configure RD5 to 6 as outputs
	// select display low
	LATDbits.LATD5 = 1;
	LATDbits.LATD6 = 0;
	TRISDbits.TRISD5 = 0;
	TRISDbits.TRISD6 = 0; 

	while(1){
        	// read dip-switch1
        	// convert to 7 segments code
		x = (PORTB & 0x000F);
		// send to display
		LATB = (LATB & 0x00FF) | (display7Scodes[x] << 8) ;
        } 
}
