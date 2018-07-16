#include <detpic32.h>

int main(void)
{

	volatile int aux;
	int i;
	// Configure the A/D module and port RB4 as analog input 

	TRISBbits.TRISB6 = 0;  // Ligar saída digital RB6

	AD1CON1bits.SSRC = 7;
	AD1CON1bits.CLRASAM = 1;
	AD1CON3bits.SAMC = 16;
	AD1CON2bits.SMPI = 15;
	AD1CHSbits.CH0SA = 4;
	AD1CON1bits.ON = 1; // Enable A/D converter

      	while(1) 
      	{ 

 		// Set LATB6 
		LATBbits.LATB6 = 1;
        	// Start conversion
		AD1CON1bits.ASAM = 1;
         	// Wait while conversion not done (AD1IF == 0)
		while(IFS1bits.AD1IF == 0);
         	// Reset LATB6
		LATBbits.LATB6 = 0;

		int *p = (int *) (&ADC1BUF0);		
		for(i = 0; i<16; i++){
			printInt(p[i*4], 10 | 4 << 10);
			printf(" ");		
		}
		// Reset AD1IF
		IFS1bits.AD1IF = 0;
		
 	} 

}
