/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :HAL                   ***********************/
/***********************   DATA : 25/4/2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/
#include "STD_TYPES.h"
#include "STK_interface.h"
#include "GPIO_interface.h"

#include "Ultrasonic_interface.h"


u32 Ultrasonic_u32Reading()
{
	u32 local_time = 0;
	u8 GetPinValue;
	/*  Trigger=>Input Trigger Pulse That Starts The Sensor’s Operation */
	GPIO_u8SetPinValue(GPIO_PORTB,  GPIO_PIN_5 , GPIO_PIN_HIGH);
	STK_voidDelay(2);
    GPIO_u8SetPinValue(GPIO_PORTB,  GPIO_PIN_5 , GPIO_PIN_LOW);


	/*  Echo=>Output Pin to read the sensor’s measurements output */
	while(!GPIO_u8GetPinValue(GPIO_PORTB , GPIO_PIN_7, &GetPinValue));
	/*  We can use timer to get the time */
	while(GPIO_u8GetPinValue(GPIO_PORTB , GPIO_PIN_7, &GetPinValue))
	{
		local_time ++;
		STK_voidDelay(1);
	}

	return local_time;

}

u16 Ultrasonic_u32Calc(){
	u32 Time=0;
	u16 Distance=0;
	Time = Ultrasonic_u32Reading();
	/*  Distance = (Time (s)* Speed of Sound in(cm/s)/2     */
	Distance = (Time * 0.0340)/2;
	
	return Distance;
}
