#include <detpic32.h>

void spi2_setClock(unsigned int clock_freq) 
{ 
	// Write SPI2BRG register(see introduction for details)
	SPI2BRG = (20000000 + clock_freq) / (2 * clock_freq) – 1;

}
