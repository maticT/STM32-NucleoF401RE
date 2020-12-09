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
	
	while(1)
	{
		GPIO_Toggle(PORTA, 5);	// Toggle pin 5
		delay(1000000);
	}
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

