#include <detpic32.h>

volatile int ADC;

void isr_adc(void);
void isr_T3(void);

int main(void)
{	
	
		
	
	
	TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0; //desligar entrada analógica RB4  
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 0;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;

    IPC6bits.AD1IP = 2;
    IEC1bits.AD1IE = 1;
    IFS1bits.AD1IF = 0; // Reset AD1IF flag
    
    
    T3CONbits.TCKPS = 7; // 1:256 prescaler
    PR3 = 39061;         // Fout = 20MHz / (256 * (39061 + 1)) = 2Hz 
    TMR3 = 0;            // Reset timer T3 count register 
    T3CONbits.TON = 1; 
    
    
    IPC3bits.T3IP = 2; // Interrupt priority (must be in range [1..6])
 	IEC0bits.T3IE = 1; // Enable timer T2 interrupts
    
    EnableInterrupts();
	
	
	AD1CON1bits.ASAM = 1;
	while(1)
	{
		printInt(ADC,10 | 4 << 10);
		printStr("\n");
	}

	return 0;
}

void _int_(27) isr_adc(void)
{
	ADC = ADC1BUF0;
	IFS1bits.AD1IF = 0;
	
}

void _int_(12) isr_T3(void)
{
	AD1CON1bits.ASAM = 1;
	IFS0bits.T3IF = 0;
}
