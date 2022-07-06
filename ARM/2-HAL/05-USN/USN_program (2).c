/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :HAL                    ***********************/
/***********************   SWC (DRIVER):USN 			 ***********************/
/***********************   DATA : 5-4-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

/* Functions Implementation */
#include "../../7-Library/STD_TYPES.h"

#include "../../1-MCAL/01-GPIO/GPIO_interface.h"
#include "../../1-MCAL/12-TIMER/TIMER_interface.h"
#include "../../1-MCAL/14-DMA/DMA_interface.h"

#include "USN_config.h"
#include "USN_interface.h"
#include "USN_private.h"



//Reading Distance in cm
u8 USN_u8ReadDistance(u32 *Copy_pu8DistValue)
{
	u8 Local_u8ErrorState=OK;
	u32 Local_u8EchoReading=0 ;
	u32 Local_u32Time = 0;
	u8 Local_u8Pin =0;

	TIMER_voidCapture(TIM1,TIMER_RISING,2000,TIM_CHANNEL2);
	//Trigger=>Input Trigger Pulse That Starts The Sensor’s Operation
	GPIO_u8SetPinValue(GPIO_PORTA,  GPIO_PIN_0 , GPIO_PIN_HIGH);
	TIMER_Delay(TIM2,50,uSEC);
    GPIO_u8SetPinValue(GPIO_PORTA,  GPIO_PIN_0 , GPIO_PIN_LOW);

	GPIO_u8GetPinValue(GPIO_PORTA, GPIO_PIN_9,&Local_u8Pin);

	while(Local_u8Pin == 0 )
	{
      		GPIO_u8GetPinValue(GPIO_PORTA, GPIO_PIN_9,&Local_u8Pin);

	}
	TIMER_voidSelectEdge (TIM1,TIMER_FALLING,TIM_CHANNEL2 );
	while(Local_u8Pin != 0 )
	{
		GPIO_u8GetPinValue(GPIO_PORTA, GPIO_PIN_9,&Local_u8Pin);

	}
	Local_u8EchoReading = TIMER_u8GetCaptureValue(TIM1,TIM_CHANNEL2);
	TIMER_u8StopChannel (TIM1 , TIM_CHANNEL2 );
	//Distance = (Time (s)* Speed of Sound in(cm/s)/2
	*Copy_pu8DistValue = (Local_u8EchoReading* 340)/2000;
	
	return Local_u8ErrorState;
}
