#include <detpic32.h>

void isr_T3(void);

int i = 0;

int main(void) 
{ 
      // Configure Timer T3 with interrupts enabled
      T3CONbits.TCKPS = 7; // 1:256 prescaler
      PR3 = 39061;         // Fout = 20MHz / (256 * (39061 + 1)) = 2Hz 
      TMR3 = 0;            // Reset timer T3 count register 
      T3CONbits.TON = 1;   // Enable timer T3 (must be the last command of the timer configuration sequence

      IPC3bits.T3IP = 2;   // Interrupt priority
      IEC0bits.T3IE = 1;   // Enable timer T3 interrupts

      EnableInterrupts(); 
      while(1); 

} 

void _int_(12) isr_T3(void){ // Replace VECTOR by the timer T3  
                             //  vector number 

	if(i == 0){
		putChar('.');
		i = 1;
	}
	else{
		i = 0;
	}

	IFS0bits.T3IF = 0;

}
