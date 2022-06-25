/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :HAL                    ***********************/
/***********************   SWC (DRIVER):BZR 			 ***********************/
/***********************   DATA : 5-4-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

/* Functions Implementation */
#include "../../6-Library/STD_TYPES.h"

#include "../../1-MCAL/01-GPIO/GPIO_interface.h"

#include "BZR_config.h"
#include "BZR_interface.h"
#include "BZR_private.h"

//Turning Buzzer On
void BZR_voidOn(u8 Copy_u8Port,u8 Copy_u8Pin)
{
	GPIO_u8SetPinValue(Copy_u8Port, Copy_u8Pin, GPIO_PIN_HIGH);
}

//Turning Buzzer Off
void BZR_voidOff(u8 Copy_u8Port,u8 Copy_u8Pin)
{
	GPIO_u8SetPinValue(Copy_u8Port, Copy_u8Pin, GPIO_PIN_LOW);
}

//Toggling Buzzer 
void BZR_voidToggle(u8 Copy_u8Port,u8 Copy_u8Pin)
{
	GPIO_u8TogglePinValue(Copy_u8Port, Copy_u8Pin);
}