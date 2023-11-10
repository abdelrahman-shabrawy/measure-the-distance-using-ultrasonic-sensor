/*
 ============================================================================
 Name        : Mini_Project4.c
 Author      : Abdelrahman Shabrawy
 Description : ULTRASONIC Project
 Date        : 1/07/2023
 ============================================================================
 */
#include <avr/io.h> /* To use the SREG register */

/* INCLUDE HARDWARE ABSTRCTION LAYERS WHICH ARE LCD ,ULTRASONIC SENSOR */
#include "../HAL/ULTRASONIC/ultrasonic.h"
#include "../HAL/LCD/lcd.h"
/* INCLUDE MICROCONTROLLER ABSTRCTION LAYERS WHICH ARE ADC and pwm */
#include "../MCAL/ICU/icu.h"
#include "../MCAL/GPIO/gpio.h"
#include "../LIBRARIES/std_types.h"



int main(void)
{
	uint16 ultrasonicDistance = 0;
	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);
	Ultrasonic_init();
	LCD_init();
	LCD_displayString("Distance =    CM");
	while(1)
	{
		ultrasonicDistance = Ultrasonic_readDistance();
		LCD_moveCursor(0, 10);
		if(ultrasonicDistance >= 100)
		{
			LCD_intgerToString(ultrasonicDistance);
		}
		else
		{
			LCD_intgerToString(ultrasonicDistance);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}

	}
}
