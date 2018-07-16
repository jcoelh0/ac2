//Se o switch 1 tiver a 1 ele vai acender o led 5, depois o 4 até ao 0 e depois volta do 0 ao 1 e o intervalo de mudança dos Leds é tipo 0.1 segundos
//Caso o switch 1 esteja a 0 ele faz a mesma cena mas o tempo de duração de cada led é 0.8

#include <detpic32.h>

void delay(int);

int main(void)
{
	TRISBbits.TRISB0 = 1;
	TRISE = TRISE & 0xFFF0;
	
	LATE = (LATE & 0xFFF0) | 0x0010;
	
	int sw;
	int boolean = 0;
	while(1)
	{
		sw = PORTBbits.RB0;
		if((LATE & 0x000F) == 0x0001)
			boolean = 1;
		if((LATE & 0x000F) == 0x0008)
			boolean = 0;
			
		if(boolean == 1)
			LATE = LATE << 1;
		else
			LATE = LATE >> 1;
			
		if(sw==1)
			delay(100);
		else
			delay(800);
	}

	return 0;
}	

void delay(int ms)
{
	for(; ms > 0; ms--)
	{
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}
}
