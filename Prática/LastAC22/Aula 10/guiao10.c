#include <detpic32.h> 
#include "i2c.h"

int getTemperature(int *temperature) 
{ 
	int ack;
	int aux, aux2, aux3;
        // Send Start event
	i2c1_start();
        // Send Address + WR (ADDR_WR) and copy return value to "ack" variable 
	aux = i2c1_send(ADDR_WR);
	ack = aux;
	// Send Command (RTR); add return value to "ack" variable 
	aux2 = i2c1_send(RTR);
	ack += aux2;
        // Send Start event (again)
	i2c1_start();
        // Send Address + RD (ADDR_RD); add return value to "ack" variable
	aux3 = i2c1_send(ADDR_RD);
	ack += aux3;
	// Test "ack" variable; if "ack" != 0 then an error has occurred  
        //     send the Stop event, print an error message and exit loop
	*temperature=i2c1_receive(I2C_NACK);
	if(ack != 0){
	    i2c1_stop();
	    printf("Error -> ack must be 0");
	    exit(1);
	}
        // Send Stop event
	i2c1_stop();
        return ack;
} 

int main(void)
{

	int val, temperature;
	i2c1_init(TC74_CLK_FREQ);

	while(1){
	   // Receive a value from slave (send NACK as argument); copy  
           //     received value to "temperature" variable 
	   temperature = getTemperature(&val);
	   // Print "temperature" variable (syscall printInt10) 
	   printInt10(val);
           // Wait 250 ms
	   delay(250);
 	}

}
