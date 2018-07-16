#include <detpic32.h>

void putc(char byte2send);
char getc(void);
void delay(int ms);
void puts(char *str);
void configUart(unsigned int baud, char parity, unsigned int stopbits);
void isr_uart1(void);

int main(void){

   // Configure UART1 (115200, N, 8, 1)
   configUart(115200, 'N', 1);

   EnableInterrupts();
   while(1);

}

void configUart(unsigned int baud, char parity, unsigned int stopbits) 
{ 

   if(baud < 600 || baud > 115200)
      baud = 115200;
   if(parity != 'N' && parity != 'E' && parity != 'O')
      parity = 'N';
   if(stopbits != 1 && stopbits != 2)
      stopbits = 1;

   // Configure BaudRate Generator
   U1BRG = ((20000000 + 8 * baud) / (16 * baud)) - 1;
   U1MODEbits.BRGH = 0;
   // Configure num. of data bits (8), parity and number of stop bits
   if(parity == 'N')
      U1MODEbits.PDSEL = 0;
   else if(parity == 'E')
      U1MODEbits.PDSEL = 1;
   else if(parity == 'O')
      U1MODEbits.PDSEL = 0b10;

   U1MODEbits.STSEL = stopbits - 1; 
   // Enable the trasmitter and receiver modules
   U1STAbits.UTXEN = 1;
   U1STAbits.URXEN = 1; 
   // Enable UART1
   U1MODEbits.ON = 1;

   // Interrupts
   U1STAbits.URXISEL = 00;
   IPC6bits.U1IP = 3;
   IEC0bits.U1RXIE = 1;
   EnableInterrupts();

}

void _int_(24) isr_uart1(void)
{ 
   putc(U1RXREG); 
   // Clear UART1 rx interrupt flag
   IFS0bits.U1RXIF = 0;
} 

void putc(char byte2send) 
{ 
   // wait while UTXBF == 1
   while(U1STAbits.UTXBF == 1);
   // Copy byte2send to the UxTXREG register
   U1TXREG = byte2send;
}

char getc(void) 
{ 
   // If OERR == 1 then reset OERR
   if(U1STAbits.OERR == 1)
      U1STAbits.OERR = 0;
   // Wait while URXDA == 0 
   while(U1STAbits.URXDA == 0);
   // If FERR or PERR then
   if(U1STAbits.FERR == 1 || U1STAbits.PERR == 1){  
      //   read UxRXREG (to discard the character) and return 0
      char var = U1RXREG;
      return 0;
   }
   // else
   else{
      //   Return U1RXREG 
      return U1RXREG;
   }
}

void puts(char *str) 
{ 
   // use putc() function to send each charater ('\0' should not be sent)
   unsigned int i = 0;
   
   while(str[i] != '\0')
      putc(str[i++]);

} 

void delay(int ms)
{

   for(; ms > 0; ms++){
      resetCoreTimer();
      while(readCoreTimer() < 20000);
   }

}
