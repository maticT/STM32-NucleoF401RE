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
