#include"lcd.h"
#include"ultrasonic.h"
#include <avr/io.h>

int main(void)
{
	SREG|=(1<<7);
	uint16 distance;
	LCD_init();
	LCD_displayString("Distance = ");
	LCD_moveCursor(0,14);
	LCD_displayString("cm");
	Ultrasonic_init();
	while(1)
	{
		LCD_moveCursor(0,11);
		distance = Ultrasonic_readDistance();
		if(distance<10)
		{
			LCD_intgerToString(distance);
			LCD_displayCharacter(' ');
			LCD_displayCharacter(' ');
		}
		else if(distance<100)
		{
			LCD_intgerToString(distance);
			LCD_displayCharacter(' ');
		}
		else if(distance>99)
		{
			LCD_intgerToString(distance);
		}

	}
}
