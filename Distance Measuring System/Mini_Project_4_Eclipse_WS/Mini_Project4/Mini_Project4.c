/**************************************************************************************************
 *
 * Author      : Mustafa Muhammad
 *
 * Description : Distance Measuring System
 *
 **************************************************************************************************/

#include "std_types.h"
#include "lcd.h"
#include "Ultrasonic.h"
#include <avr/io.h> /* To use the SREG register */

int main(void)
{

	uint16 dis;

	/* Initialize the LCD & show distance */
	LCD_init();
	LCD_displayStringRowColumn(0, 0, "Distance =    cm");

	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);

	/* Initialize the Ultrasonic */
	Ultrasonic_init();

	for(;;)
	{
		/* Get the distance from Ultrasonic_readDistance func */
		dis = Ultrasonic_readDistance();

		/* set cursor on LCD */
		LCD_moveCursor(0, 11);

		/* Display the distance according to the number of its Digits */
		if(dis < 10)
		{
			LCD_intgerToString(dis);
			LCD_displayCharacter(' ');
			LCD_displayCharacter(' ');
		}
		else if(dis < 100)
		{
			LCD_intgerToString(dis);
			LCD_displayCharacter(' ');
		}
		else
		{
			LCD_intgerToString(dis);
		}
	}
}
