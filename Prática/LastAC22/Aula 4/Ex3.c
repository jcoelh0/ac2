#include <detpic32.h>	

int main(void)
{

	printf("Pedro Miguel André Coelho Nº 68803");

	//0000 0000 1111 1111  = 0x00ff
	LATB = LATB & 0x0000;	
	TRISB = TRISB & 0x00FF;

	LATDbits.LATD5 = 0;
	LATDbits.LATD6 = 1;
	TRISDbits.TRISD5 = 0;
	TRISDbits.TRISD6 = 0;

	char c;
	while(1){
		LATDbits.LATD5 = 0;
		LATDbits.LATD6 = 1;
		c = getChar();

		if(c=='A' || c=='a')
			LATBbits.LATB8 = 1;
		else if(c=='B' || c=='b')
			LATBbits.LATB9 = 1;
		else if(c=='C' || c=='c')
			LATBbits.LATB10 = 1;
		else if(c=='D' || c=='d')
			LATBbits.LATB11 = 1;
		else if(c=='E' || c=='e')
			LATBbits.LATB12 = 1;
		else if(c=='F' || c=='f')
			LATBbits.LATB13 = 1;
		else if(c=='G' || c=='g')
			LATBbits.LATB14 = 1;
		else if(c=='.')
			LATBbits.LATB15 = 1;
	}

}
