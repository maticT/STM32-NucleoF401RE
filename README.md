# STM32-NucleoF401RE
HAL Drivers implementation practice using STM32 NucleoF401RE development board

Repository tracks a hobby project of programming HAL libraries for the Nucleo development board using Keil uVision.
The goal of this project is to gain deeper understanding in the field of HAL layer development for microcontrollers.

# GPIO pins and interrupts
Project implements HAL functions for GPIO pins/registers and setting up external interrupts (EXTI registers).

Functionality is tested on a simple LED toggle program. Blue user button B1 (Port C, pin 13) executes an interrupt function, that toggles the state of the LED LD2 (Port A, pin 5).

# USART communication
Implemented USART serial communication via ST-Link. PA2 and PA3 pins are used as Tx and Rx pins respectively. Small program is added to verify communcation with PC. For datta sniffing Termite is used on the personal computer.

------------------------------------------------
README will be updated as the project progresses.
