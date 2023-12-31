/******************************************************************************
 *
 * Module: Ultrasonic Sensor
 *
 * File Name: ultrasonic.h
 *
 * Description: source file for the Ultrasonic  Sensor driver
 *
 * Author: Abdelrahman Shabrawy
 *
 *******************************************************************************/
/* INCLUDE HARDWARE ABSTRCTION LAYERS WHICH ARE ULTRASONIV  */
#include "ultrasonic.h"
#include <util/delay.h>

uint8  g_edgeCount      = 0;
uint16 g_timeHigh       = 0;

uint16 g_sensorDistance = 0;

ICU_ConfigType ICU_Configrations = {F_CPU_8,RAISING};

/*
 * • Description
 *	➢ Initialize the ICU driver as required.
 *	➢ Setup the ICU call back function.
 *	➢ Setup the direction for the trigger pin as output pin through the GPIO driver.
 */

void Ultrasonic_init(void)
{
	ICU_init(&ICU_Configrations);
	ICU_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(TRIGGERSENSOR_PORT_ID,TRIGGERSENSOR_CHANNEL_ID, PIN_OUTPUT);
}

/*
 * • Description
 *	➢ Send the Trigger pulse to the ultrasonic.
 */

void Ultrasonic_Trigger(void)
{
	GPIO_writePin(TRIGGERSENSOR_PORT_ID, TRIGGERSENSOR_CHANNEL_ID, LOGIC_HIGH);
	_delay_us(20);
	GPIO_writePin(TRIGGERSENSOR_PORT_ID, TRIGGERSENSOR_CHANNEL_ID, LOGIC_LOW);

}

/*
 * •Description
 * 	➢ Send the trigger pulse by using Ultrasonic_Trigger function.
 *	➢ Start the measurements by the ICU from this moment.
 */

uint16 Ultrasonic_readDistance(void)
{
	Ultrasonic_Trigger();
	g_sensorDistance = ((uint16)((float)g_timeHigh/57.8));
	return g_sensorDistance;
}

/*
 *	• Description
 *	 ➢ This is the call back function called by the ICU driver.
 * 	 ➢ This is used to calculate the high time (pulse time) generated by the ultrasonic sensor.
 */

void Ultrasonic_edgeProcessing(void)
{
	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		ICU_clearTimerValue();
		/* Detect falling edge */
		ICU_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2)
	{
		/* Store the High time value */
		g_timeHigh = ICU_getInputCaptureValue();
		/* Detect rising edge */
		ICU_setEdgeDetectionType(RAISING);
	}
}


