#include <detpic32.h>

void send2displays(unsigned char);
void delay(int);

int main(void)
{
	
	TRISDbits.TRISD5 = 0;
	TRISDbits.TRISD6 = 0;
	
	TRISB = TRISB & 0x00ff; //r15 a rb8 sao saidas
	
	LATDbits.LATD5 = 0;
	LATDbits.LATD6 = 0;
	
	while(1)
	{
		char x = 0x3F;
		send2displays(x);
		delay(1);
	}
	
}

void send2displays(unsigned char value) 
{ 

	static const char display7Scodes[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71};
	
	static unsigned char displayFlag = 0;
	
	unsigned char first = value & 0x0F;
	first = display7Scodes[first];
	unsigned char second = value >> 4;
	second = display7Scodes[second];
	
	if(!displayFlag){ // send digit_high to display_high
		LATDbits.LATD5 = 1;
		LATDbits.LATD6 = 0;
		LATB = (LATB & 0x00FF) | first << 8;
	
	}else{ // send digit_low to display_low
		LATDbits.LATD5 = 0;
		LATDbits.LATD6 = 1;
		LATB= (LATB & 0x00FF) | second << 8;
		
	}
	displayFlag = !displayFlag;
} 

void delay(int ms) 
{ 
   	for(; ms > 0; ms--) 
   	{ 
     	resetCoreTimer(); 
      	while(readCoreTimer() < 20000); 
   	} 
}
