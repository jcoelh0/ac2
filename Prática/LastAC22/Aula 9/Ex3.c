#define  DisableUart1RxInterrupt()    IEC0bits.U1RXIE = 0
#define  EnableUart1RxInterrupt()     IEC0bits.U1RXIE = 1
#define  DisableUart1TxInterrupt()    IEC0bits.U1TXIE = 0 
#define  EnableUart1TxInterrupt()     IEC0bits.U1TXIE = 1

#define BUF_SIZE	8

typedef struct{ 
	unsigned char data[BUF_SIZE]; 
	unsigned int head; 
	unsigned int tail; 
    unsigned int count; 
} circularBuffer; 

void comDrv_flushRx(void){ 
      // Initialize variables of the reception buffer 

	volatile circularBuffer rxb;  // Reception Buffer

} 

void comDrv_flushTx(void){ 
      // Initialize variables of the transmission buffer

	volatile circularBuffer txb;  // Transmission Buffer

}
