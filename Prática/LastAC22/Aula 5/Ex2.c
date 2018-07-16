#include <detpic32.h>

int main(void)
{

	volatile int aux;

	// Configure the A/D module and port RB4 as analog input 

	TRISBbits.TRISB6 = 0;  // Ligar saída digital RB6

	AD1CON1bits.SSRC = 7;
	AD1CON1bits.CLRASAM = 1;
	AD1CON3bits.SAMC = 16;
	AD1CON2bits.SMPI = 0;
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
         	// Read conversion result (ADC1BUF0) to "aux" variable
		aux = ADC1BUF0;
		// Reset AD1IF
		IFS1bits.AD1IF = 0;
		
 	} 

}
