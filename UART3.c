/**
* @file UART3.c
*
* @bried Header file for UART3 driver 
*
* @note Enabling UART3 for the Arduino MKR Zero soundboard
*
* @author Evelyn Dominguez
*/

#include "UART3.h"
#include "TM4C123GH6PM.h"


void UART3_Init(void)
{
	// Enable the clock to UART3 by setting the 
	SYSCTL->RCGCUART |= 0x08;
	
	// Enable the clock to Port C by setting the
	SYSCTL->RCGCGPIO |= 0x04;
	
	// Disable the UART3 module before configuration by clearing
	// the UARTEN bit (Bit 0) in the CTL register
	UART3->CTL &= ~0x01;
	
	// Set the baud rate by writing to the DIVINT field (Bits 15 to 0)
	// and the DIVFRAC field (Bits 5 to 0) in the IBRD and FBRD registers, respectively.
	// The integer part of the calculated constant will be written to the IBRD register,
	// while the fractional part will be written to the FBRD register.
	// N = (System Clock Frequency) / (16 * Baud Rate)
	// N = (50,000,000) / (16 * 115200) = 27.12673611 (N = 27)
	// F = ((0.12673611 * 64) + 0.5) = 8.611 (F = 8)
	UART3->IBRD = 325; //27
	UART3->FBRD = 33; //8
	
	// Configure the data word length of the UART packet to be 8 bits by 
	UART3->LCRH |= 0x60;
	
	// Enable the transmit and receive FIFOs by setting the FEN bit (Bit 4) in the LCRH register
	UART3->LCRH |= 0x10;
	
	// Select one stop bit to be transmitted at the end of a UART frame
	UART3->LCRH &= ~0x08;
	
	// Disable the parity bit by clearing the PEN bit (Bit 1) in the LCRH register
	UART3->LCRH &= ~0x02;
	
	// Enable the UART3 module after configuration by setting
	// the UARTEN bit (Bit 0) in the CTL register
	UART3->CTL |= 0x01;
	
	// Configure the PC7 (U3TX) and PC6 (U3RX) pins to use the alternate function
	GPIOC->AFSEL |= 0xC0;
	
	// Clear the PMC7 (Bits 31 to 28) and PMC6 (Bits 27 to 24) fields in the PCTL register before configuration
	GPIOC->PCTL &= ~0xFF000000;
	
	// Configure the PC7 pin to operate as a U3TX pin by writing 0x1 to the
	GPIOC->PCTL |= 0x10000000;
	
	// Configure the PC6 pin to operate as a U3RX pin by writing 0x1 to the
	GPIOC->PCTL |= 0x01000000;
	
	// Enable the digital functionality for the PC7 and PC6 pins
	GPIOC->DEN |= 0xC0;
}


char UART3_Input_Character(void)
{
	while((UART3->FR & UART3_RECEIVE_FIFO_EMPTY_BIT_MASK) != 0);
	
	return (char)(UART3->DR & 0xFF);
}

void UART3_Output_Character(char data)
{
	while((UART3->FR & UART3_TRANSMIT_FIFO_FULL_BIT_MASK) != 0);
	UART3->DR = data;
}

void UART3_Input_String(char *buffer_pointer, uint16_t buffer_size) 
{
	int length = 0;
	char character = UART3_Input_Character();
	
	while(character != UART3_CR)
	{
		if (character == UART3_BS)
		{
			if (length)
			{
				buffer_pointer--;
				length--;
				UART3_Output_Character(UART3_BS);
			}
		}
		
		else if(length < buffer_size)
		{
			*buffer_pointer = character;
			buffer_pointer++;
			length++;
			UART3_Output_Character(character);
		}
		character = UART3_Input_Character();
	}
	*buffer_pointer = 0;
}

void UART3_Output_String(char *pt)
{
	while(*pt)
	{
		UART3_Output_Character(*pt);
		pt++;
	}
}

uint32_t UART3_Input_Unsigned_Decimal(void)
{
	uint32_t number = 0;
	uint32_t length = 0;
  char character = UART3_Input_Character();
	
	// Accepts until <enter> is typed
	// The next line checks that the input is a digit, 0-9.
	// If the character is not 0-9, it is ignored and not echoed
  while(character != UART3_CR)
	{ 
		if ((character >= '0') && (character <= '9')) 
		{
			// "number" will overflow if it is above 4,294,967,295
			number = (10 * number) + (character - '0');
			length++;
			UART3_Output_Character(character);
		}
		
		// If the input is a backspace, then the return number is
		// changed and a backspace is outputted to the screen
		else if ((character == UART3_BS) && length)
		{
			number /= 10;
			length--;
			UART3_Output_Character(character);
		}
		
		character = UART3_Input_Character();
	}
	
	return number;
}

void UART3_Output_Unsigned_Decimal(int n)
{
	// Use recursion to convert decimal number
	// of unspecified length as an ASCII string
  if (n >= 10)
	{
    UART3_Output_Unsigned_Decimal(n / 10);
    n = n % 10;
  }
	
	// n is between 0 and 9
  UART3_Output_Character(n + '0');
}

uint32_t UART3_Input_Unsigned_Hexadecimal(void)
{
	uint32_t number = 0;
	uint32_t digit = 0;
	uint32_t length = 0;
  char character = UART3_Input_Character();
	
	while(character != UART3_CR)
	{
		// Initialize digit and assume that the hexadecimal character is invalid
		digit = 0x10;
		
		if ((character >= '0') && (character <= '9'))
		{
			digit = character - '0';
		}
		else if ((character>='A') && (character <= 'F'))
		{
			digit = (character - 'A') + 0xA;
		}
		else if ((character >= 'a') && (character <= 'f'))
		{
			digit = (character - 'a') + 0xA;
		}
	
		// If the character is not 0-9 or A-F, it is ignored and not echoed
    if (digit <= 0xF)
		{
      number = (number * 0x10) + digit;
      length++;
      UART3_Output_Character(character);
    }
		
		// Backspace outputted and return value changed if a backspace is inputted
		else if((character == UART3_BS) && length)
		{
			number /= 0x10;
			length--;
			UART3_Output_Character(character);
		}
		
		character = UART3_Input_Character();
  }
  return number;
}

void UART3_Output_Unsigned_Hexadecimal(uint32_t number)
{
	// Use recursion to convert the number of
	// unspecified length as an ASCII string
	if (number >= 0x10)
	{
		UART3_Output_Unsigned_Hexadecimal(number / 0x10);
		UART3_Output_Unsigned_Hexadecimal(number % 0x10);
	}
	else
	{
		if (number < 0xA)
		{
			UART3_Output_Character(number + '0');
		}
		else
		{
			UART3_Output_Character((number - 0x0A) + 'A');
		}
	}
}

void UART3_Output_Newline(void)
{
	UART3_Output_Character(UART3_CR);
	UART3_Output_Character(UART3_LF);
}



