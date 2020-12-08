#include "stm32f401xe.h"

int main(void)
{
	// Initialize the clock for the Port A
	RCC->AHB1ENR |= 1;
	
	// Configure Pin5 on GPIOA
	GPIOA->MODER |= ( (0<<11)	|	(1<<10));		// General purpose output mode
	GPIOA->OTYPER |= (0<<5);	
	
	while(1)
	{
		GPIOA->BSRR = (1<<(21));	// Set pin 5 LOW
		for(int i = 0; i <= 5000000; i++);
		GPIOA->BSRR = (1<<5);	// Set pin 5 HIGH
		for(int i = 0; i <= 5000000; i++);	
		
	}
}
