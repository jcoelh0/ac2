#include <detpic32.h>

void setPWM(unsigned int dutyCycle);

int main(void){

   T3CONbits.TCKPS = 2; // 1:4 prescaler
   PR3 = 49999;         // Fout = 20MHz / (4 * (49999 + 1)) = 100 Hz 
   TMR3 = 0;            // Reset timer T3 count register 
   T3CONbits.TON = 1;   // Enable timer T3 (must be the last command of the timer configuration sequence) 
   OC1CONbits.OCM = 6;  // PWM mode on OCx; fault pin disabled 
   OC1CONbits.OCTSEL = 1;// Use timer T3 as the time base for PWM generation 
   setPWM(80);       // Ton constant 
   OC1CONbits.ON = 1;   // Enable OC1 module

   while(1);
   return 0; 

}

void setPWM(unsigned int dutyCycle) 
{ 
   // duty_cycle must be in the range [0, 100] 
   OC1RS = ((49999+1) * dutyCycle) / 100;
}
