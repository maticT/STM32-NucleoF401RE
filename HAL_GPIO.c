#include "HAL_GPIO.h"
#include <stdint.h>

static void HAL_Config_Mode(GPIO_TypeDef *port , uint32_t pinNumber , uint32_t mode_type)
{
	uint32_t bitNumber = pinNumber * 2;	// Bit number for GPIO MODE register
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

static void HAL_Config_Speed(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinSpeed)
{
	uint32_t bitNumber = pinNumber * 2;
	
	switch(pinSpeed)
	{
		// (0b00)
		case(SPEED_LOW):
			port->OSPEEDR &= ~( (1<<bitNumber) | (1<<(bitNumber + 1)) ); // Reset bits bitNum and (bitNum + 1)
		break;
		
		// (0b01)
		case(SPEED_MEDIUM):
			port->OSPEEDR |= (1<<bitNumber);					// Set bit bitNumber
			port->OSPEEDR &= ~(1<<(bitNumber + 1));		// Reset bit (bitNum + 1)
		break;
		
		//	(0b10)
		case(SPEED_HIGH):
			port->OSPEEDR &= ~(1<<bitNumber);					// Reset bit bitNumber
			port->OSPEEDR	|= (1<<(bitNumber + 1));		// Set bit (bitNumber + 1)
		break;
		
		//	(0b11)
		case(SPEED_VHIGH):
			port->OSPEEDR |= (	(1<<bitNumber)	|	(1<<(bitNumber + 1)) );	// Set bits bitNum and (bitNum + 1)
		break;
		
	}// end speed type switch
}





