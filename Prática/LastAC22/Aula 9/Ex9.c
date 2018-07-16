#define  DisableUart1RxInterrupt()    IEC0bits.U1RXIE = 0
#define  EnableUart1RxInterrupt()     IEC0bits.U1RXIE = 1
#define  DisableUart1TxInterrupt()    IEC0bits.U1TXIE = 0 
#define  EnableUart1TxInterrupt()     IEC0bits.U1TXIE = 1

#define BUF_SIZE	8
#define INDEX_MASK	(BUF_SIZE - 1)

typedef struct{ 
	unsigned char data[BUF_SIZE]; 
	unsigned int head; 
	unsigned int tail; 
	unsigned int count; 
} circularBuffer; 

volatile circularBuffer rxb;  // Reception Buffer
volatile circularBuffer txb;  // Transmission Buffer

void comDrv_config(unsigned int baud, char parity, unsigned int stopbits){

	// Configure baudrate generator
	U1BRG = ((20000000+8*baud) / (16 * baud)) - 1;
	U1MODEbits.BRGH = 0;
	// Configure number of data bits, parity and number of stop bits 
	if (parity == 'e')
		U1MODEbits.PDSEL = 1;
	else if(parity == 'o')
		U1MODEbits.PDSEL = 2;
	else
		U1MODEbits.PDSEL = 0;
		
	U1MODEbits.STSEL = stopbits - 1;
    // Enable the trasmitter and receiver modules
    U1STAbits.URXEN = 1;
    U1STAbits.UTXEN = 1;
    
    //ints uart
    U1STAbits.UTXSEL = 0;
    U1STAbits.URXISEL = 0;
    
    IPC6bits.U1IP = 2;
    
    // Enable UART1
    U1MODEbits.ON = 1;
	
}

void comDrv_flushRx(void){ 
	// Initialize variables of the reception buffer 
	rxb.head = 0;
	rxb.tail = 0;
	rxb.count = 0;
} 

void comDrv_flushTx(void){ 
    // Initialize variables of the transmission buffer
	txb.head = 0;
	txb.tail = 0;
	txb.count = 0;

}

void comDrv_putc(char ch){ 
      
	while(txb.count == BUF_SIZE){ } // Wait while buffer is full 
      	
	txb.data[txb.tail] = ch;       // Copy character to the transmission buffer at position "tail" 
	txb.tail = (txb.tail + 1) & INDEX_MASK;  // Increment "tail" index (mod. BUF_SIZE) 
      	
	DisableUart1TxInterrupt();     // Begin of critical section
	txb.count++;  		       // Increment "count" variable
	EnableUart1TxInterrupt();      // End of critical section 

}

char comDrv_getc(char *pchar){ 
     
	// Test "count" variable (reception buffer) and return FALSE if it is zero 
	if (rxb.count == 0)
		return FALSE;
	DisableUart1RxInterrupt();    // Begin of critical section 
    *pchar = rxb.data[rxb.head];  // Copy character pointed by "head" to *pchar 
    rxb.count--;  // Decrement "count" variable 
    rxb.head = (rxb.head + 1) & INDEX_MASK;  // Increment "head" variable (mod BUF_SIZE)
    EnableUart1RxInterrupt();     //   End of critical section 
    return TRUE; 

}

void comDrv_puts(char *s){ 

	while(*s != NULL){	
	  	comDrv_putc(*s);
		s++;
	}
}

void _int_(24) isr_uart1(void){

	//if U1TXIF is set
	if (IFS0bits.U1TXIF == 1){ 
    //if "count" variable (transmission buffer, txb) is greater than 0 
    	if (txb.count > 0){ 
        	// Copy character pointed by "head" to U1TXREG register
        	U1TXREG = txb.data[txb.head];
        	// Increment "head" variable (mod BUF_SIZE)
        	txb.head = (txb.head + 1) & INDEX_MASK;
        	// Decrement "count" variable	
        	txb.count--;
        } 
        // if "count" variable is 0 then
        if (txb.count == 0)
        	DisableUart1TxInterrupt();
    	// Reset UART1 TX interrupt flag
    	IFS0bits.U1TXIF = 0;	
    }

	//if U1RXIF is set
	if (IFS0bits.U1RXIF == 1){  
         rxb.data[rxb.tail] = U1RXREG;   // Read character from UART and write it to the "tail" position of the reception buffer  
         // Increment "tail" variable (mod BUF_SIZE)
         rxb.tail = (rxb.tail + 1) & INDEX_MASK;
         // If reception buffer is not full (e.g. count < BUF_SIZE)
         if(rxb.count < BUF_SIZE)
         	//   increment "count" variable
         	rxb.count++;
         else
         //   increment "head" variable (discard oldest character)
         	rxb.head = (rxb.head + 1) & INDEX_MASK;
         // reset UART1 RX interrupt flag
         IFS0bits.U1RXIF = 0;
      } 
}

int main(void){ 
      
	comDrv_config(115200,'N',1); // default "pterm" parameters with TX and RX interrupts disabled 
	comDrv_flushRx(); 
	comDrv_flushTx(); 
	EnableInterrupts(); 
	while(1) 
		comDrv_puts("Teste do bloco de transmissao do device driver!...");

}
