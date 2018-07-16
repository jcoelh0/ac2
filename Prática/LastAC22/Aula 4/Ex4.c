#include <detpic32.h>

void delay(int);

void main(void) 
{ 
	unsigned char segment;
        
        // configure RB8-RB14 as outputs
	LATB = (LATB & 0x80FF);
	TRISB = (TRISB & 0x80FF);

	// configure RD5-RD6 as outputs 
	LATDbits.LATD6 = 1; // display high active 
        LATDbits.LATD5 = 0; // display low inactive 	
	TRISDbits.TRISD6 = 0;
	TRISDbits.TRISD5 = 0;
        
	while(1)
        { 
 	       LATDbits.LATD6 = !LATDbits.LATD6; 
 	       LATDbits.LATD5 = !LATDbits.LATD5;  
 	       segment = 1;
	       int i;
 	       for(i=0; i < 7; i++) 
               { 
               		// send "segment" value to display
			LATB = (LATB & 0x80FF) | (segment << 8);

               		// wait 1 second
			delay(1000);
              		segment = segment << 1; 
               } 
        } 
}

void delay(int ms)
{ 
	for(; ms > 0; ms--) 
	{ 
		resetCoreTimer(); 
		while(readCoreTimer() < 20000); 
	} 
}
