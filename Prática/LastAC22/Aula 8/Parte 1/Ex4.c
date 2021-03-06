#include <detpic32.h>

void configUart(unsigned int baud, char parity, unsigned int stopbits) 
{ 

   if(baud < 600 || baud > 115200)
      baud = 115200;
   if(parity != 'N' && parity != 'E' && parity != 'O')
      parity = 'N';
   if(stopbits != 1 && stopbits != 2)
      stopbits = 1;

   // Configure BaudRate Generator
   U1BRG = ((20000000 + 8 * baud) / (16 * baud)) – 1;
   U1MODEbits.BRGH = 0;
   // Configure num. of data bits (8), parity and number of stop bits
   if(parity == 'N')
      parity = 00;
   else if(parity == 'E')
      parity = 01;
   else if(parity == 'O')
      parity = 10;

   U1MODEbits.STSEL = stopbits - 1; 
   // Enable the trasmitter and receiver modules
   U1STAbits.UTXEN = 1;
   U1STAbits.URXEN = 1; 
   // Enable UART1
   U1MODEbits.ON = 1;

}
