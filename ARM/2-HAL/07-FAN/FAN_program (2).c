/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :HAL                    ***********************/
/***********************   SWC (DRIVER):FAN 			 ***********************/
/***********************   DATE : 29-6-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

/* Functions Implementation */
#include "../../7-Library/STD_TYPES.h"

#include "../../1-MCAL/01-GPIO/GPIO_interface.h"

#include "FAN_config.h"
#include "FAN_interface.h"
#include "FAN_private.h"

//Turning FAN On
void FAN_voidFanOn(FAN_t* Copy_pFAN_tStructLed)
{
	if(Copy_pFAN_tStructLed->FAN_u8Connection == FAN_ACTIVE_HIGH)
		GPIO_u8SetPinValue(Copy_pFAN_tStructLed->FAN_u8Port, Copy_pFAN_tStructLed->FAN_u8Pin, GPIO_PIN_HIGH);
	else
		GPIO_u8SetPinValue(Copy_pFAN_tStructLed->FAN_u8Port, Copy_pFAN_tStructLed->FAN_u8Pin, GPIO_PIN_LOW);
}

//Turning FAN Off
void FAN_voidFanOff(FAN_t* Copy_pFAN_tStructLed)
{
	if(Copy_pFAN_tStructLed->FAN_u8Connection == FAN_ACTIVE_HIGH)
		GPIO_u8SetPinValue(Copy_pFAN_tStructLed->FAN_u8Port, Copy_pFAN_tStructLed->FAN_u8Pin, GPIO_PIN_LOW);
	else
		GPIO_u8SetPinValue(Copy_pFAN_tStructLed->FAN_u8Port, Copy_pFAN_tStructLed->FAN_u8Pin, GPIO_PIN_HIGH);
}
