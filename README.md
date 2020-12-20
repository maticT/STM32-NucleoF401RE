# STM32-NucleoF401RE
HAL Drivers implementation practice using STM32 NucleoF401RE development board

Repository tracks a hobby project of programming HAL libraries for the Nucleo development board using Keil uVision.
The goal of this project is to gain deeper understanding in the field of HAL layer development for microcontrollers.

As of last commit, project implements HAL functions for GPIO pins/registers and setting up external interrupts (EXTI registers).

Functionality is tested on a simple LED toggle program. Blue user button B1 (Port C, pin 13) executes an interrupt function, that toggles the state of the LED LD2 (Port A, pin 5).

------------------------------------------------
README will be updated as the project progresses.
