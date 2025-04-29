/**
 * @file Stepper_Motor.c
 *
 * @brief Source file for the Stepper_Motor driver.
 *
 * This file contains the function definitions for the Stepper_Motor driver. It uses
 * GPIO pins to provide output signals to the ULN2003 stepper motor driver.
 * 
 * The following components are used:
 *	-	28BYJ-48 5V Stepper Motor
 *  - ULN2003 Stepper Motor Driver
 *  - 3.3V / 5V Breadboard Power Supply Module (External Power Source)
 *
 * @author Aaron Nanas
 */

#include "Stepper_Motor.h"
 
void Stepper_Motor_Init()
{
	//Enable Clock A 
	SYSCTL-> RCGCGPIO |= 0x01;
	//Configure PA2,PA3,PA4, and PA5 pins as output
	GPIOA-> DIR |= 0x3C;
	//Configure PA2,PA3,PA4, and PA5 pins to function as
	//GPIO pins by clearing Bits 5 to 2 in the AFSEL register
	GPIOA->AFSEL &= ~0x3C;
	//Enable the digital functionality for the PA2,PA3,PA4, and PA5 pins
	//by setting Bits 5 to 2 in the DEN register
	GPIOA->DEN |= 0x3C;
	
	SYSCTL->RCGCGPIO |= 0x20;
	GPIOF->DIR |= 0x0C;
	GPIOF -> AFSEL &= ~0x0C;
	GPIOF->DEN |= 0x0C;
	GPIOF->DATA |= 0x0C;
}