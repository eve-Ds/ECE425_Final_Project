
#include "TM4C123GH6PM.h"
#include "stdlib.h"
#include "SysTick_Delay.h"

#include "UART3.h"
#include "UART_BLE.h"
#include "UART0.h"
#include "stdio.h"
#include "Stepper_Motor.h"

#include "string.h"
#include "Timer_0A_Interrupt.h"

#define BUFFER_SIZE   128

void Process_UART_BLE_Data(char UART_BLE_Buffer[]);
void Timer_0A_Stepper_Motor(void);
extern int motorActive;

int main(void)
{		
	// Initialize the SysTick timer used to provide blocking delay functions
	SysTick_Delay_Init();
	
	UART3_Init();
	
	// Initialize an array to store the characters received from the Adafruit BLE UART module
	char UART_BLE_Buffer[BUFFER_SIZE];

	// Initialize the UART0 module which will be used to print characters on the serial terminal
	UART0_Init();
	
	
	// Initialize the UART1 module which will be used to communicate with the Adafruit BLE UART module
	UART_BLE_Init();
	
	//Initialize the pins used by the 28BYJ-48 Stepper Motor and the ULN2003 Stepper Motor Driver
	Stepper_Motor_Init();
	Timer_0A_Interrupt_Init(Timer_0A_Stepper_Motor);
	
	// Provide a short delay after initialization and reset the Adafruit BLE UART module
	SysTick_Delay1ms(1000);
	UART_BLE_Reset();
	
	// Send a message to the Adafruit BLE UART module to check if the connection is stable
	UART_BLE_Output_String("UART BLE Active");
	UART_BLE_Output_String(" ");
	SysTick_Delay1ms(1000);
	
	while(1) {
		
	if(UART_BLE_Available())
	{
		SysTick_Delay1ms(1000);
		int string_size = UART_BLE_Input_String(UART_BLE_Buffer, BUFFER_SIZE);
		
		UART0_Output_String("String Size: ");
		UART0_Output_Unsigned_Decimal(string_size);
		UART0_Output_Newline();
		
		UART0_Output_String("UART BLE Data: ");
		
		for (int i = 0; i < string_size; i++)
		{
			if (UART_BLE_Buffer[i] == 0)
			{
				UART0_Output_Character('A');
			}
			else
			{
				UART0_Output_Character(UART_BLE_Buffer[i]);
			}
		}
		
		UART0_Output_Newline();
		Process_UART_BLE_Data(UART_BLE_Buffer);
		UART0_Output_Newline();
	}
}
	
}

void Process_UART_BLE_Data(char UART_BLE_Buffer[])
{
	if (Check_UART_BLE_Data(UART_BLE_Buffer, "PAUSE"))
	{
		UART3_Output_String("PAUSE");
		SysTick_Delay1ms(1300);
		Stop_Stepper_Motor();
	}
	
	
	else if (Check_UART_BLE_Data(UART_BLE_Buffer, "RESUME"))
	{
		UART3_Output_String("RESUME");
		SysTick_Delay1ms(1300); 
		Start_Stepper_Motor();
	}
	
	else if (Check_UART_BLE_Data(UART_BLE_Buffer, "VOLUME UP"))
	{
		UART3_Output_String("VOLUME UP");
	}
	
	else if (Check_UART_BLE_Data(UART_BLE_Buffer, "VOLUME DOWN"))
	{
		UART3_Output_String("VOLUME DOWN");
	}
		
	else if (Check_UART_BLE_Data(UART_BLE_Buffer, "ATZ"))
	{
		UART0_Output_String("UART BLE Reset Command Issued");
		UART3_Output_Newline();
	}
	
	else if (Check_UART_BLE_Data(UART_BLE_Buffer, "OK"))
	{
		// Read the last received data from the UART Receive Buffer
		
		// Note: After a reset is issued and the module responds with "OK",
		// the module transmits a null character. This prevents the null character
		// from being added to the buffer when the user sends a command string for the first time
		char character = UART_BLE_Input_Character();
		
		UART0_Output_String("UART BLE Response Received");
		UART3_Output_Newline();
	}

	else {
		UART3_Output_String(UART_BLE_Buffer);
		SysTick_Delay1ms(1300);
		Start_Stepper_Motor();
	} 
	/*
	else 
	{
		UART0_Output_String("UART BLE Command Not Found");
		UART3_Output_String(UART_BLE_Buffer);
		UART3_Output_Newline();
	} */
	
}
int step_index = 0;
const uint8_t half_step[] = {0x04, 0x0C, 0x08, 0x18, 0x10, 0x30, 0x20, 0x24};

	void Timer_0A_Stepper_Motor(void) {
		if (motorActive) {
			if (step_index >= 8)
				{
			step_index = 0;
		}
		GPIOA->DATA = (GPIOA->DATA & ~0x3C) | half_step[step_index];
		step_index = step_index + 1;
	}
}