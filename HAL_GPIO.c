#include "HAL_GPIO.h"

/*************MODER configuration*************/
static void HAL_Config_Mode(GPIO_TypeDef *port , uint32_t pinNumber , uint32_t mode_type)
{
	uint32_t bitNumber;
	bitNumber = pinNumber * 2;	// Bit number for GPIO MODE register
	switch(mode_type)
	{
		//	(0b00)
		case INPUT_ANALOG:
			port->MODER &= ~( (1<<bitNumber) | (1<<(bitNumber + 1)) ); // Reset bits bitNum and (bitNum + 1)
		break;
		
		//	(0b01)
		case OUTPUT_GENERAL:
			port->MODER |= (1<<bitNumber);					// Set bit bitNum
			port->MODER &= ~(1<<(bitNumber + 1));		// Reset bit (bitNum + 1)
		break;
		
		//	(0b10)
		case ALT_FUN:
			port->MODER &= ~(1<<(bitNumber));				// Reset bit bitNum
			port->MODER |= (1<<(bitNumber + 1));		// Set bit (bitNum + 1)
		break;
		
		//	(0b11)
		case AN_MODE:
			port->MODER |= ( (1<<bitNumber) | (1<<(bitNumber + 1)) );	// Set bits bitNum and (bitNum + 1)
		break;
		
	}// end mode type switch
}
/********************************************/


/***********OSPEEDR configuration************/
static void HAL_Config_Speed(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinSpeed)
{
	uint32_t bitNumber = pinNumber * 2;
	
	switch(pinSpeed)
	{
		// (0b00)
		case SPEED_LOW:
			port->OSPEEDR &= ~( (1<<bitNumber) | (1<<(bitNumber + 1)) ); // Clear bits bitNum and (bitNum + 1)
		break;
		
		// (0b01)
		case SPEED_MEDIUM:
			port->OSPEEDR |= (1<<bitNumber);					// Set bit bitNumber
			port->OSPEEDR &= ~(1<<(bitNumber + 1));		// Clear bit (bitNum + 1)
		break;
		
		//	(0b10)
		case SPEED_HIGH:
			port->OSPEEDR &= ~(1<<bitNumber);					// Clear bit bitNumber
			port->OSPEEDR	|= (1<<(bitNumber + 1));		// Set bit (bitNumber + 1)
		break;
		
		//	(0b11)
		case SPEED_VHIGH:
			port->OSPEEDR |= (	(1<<bitNumber)	|	(1<<(bitNumber + 1)) );	// Set bits bitNum and (bitNum + 1)
		break;
		
	}// end speed type switch
}
/********************************************/

/***********OTYPER configuration*************/
static void HAL_Config_Otype(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinOtype)
{
	switch(pinOtype)
	{
		// Output push-pull
		case OUTPUT_PP:
			port->OTYPER &= ~(1<<pinNumber);			// Clear bit pinNumber
		break;
		
		case OUTPUT_OPEN:
			port->OTYPER |= (1<<pinNumber);				// Set bit pinNumber
		break;
	}// end output type switch
}
/********************************************/

/***********PUPDR configuration**************/
static void HAL_Config_Pupd(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pupdMode)
{
	uint32_t bitNumber = pinNumber * 2;
	switch(pupdMode)
	{
		case PUPD_NONE:
			port->PUPDR &= ~( (1<<bitNumber) | (1<<(bitNumber + 1)) ); // Reset bits bitNum and (bitNum + 1)
		break;
		
		case PUPD_PU:
			port->PUPDR |= (1<<bitNumber);					// Set bit bitNumber
			port->PUPDR &= ~(1<<(bitNumber + 1));		// Clear bit (bitNumber + 1)
		break;
		
		case PUPD_PD:
			port->PUPDR &= ~(1<<bitNumber);					// Clear bit bitNumber
			port->PUPDR |= (1<<(bitNumber + 1));		// Set bit bitNumber
		break;
		
		case PUPD_RESERVED:
			port->PUPDR |= (	(1<<bitNumber)	|	(1<<(bitNumber + 1)) );	// Set bits bitNumber and (bitNumber + 1)
		break;
	}//	end pupd switch
}

