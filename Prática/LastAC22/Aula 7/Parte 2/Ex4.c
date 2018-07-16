#include <detpic32.h>

volatile int voltage; // Global variable 

void setPWM(unsigned int dutyCycle);
void isr_T1(void);
void isr_T3(void);
void isr_adc(void);
unsigned char toBCD(unsigned char);
void send2displays(unsigned char);
void configureAll();

int main(void) 
{ 
   int dutyCycle; 
   configureAll(); 
   EnableInterrupts();  // Global Interrupt Enable 
   while(1) 
   { 
      // Read RB1, RB0 to the variable "portVal" 
      int portVal = (PORTB & 0x0001) || ((PORTB & 0x0002) >> 1);

      switch(portVal) 
      { 
         case 0:  // Measure input voltage 
            // Enable T1 interrupts
	    IEC0bits.T1IE = 1; 
            setPWM(0);  // LED OFF 
            break; 
         case 1:  // Freeze 
            // Disable T1 interrupts
	    IEC0bits.T1IE = 0;
            setPWM(100);  // LED ON (maximum bright) 
            break; 
         default: // LED brigthness control  
            // Enable T1 interrupts
	    IEC0bits.T1IE = 1;
            dutyCycle = voltage * 3; 
            setPWM(dutyCycle); 
            break; 
      } 
   } 
   return 0;
} 

void configureAll(void){

	// Configure all (digital I/O, analog input, A/D module, interrupts) 
	// Ler RB0 e RB1
	TRISBbits.TRISB0 = 1;
	TRISBbits.TRISB1 = 1;
       	
	TRISB = TRISB & 0x00FF;
	TRISDbits.TRISD5 = 0;
	TRISDbits.TRISD6 = 0;
	TRISBbits.TRISB4 = 0; 	// Ligar saída digital
	AD1PCFGbits.PCFG4 = 1;	// Desligar entrada analógica RB4
	AD1CON1bits.SSRC = 7;

	AD1CON1bits.CLRASAM = 1;

	AD1CON3bits.SAMC = 16;
	AD1CON2bits.SMPI = 7;

	AD1CHSbits.CH0SA = 4;
	AD1CON1bits.ON = 1; 

	// Configure Timers T1 and T3
	// Timer T1 - 4Hz
	T1CONbits.TCKPS = 7; // 1:256 prescaler
   	PR1 = 19530; // Fout = 20MHz / (256 * (19530 + 1)) = 4 Hz 
   	TMR1 = 0;            // Reset timer T1 count register 
   	T1CONbits.TON = 1;   // Enable timer T1

   	IPC1bits.T1IP = 2;   // Interrupt priority
   	IEC0bits.T1IE = 1;   // Enable timer T1 interrupts

	// Timer T3 - 100 Hz
	T3CONbits.TCKPS = 2; // 1:4 prescaler
   	PR3 = 49999; // Fout = 20MHz / (4 * (49999 + 1)) = 100 Hz 
   	TMR3 = 0;            // Reset timer T3 count register 
   	T3CONbits.TON = 1;   // Enable timer T3

      	IPC3bits.T3IP = 2;   // Interrupt priority
   	IEC0bits.T3IE = 1;   // Enable timer T3 interrupts

      	// Configure interrupt system 
	IPC6bits.AD1IP = 2;	// configure priority of A/D interrupts 
	IEC1bits.AD1IE = 1;	// enable A/D interrupts

        IFS1bits.AD1IF = 0;           // Reset AD1IF flag 

        EnableInterrupts();           // Global Interrupt Enable 

}

void setPWM(unsigned int dutyCycle) 
{ 
   // duty_cycle must be in the range [0, 100] 
   OC1RS = ((19530+1) * dutyCycle) / 100;
}

void _int_(27) isr_adc(void){

	// Calculate buffer average (8 samples)
	int i, V;
	int media = 0;
	int *p = (int *)(&ADC1BUF0);
	for(i = 0; i < 16; i++)
		media += p[i*4];
 	media = media / 8;
        // Calculate voltage amplitude
	V = (media * 33) / 1023;
        // Convert voltage amplitude to decimal. Copy it to "voltage" 
	voltage = toBCD(V);
	// Reset AD1IF flag
        IFS1bits.AD1IF = 0;
}

void _int_(4) isr_T1(void) 
{ 
         // Start A/D conversion
	 AD1CON1bits.ASAM = 1; 
         // Reset T1IF flag
	 IFS0bits.T1IF = 0;
} 

void _int_(12) isr_T3(void) 
{ 
         // Send "voltage" global variable to displays 
	 send2displays(voltage);
         // Reset T3IF flag 
	 IFS0bits.T3IF = 0;
} 

unsigned char toBCD(unsigned char value){

	return ((value / 10) << 4) + (value % 10);

}

void send2displays(unsigned char value)
{ 

	static const char display7Scodes[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7C,0x39,0x5E,0x79,0x71};
	
	static unsigned char displayFlag = 0;
	
	unsigned char first = value & 0x0F;
	first = display7Scodes[first];
	unsigned char second = value >> 4;
	second = display7Scodes[second];
	
	if(!displayFlag){ // send digit_high to display_high
		LATDbits.LATD5 = 1;
		LATDbits.LATD6 = 0;
		LATB = (LATB & 0x00FF) | first<<8;
		
	}else{ // send digit_low to display_low
		LATDbits.LATD5 = 0;
		LATDbits.LATD6 = 1;
		LATB= (LATB & 0x00FF) | second<<8;
		
	}
	displayFlag = !displayFlag;
} 
