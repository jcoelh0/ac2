#include <detpic32.h>

void isr_T1(void);
void isr_T3(void);

int main(void) 
{ 
      // Configure Timer T1 with interrupts enabled
      T1CONbits.TCKPS = 7; // 1:256 prescaler
      PR1 = 39061;         // Fout = 20MHz / (256 * (39061 + 1)) = 2Hz 
      TMR1 = 0;            // Reset timer T1 count register 
      T1CONbits.TON = 1;   // Enable timer T1 (must be the last command of the timer configuration sequence

      IPC1bits.T1IP = 2;   // Interrupt priority (must be in range [1..6])
      IEC0bits.T1IE = 1;   // Enable timer T1 interrupts

      // Configure Timer T3 with interrupts enabled
      T3CONbits.TCKPS = 5; // 1:32 prescaler
      PR3 = 62499;         // Fout = 20MHz / (32 * (62499 + 1))= 10Hz 
      TMR3 = 0;            // Reset timer T3 count register 
      T3CONbits.TON = 1;   // Enable timer T3 (must be the last command of the timer configuration sequence

      IPC3bits.T3IP = 2;   // Interrupt priority (must be in range [1..6])
      IEC0bits.T3IE = 1;   // Enable timer T3 interrupts

      EnableInterrupts(); 
      while(1); 

} 

void _int_(4) isr_T1(void) // Replace VECTOR by the timer T3  
                    		// vector number 
{ 
      // print character '1'
      printStr("1");
      // Reset T1 interrupt flag
      IFS0bits.T1IF = 0;

}

void _int_(12) isr_T3(void) // Replace VECTOR by the timer T3  
                    		// vector number 
{ 
      // print character '3'
      printStr("3");
      // Reset T3 interrupt flag
      IFS0bits.T3IF = 0;

}
