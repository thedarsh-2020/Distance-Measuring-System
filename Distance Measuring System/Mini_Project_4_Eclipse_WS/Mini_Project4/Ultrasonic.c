/******************************************************************************
 *
 * Module: Ultrasonic Driver
 *
 * Description: Source file for Ultrasonic Driver
 *
 *******************************************************************************/

#include "icu.h"
#include "gpio.h"
#include <util/delay.h>
#include "std_types.h"
#include "Ultrasonic.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

static uint16 distance;
static uint16 timer_value;
static uint8 icu_flag = 0;
static uint8 icu_edge = 0;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function to initialize the Ultrasonic Driver
 */
void Ultrasonic_init(void)
{
	/* Create configuration structure for ICU driver
	 * by setting prescaler (8MHz) and capture Rising edge */
	Icu_ConfigType Icu_Config = {F_CPU_8, RISING};

	/* Initialize the ICU driver by taking its configuration from structure Icu_Config */
	Icu_init(&Icu_Config);

	/* Set the Call back function pointer in the ICU driver to call func. that editing capture edge */
	Icu_setCallBack(Ultrasonic_edgeProcessing);

	/* Setup the direction for the trigger pin as output pin & initiate its first state to LOW */
	GPIO_setupPinDirection(PORTB_ID, PIN5_ID, PIN_OUTPUT);
	GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_LOW);
}

/*
 * Description :
 * Function to out Trigger Pulse
 */
void Ultrasonic_Trigger(void)
{
	/* Out trigger by set pin to out logic "1" for 10 micro-sec and back to logic "0"
	 * according to ultrasonic data sheet
	 */
	GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(PORTB_ID, PIN5_ID, LOGIC_LOW);
}

/*
 * Description :
 * Function to measure the distance after get timer value from ICU
 */
uint16 Ultrasonic_readDistance(void)
{
	/* First out Trigger Pulse */
	Ultrasonic_Trigger();

	/* go into a loop waiting falling edge to get time to measure the distance*/
	for(;;)
	{
		if(icu_edge == 2)
		{
			timer_value = Icu_getInputCaptureValue();
			distance = (uint16) ( timer_value / 58.8f);
			icu_edge = 0;
			break;
		}
	}
	return distance;
}

/*
 * Description :
 * Function to control capture edge by ICU
 */
void Ultrasonic_edgeProcessing(void)
{
	icu_edge++;
	/* Clear the timer counter register to start count to get time at falling edge */
	Icu_clearTimerValue();

	/*
	 * according to icu flag, will set capture edge
	 */
	if(icu_flag == 0)
	{
		/* Detect falling edge */
		Icu_setEdgeDetectionType(FALLING);
		icu_flag++;
	}
	else
	{
		Icu_setEdgeDetectionType(RISING);
		icu_flag = 0;
	}
}
