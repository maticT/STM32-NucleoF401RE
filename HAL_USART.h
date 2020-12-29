#ifndef HAL_USART
#define HAL_USART

#include "stm32f401xe.h"

/* Include standard libs */
#include "string.h"
#include "stdlib.h"
#include "stdarg.h"
#include "stdio.h"

void USART_Initialize(char usart_char);

void USART_Print(char *msg, ...);


#endif
