#ifndef HAL_GPIO
#define HAL_GPIO

#include "stm32f401xe.h"

#define LOW 	0
#define HIGH 	1

#define PORTA		GPIOA
#define PORTB		GPIOB
#define PORTC		GPIOC
#define PORTD		GPIOD
#define PORTE		GPIOE
#define PORTF		GPIOF

//	MODER (Types)
#define INPUT_ANALOG			((uint32_t) 0x00)
#define OUTPUT_GENERAL		((uint32_t) 0x01)
#define	ALT_FUN						((uint32_t) 0x02)
#define AN_MODE						((uint32_t) 0x03)

//	OTYPER (Output type)
#define OUTPUT_PP					((uint32_t) 0x00)
#define OUTPUT_OPEN				((uint32_t)	0x01)

//	OSPEEDR (Output speed)
#define SPEED_LOW					((uint32_t) 0x00)
#define SPEED_MEDIUM			((uint32_t) 0x01)
#define SPEED_HIGH				((uint32_t) 0x02)
#define SPEED_VHIGH				((uint32_t) 0x03)
	
//	PUPDR (Pull-up/down)
#define	PUPD_NONE					((uint32_t) 0x00)
#define PUPD_PU						((uint32_t) 0x01)
#define PUPD_PD						((uint32_t) 0x02)
#define PUPD_RESERVED			((uint32_t) 0x03)

//	ODR	(output data register)
#define	ODR_SET						((uint32_t) 0x00)
#define ODR_RESET					((uint32_t) 0x01)

//	BSSR (Bit set reset register)
#define BSRR_SET					((uint32_t) 0x01)
#define BSRR_RESET				((uint32_t) 0x01)

//	RCC (Clock enable)
#define GPIO_CLOCK_ENABLE_PORTA			(RCC->AHB1ENR |= (1<<0))
#define GPIO_CLOCK_ENABLE_PORTB			(RCC->AHB1ENR |= (1<<1))
#define GPIO_CLOCK_ENABLE_PORTC			(RCC->AHB1ENR |= (1<<2))
#define GPIO_CLOCK_ENABLE_PORTD			(RCC->AHB1ENR |= (1<<3))
#define GPIO_CLOCK_ENABLE_PORTE			(RCC->AHB1ENR |= (1<<4))
#define GPIO_CLOCK_ENABLE_PORTH			(RCC->AHB1ENR |= (1<<7))

typedef struct {
	GPIO_TypeDef *port;
	
	uint32_t	pin;
	
	uint32_t	mode;
	
	uint32_t	out_type;
	
	uint32_t	pull;
	
	uint32_t	speed;
	
	uint32_t	alt_func;
}GPIO_TYPE;

typedef enum {
	RISING_EDGE,
	FALLING_EDGE,
	RISING_FALLING_EDGE
}edge_select;


//	GPIO CONFIGURATION
//*******************************************//
//	Configure pin mode
static void HAL_Config_Mode(GPIO_TypeDef *port , uint32_t pinNumber , uint32_t mode_type);
//	Configure pin speed
static void HAL_Config_Speed(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinSpeed);
//	Configure pin output type
static void HAL_Config_Otype(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinOtype);
//	Configure pin pull-up/down register
static void HAL_Config_Pupd(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pupdMode);
//	GPIO initialization
void GPIO_Init(GPIO_TYPE gpio_type);


//	GPIO USER PIN FUNCTIONS
//*******************************************//
//	Set/reset specific pin
void GPIO_Write(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t state);
//	Toggle specific pin
void GPIO_Toggle(GPIO_TypeDef *port, uint32_t pinNumber);

//	INTERRUPTS
//*******************************************//
void INTERRUPT_GPIO_Config(GPIO_TypeDef *port, uint32_t pinNumber, edge_select edge);
void INTERRUPT_GPIO_Enable(uint32_t pinNumber, IRQn_Type irqNumber);
void INTERRUPT_GPIO_Clear(uint32_t pinNumber);



#endif
