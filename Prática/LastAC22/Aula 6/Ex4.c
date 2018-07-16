#include <detpic32.h>

volatile unsigned char value2display = 0;   // Global variable 

void isr_adc(void);
void delay(int);
unsigned char toBCD(unsigned char);
void send2displays(unsigned char);

int main(void){ 

	// Configure all (digital I/O, analog input, A/D module, interrupts) 
       	
	TRISB = TRISB & 0x00FF;
	TRISDbits.TRISD5 = 0;
	TRISDbits.TRISD6 = 0;
	TRISBbits.TRISB4 = 0; 	//ligar saída digital
	AD1PCFGbits.PCFG4 = 1;	//desligar entrada analógica RB4
	AD1CON1bits.SSRC = 7;

	AD1CON1bits.CLRASAM = 1;

	AD1CON3bits.SAMC = 16;
	AD1CON2bits.SMPI = 7;

	AD1CHSbits.CH0SA = 4;
	AD1CON1bits.ON = 1; 

      	// Configure interrupt system 
	IPC6bits.AD1IP = 2;	// configure priority of A/D interrupts 
	IEC1bits.AD1IE = 1;	// enable A/D interrupts

        IFS1bits.AD1IF = 0;           // Reset AD1IF flag 
        EnableInterrupts();           // Global Interrupt Enable 

        int i = 0; 
        while(1){ 
        	// Wait 10 ms using the core timer

		delay(10);

  	        if(i++ == 25){  // 250 ms (4 samples/second) 
  	 		// Start A/D conversion
		        AD1CON1bits.ASAM = 1;
  	        	i = 0; 
  	       	} 
  	       	// Send "value2display" variable to displays
		send2displays(value2display);
  	} 
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
        // Convert voltage amplitude to decimal. Assign it to "value2display"
	value2display = toBCD(V);
	
        IFS1bits.AD1IF = 0;           // Reset AD1IF flag 
}

void delay(int ms){

	for(; ms > 0; ms--){
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}

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
