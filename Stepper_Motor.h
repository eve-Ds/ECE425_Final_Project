/**
 * @file Stepper_Motor.h
 *
 * @brief Header file for the Stepper_Motor driver.
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

#include "TM4C123GH6PM.h"


/**
 * @brief Initializes stepper motor
 *
 * @param none
 *
 * @return None
 */
void Stepper_Motor_Init();

/**
 * @brief Controls the stop of the motor
 *
 * @param void
 *
 * @return None
 */
void Stop_Stepper_Motor(void);
/**
 * @brief Controls the start of the motor
 *
 * @param void
 *
 * @return None
 */
void Start_Stepper_Motor(void);