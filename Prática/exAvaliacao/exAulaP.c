#include<detpic32.h>

void putc(char b){
	while(U1STAbits.UTXBF==1);
	U1TXREG=b;
}
void myputs(char *s){
	for(;*s!='\0';s++)
    	putc(*s);
}
void delay(int ms)
{
	for(; ms > 0; ms--)
	{
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}
}
// PDSEL<1:0>: Parity and Data Selection bits
// 11 = 9-bit data, no parity
// 10 = 8-bit data, odd parity
// 01 = 8-bit data, even parity
// 00 = 8-bit data, no parity


void configureUART(int baudrate,char pD,int nStop){
  	if(baudrate>=600 && baudrate<=115200){
      	U1BRG=((PBCLK+8*baudrate)/(16*baudrate))-1;
  	}
  	else{
    	U1BRG=((PBCLK+8*115200)/(16*115200))-1;
  	}
	switch(pD){
	  	case 'N':
			U1MODEbits.PDSEL=0;
			break;
		case 'E':
			U1MODEbits.PDSEL=1;
			break;
		case 'P':
			U1MODEbits.PDSEL=2;
			break;
		default:
			U1MODEbits.PDSEL=0;
  	}
  	U1MODEbits.BRGH=0;
  	if(nStop==1 || nStop==2){
    	U1MODEbits.STSEL=nStop;
  	}
	else{
   		U1MODEbits.STSEL=1;
  	}
	U1STAbits.UTXEN=1;                             //
  	U1MODEbits.ON=1;                               //ENABLE UART	RD3
}

int main(void){
	TRISEbits.TRISE4=0;

  	configureUART(115200,'N',1);
  	printf("What char would you like to send?  ");
  	char c=getChar();
	printf("\n");
	while(1){
		//putc('+');
		LATEbits.LATE4=1;
    	putc(c);												//r: 0111 0010 Y
		LATEbits.LATE4=0;
		delay(1);
	}
	return 0;
}
