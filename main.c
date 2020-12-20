#include "stm32f401xe.h"
#include "HAL_GPIO.h"

void delay(uint32_t a);

int main(void)
{
	GPIO_TYPE testGPIO;
	
	testGPIO.port = PORTA;
	testGPIO.pin = 5;
	testGPIO.mode = OUTPUT_GENERAL;
	testGPIO.out_type = OUTPUT_PP;
	testGPIO.pull = PUPD_NONE;
	
	GPIO_Init(testGPIO);
	
	INTERRUPT_GPIO_Config(PORTC, 13, RISING_EDGE);
	INTERRUPT_GPIO_Enable(13, EXTI15_10_IRQn);

	while(1)
	{
		
	}
}

void EXTI15_10_IRQHandler(void)	
{
	// Clear the interrupt pending flag
	INTERRUPT_GPIO_Clear(13);
	
	GPIO_Toggle(PORTA, 5);
}


void delay(uint32_t a)
{
	volatile uint32_t i = 0;
	volatile uint32_t j = 0;

	for (i = 0; i < a; i++)
	{
		j++;
	}
	return;
}

