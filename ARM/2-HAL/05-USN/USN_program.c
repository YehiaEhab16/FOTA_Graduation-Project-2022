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
#include "../../1-MCAL/02-RCC/RCC_interface.h"

#include "USN_config.h"
#include "USN_interface.h"
#include "USN_private.h"



//Reading Distance in cm
u8 USN_u8ReadDistance(u32 *Copy_pu32DistValue)
{
	u8 Local_u8ErrorState=OK;
	u32 Local_u32EchoReading=0;
	u8 Local_u8Pin=0;

	TIMER_voidCapture(TIM1,TIMER_RISING,2000,USN_TIM_CHANNEL);
	//Trigger=>Input Trigger Pulse That Starts The Sensor’s Operation
	GPIO_u8SetPinValue(USN_PORT,  USN_TRIG_PIN, GPIO_PIN_HIGH);
	TIMER_Delay(TIM2,50,uSEC);
    GPIO_u8SetPinValue(USN_PORT,  USN_TRIG_PIN, GPIO_PIN_LOW);

	while(Local_u8Pin == 0)
   		GPIO_u8GetPinValue(GPIO_PORTA, USN_ECHO_PIN,&Local_u8Pin);

	TIMER_voidSelectEdge (TIM1,TIMER_FALLING,USN_TIM_CHANNEL);
	while(Local_u8Pin != 0)
		GPIO_u8GetPinValue(GPIO_PORTA, USN_ECHO_PIN,&Local_u8Pin);
	Local_u32EchoReading = TIMER_u8GetCaptureValue(TIM1,USN_TIM_CHANNEL);

	TIMER_StopTimer(TIM1);
	TIMER_u8StopChannel(TIM1, USN_TIM_CHANNEL);
	//Distance = (Time (s)* Speed of Sound in(cm/s)/2
	*Copy_pu32DistValue = (Local_u32EchoReading* 340)/20000;
	
	return Local_u8ErrorState;
}
