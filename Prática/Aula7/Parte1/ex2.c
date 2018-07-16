#include <detpic32.h>

void isr_T3(void);

void main(void)
{
	// Configure Timer T3 with interrupts enabled
	T3CONbits.TCKPS = 7; 		// 1:256 prescaler (i.e Fout_presc = 78125 Hz)
 	PR3 = 39061; 		 		// Fout = 20MHz / (32 * (x + 1)) = 2 Hz
 						 		// PR3 = (78125Hz / 2Hz) – 1 ≅ 39061
 	TMR3 = 0; 			 		// Reset timer T3 count register
 	T3CONbits.TON = 1; 	 		// Enable timer T3
 	
	IPC3bits.T3IP = 2; 			// Interrupt priority (must be in range [1..6])
 	IEC0bits.T3IE = 1; 			// Enable timer T3 interrupts
 	IFS0bits.T3IF = 0; 			// Reset timer T3 interrupt flag 
	
	EnableInterrupts();
	while(1);
}
void _int_(12) isr_T3(void) // Replace VECTOR by the timer T3
{
	putChar('.');
	IFS0bits.T3IF = 0;			// Reset T3 interrupt flag
} 
