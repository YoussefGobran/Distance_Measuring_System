#include<util\delay.h>
#include"ultrasonic.h"
#include"gpio.h"
#include"icu.h"
#include"common_macros.h"

uint16 ticks = 0;
uint8 edge= RAISING;

void Ultrasonic_init(void)
{
	GPIO_setupPinDirection(PORTB_ID, PIN5_ID, PIN_OUTPUT);
	ICU_ConfigType Init ={F_CPU_8,RAISING};
	ICU_setCallBack(Ultrasonic_edgeProcessing);
	ICU_init(&Init);
	GPIO_writePin(TRIGGER_PORT, TRIGGER_PIN, LOGIC_LOW);
}
void Ultrasonic_Trigger(void)
{
	GPIO_writePin(TRIGGER_PORT, TRIGGER_PIN, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(TRIGGER_PORT, TRIGGER_PIN, LOGIC_LOW);
}
uint16 Ultrasonic_readDistance(void)
{
	Ultrasonic_Trigger();
	return (ticks/58+1);
}
void Ultrasonic_edgeProcessing(void)
{
	if(edge == RAISING)
	{
		ICU_setEdgeDetectionType(FALLING);
		edge = FALLING;
	}
	else if(edge == FALLING)
	{
		ticks=ICU_getInputCaptureValue();
		ICU_setEdgeDetectionType(RAISING);
		edge = RAISING;
	}
	ICU_clearTimerValue();
}
