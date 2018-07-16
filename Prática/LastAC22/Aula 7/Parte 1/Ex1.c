#include <detpic32.h>

int main(void) 
{ 
      // Configure Timer T3 (2 Hz with interrupts disabled)
      T3CONbits.TCKPS = 7; // 1:256 prescaler
      PR3 = 39061;         // Fout = 20MHz / (256 * (39061 + 1)) = 2Hz 
      TMR3 = 0;            // Reset timer T3 count register 
      T3CONbits.TON = 1;   // Enable timer T3 (must be the last command of the timer configuration sequence)  

      while(1) 
      { 
         // Wait until T3IF = 1 
         while(IFS0bits.T3IF == 0);
	 // Reset T3IF 
	 IFS0bits.T3IF = 0;
         putChar('.'); 
      } 
   
}
