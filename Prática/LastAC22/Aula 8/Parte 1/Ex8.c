#include <detpic32.h>

void putc(char byte2send);
void delay(int ms);
void puts(char *str);
void configUart(unsigned int baud, char parity, unsigned int stopbits);

int main(void){

   // Configure UART1 (115200, N, 8, 1)
   configUart(115200, 'N', 1);

   // config RB6 as output
   TRISBbits.TRISB6 = 0;

   while(1) 
   {
      // Set RB6
      LATBbits.LATB6 = 1;
      puts("12345"); 
      // Reset RB6
      LATBbits.LATB6 = 0;
   } 

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

}

void putc(char byte2send) 
{ 
   // wait while UTXBF == 1
   while(U1STAbits.UTXBF == 1);
   // Copy byte2send to the UxTXREG register
   U1TXREG = byte2send;
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
