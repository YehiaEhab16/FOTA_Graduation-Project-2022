/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :HAL                    ***********************/
/***********************   SWC (DRIVER):USN 			 ***********************/
/***********************   DATA : 5-4-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

/* Functions Implementation */
#include "../../6-Library/STD_TYPES.h"

#include "../../1-MCAL/01-GPIO/GPIO_interface.h"
#include "../../1-MCAL/12-TIMER/TIMER_interface.h"

#include "USN_config.h"
#include "USN_interface.h"
#include "USN_private.h"

//Reading Distance in cm
u8 USN_u8ReadDistance(u8 *Copy_pu8DistValue)
{
	u8 Local_u8ErrorState=OK;
	u8 Local_u8EchoReading;
	u32 Local_u32Time = 0;
	//Trigger=>Input Trigger Pulse That Starts The Sensor’s Operation
	GPIO_u8SetPinValue(GPIO_PORTB,  GPIO_PIN_5 , GPIO_PIN_HIGH);
	//TIMER_voidDelay(TIMER0,2,M);
    GPIO_u8SetPinValue(GPIO_PORTB,  GPIO_PIN_5 , GPIO_PIN_LOW);


	//Echo=>Output Pin to read the sensor’s measurements output
	GPIO_u8GetPinValue(GPIO_PORTB , GPIO_PIN_7, &Local_u8EchoReading);
	
	while(!Local_u8EchoReading);
	
	while(Local_u8EchoReading)
	{
		Local_u32Time ++;
		//TIMER_voidDelay(TIMER0,1,M);
	}
	
	//Distance = (Time (s)* Speed of Sound in(cm/s)/2
	*Copy_pu8DistValue = (Local_u32Time * 0.0340)/2;
	
	return Local_u8ErrorState;
}
