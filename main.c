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

	USART_Initialize(2);
	
	while(1)
	{
		//USART_Print("Hello world!\n");
		
		delay(1000000);
	}
}

void EXTI15_10_IRQHandler(void)	
{
	// Clear the interrupt pending flag
	INTERRUPT_GPIO_Clear(13);
	
	GPIO_Toggle(PORTA, 5);
	USART_Print("Hello world! I'm %d years old\n", 25);
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