/***********BSRR configuration****************/
void GPIO_Write(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t state)
{
	if(state)
	{
		port->BSRR = (1<<pinNumber);
	}
	else
	{
		port->BSRR = (1<<(pinNumber + 16));
	}
}

/***********BSRR configuration****************/
void GPIO_Toggle(GPIO_TypeDef *port, uint32_t pinNumber)
{
	port->ODR ^=(1<<pinNumber);
}

/***********CLOCK initialization**************/
void GPIO_Init(GPIO_TYPE gpio_type)
{
	if(gpio_type.port == PORTA)
		GPIO_CLOCK_ENABLE_PORTA;
	
	if(gpio_type.port == PORTB)
		GPIO_CLOCK_ENABLE_PORTB;
	
	if(gpio_type.port == PORTC)
		GPIO_CLOCK_ENABLE_PORTC;
	
	if(gpio_type.port == PORTD)
		GPIO_CLOCK_ENABLE_PORTD;
	
	if(gpio_type.port == PORTE)
		GPIO_CLOCK_ENABLE_PORTE;
	
	HAL_Config_Mode(gpio_type.port, gpio_type.pin, gpio_type.mode);
	HAL_Config_Otype(gpio_type.port, gpio_type.pin, gpio_type.out_type);
	HAL_Config_Pupd(gpio_type.port, gpio_type.pin, gpio_type.pull);
	HAL_Config_Speed(gpio_type.port, gpio_type.pin, gpio_type.speed);
}


