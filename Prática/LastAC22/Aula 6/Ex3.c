#include <detpic32.h>

int main(void) 
{ 
	// Configure all (digital I/O, analog input, A/D module)
	TRISBbits.TRISB6 = 0;
	TRISBbits.TRISB4 = 1; 	//desligar saída digital
	AD1PCFGbits.PCFG4 = 0;	//ligar entrada analógica RB4
	AD1CON1bits.SSRC = 7;

	AD1CON1bits.CLRASAM = 1;

	AD1CON3bits.SAMC = 16;
	AD1CON2bits.SMPI = 0;

	AD1CHSbits.CH0SA = 4;
	AD1CON1bits.ON = 1; 

      	// Configure interrupt system 
	IPC6bits.AD1IP = 2;	// configure priority of A/D interrupts 
	IEC1bits.AD1IE = 1;	// enable A/D interrupts

      	IFS1bits.AD1IF = 0;            // Reset AD1IF flag 
      	EnableInterrupts();            // Global Interrupt Enable 
      	// Start A/D conversion 
	AD1CON1bits.ASAM = 1;
      	while(1)
	{
		LATBbits.LATB6 = 0;
	}                   // all activity is done by the ISR 
}

// Interrupt Handler 
void _int_(27) isr_adc(void){     // Replace VECTOR by the A/D vector 
                                  // number - see "PIC32 family data  
                                  // sheet" (pages 74-76) 
 
	// Print ADC1BUF0 value       // Hexadecimal (3 digits format)
	printInt(ADC1BUF0, 16 | 3 << 16);
     	// Start A/D conversion 

	// Start conversion 
	AD1CON1bits.ASAM = 1;

     	IFS1bits.AD1IF = 0;           // Reset AD1IF flag 

	LATBbits.LATB6 = 1;
}

// Tempo de Conversão = 3.6 us

// 4.4 us - 3.6 us = 0.8 us

// Tempo overhead = 0.8 us + 1.2 us = 2 us
