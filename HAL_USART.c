#include "HAL_USART.h"

void USART_Initialize(char usart_ch){
	if(usart_ch == 2)
	{
		// Enable USART2 clock
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
		
		// Enable GPIOA clock (PA2 is used as TX pin, PA3 as RX)
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
		// Set pins PA2 and PA3 to alternate function mode
		GPIOA->MODER |= GPIO_MODER_MODER2_1 | GPIO_MODER_MODER3_1;
		GPIOA->MODER &= ~(GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0);
		// Set pins PA2 and PA3 to output push-pull mode - Pins must not be floating for USART communication
		GPIOA->OTYPER &= ~(GPIO_OTYPER_OT2 | GPIO_OTYPER_OT3);
		// Activate alternate function mode USART2 for pin PA2
		GPIOA->AFR[0] |= GPIO_AFRL_AFRL2_0 | GPIO_AFRL_AFRL2_1 | GPIO_AFRL_AFRL2_2;
		GPIOA->AFR[0] &= ~GPIO_AFRL_AFRL2_3;
		// Activate alternate function mode USART2 for pin PA3
		GPIOA->AFR[0] |= GPIO_AFRL_AFRL3_0 | GPIO_AFRL_AFRL3_1 | GPIO_AFRL_AFRL3_2;
		GPIOA->AFR[0] &= ~GPIO_AFRL_AFRL3_3;
		
		// Configure USART2
		// baudrate = clock / (baudrate * 16)
		// The peripheral clock is runing at 16 Mhz -> baudrate = 16000000 / (9600 * 16) = 104,1666667
		// hex(104) = 0x68
		// 0,1666667 * 16 = 2,666667
		// hex(2,666667) = 2
		USART2->BRR = 0x682;
		USART2->CR1 |= USART_CR1_TE;
		//USART2->CR1 |= USART_CR1_RE;
		USART2->CR1	|= USART_CR1_UE;
	}
	
}

void USART_Print(char *msg, ...)
{
	char buff[80];
	
	va_list args;
	va_start(args, msg);
	vsprintf(buff, msg, args);
	
	for(uint32_t i = 0; i < strlen(buff); i++)
	{
		USART2->DR = buff[i];
		while( !(USART2->SR & USART_SR_TXE)	);
	}
}