/***********Interrupt initialization***********/
void INTERRUPT_GPIO_Config(GPIO_TypeDef *port, uint32_t pinNumber, edge_select edge) 
{
	// Enable SYSCFG and used PORT clocks
	RCC->APB2ENR = RCC_APB2ENR_SYSCFGEN;
	
	if(port == PORTA)
	{
		GPIO_CLOCK_ENABLE_PORTA;
		
		switch(pinNumber)
		{
			// Configure the appropriate EXTI registers for each pin
			case 0:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PA;
			break;
			
			case 1:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI1_PA;
			break;

			case 2:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI2_PA;
			break;

			case 3:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI3_PA;
			break;
			
			case 4:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI4_PA;
			break;
			
			case 5:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI5_PA;
			break;
			
			case 6:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI6_PA;
			break;
			
			case 7:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI7_PA;
			break;
			
			case 8:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI8_PA;
			break;
			
			case 9:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI9_PA;
			break;
			
			case 10:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI10_PA;
			break;
			
			case 11:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI11_PA;
			break;			
			
			case 12:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI12_PA;
			break;

			case 13:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI13_PA;
			break;
			
			case 14:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI14_PA;
			break;
			
			case 15:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI15_PA;
			break;
		}
	}
		
	if(port == PORTB)
	{
		GPIO_CLOCK_ENABLE_PORTB;
		
		switch(pinNumber)
		{
			// Configure the appropriate EXTI registers for each pin
			case 0:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PB;
			break;
			
			case 1:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI1_PB;
			break;

			case 2:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI2_PB;
			break;

			case 3:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI3_PB;
			break;
			
			case 4:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI4_PB;
			break;
			
			case 5:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI5_PB;
			break;
			
			case 6:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI6_PB;
			break;
			
			case 7:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI7_PB;
			break;
			
			case 8:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI8_PB;
			break;
			
			case 9:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI9_PB;
			break;
			
			case 10:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI10_PB;
			break;
			
			case 11:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI11_PB;
			break;			
			
			case 12:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI12_PB;
			break;

			case 13:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI13_PB;
			break;
			
			case 14:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI14_PB;
			break;
			
			case 15:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI15_PB;
			break;
		}
	}
	
	if(port == PORTC)
	{
		GPIO_CLOCK_ENABLE_PORTC;
		
		switch(pinNumber)
		{
			// Configure the appropriate EXTI registers for each pin
			case 0:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PC;
			break;
			
			case 1:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI1_PC;
			break;

			case 2:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI2_PC;
			break;

			case 3:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI3_PC;
			break;
			
			case 4:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI4_PC;
			break;
			
			case 5:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI5_PC;
			break;
			
			case 6:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI6_PC;
			break;
			
			case 7:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI7_PC;
			break;
			
			case 8:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI8_PC;
			break;
			
			case 9:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI9_PC;
			break;
			
			case 10:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI10_PC;
			break;
			
			case 11:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI11_PC;
			break;			
			
			case 12:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI12_PC;
			break;

			case 13:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI13_PC;
			break;
			
			case 14:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI14_PC;
			break;
			
			case 15:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI15_PC;
			break;
		}
	}
	
	if(port == PORTD)
	{
		GPIO_CLOCK_ENABLE_PORTD;
	
		switch(pinNumber)
		{
			// Configure the appropriate EXTI registers for each pin
			case 0:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PD;
			break;
			
			case 1:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI1_PD;
			break;

			case 2:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI2_PD;
			break;

			case 3:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI3_PD;
			break;
			
			case 4:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI4_PD;
			break;
			
			case 5:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI5_PD;
			break;
			
			case 6:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI6_PD;
			break;
			
			case 7:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI7_PD;
			break;
			
			case 8:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI8_PD;
			break;
			
			case 9:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI9_PD;
			break;
			
			case 10:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI10_PD;
			break;
			
			case 11:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI11_PD;
			break;			
			
			case 12:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI12_PD;
			break;

			case 13:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI13_PD;
			break;
			
			case 14:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI14_PD;
			break;
			
			case 15:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI15_PD;
			break;
		}
	}
		
	if(port == PORTE)
	{
		GPIO_CLOCK_ENABLE_PORTE;
	
		switch(pinNumber)
		{
			// Configure the appropriate EXTI registers for each pin
			case 0:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PE;
			break;
			
			case 1:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI1_PE;
			break;

			case 2:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI2_PE;
			break;

			case 3:
				SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI3_PE;
			break;
			
			case 4:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI4_PE;
			break;
			
			case 5:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI5_PE;
			break;
			
			case 6:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI6_PE;
			break;
			
			case 7:
				SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI7_PE;
			break;
			
			case 8:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI8_PE;
			break;
			
			case 9:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI9_PE;
			break;
			
			case 10:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI10_PE;
			break;
			
			case 11:
				SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI11_PE;
			break;			
			
			case 12:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI12_PE;
			break;

			case 13:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI13_PE;
			break;
			
			case 14:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI14_PE;
			break;
			
			case 15:
				SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI15_PE;
			break;
		}
	}
	
	if(edge == RISING_EDGE)
	{
		EXTI->RTSR |= (1<<pinNumber);
	}
	if(edge == FALLING_EDGE)
	{
		EXTI->FTSR |= (1<<pinNumber);
	}
	if(edge == RISING_FALLING_EDGE)
	{
		EXTI->RTSR |= (1<<pinNumber);
		EXTI->FTSR |= (1<<pinNumber);
	}
}

/*************INTERRUPT enable*************/
void INTERRUPT_GPIO_Enable(uint32_t pinNumber, IRQn_Type irqNumber)
{
	// Enable interrupt in EXTI
	EXTI->IMR |= (1<<pinNumber);
	// Enable interrupt in NVIC
	NVIC_EnableIRQ(irqNumber);
}

/************INTERRUPT clear***************/
void INTERRUPT_GPIO_Clear(uint32_t pinNumber)
{
	EXTI->PR |= (1<<pinNumber);
}

