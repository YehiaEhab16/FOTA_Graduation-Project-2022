/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :HAL                    ***********************/
/***********************   SWC (DRIVER):LED 			 ***********************/
/***********************   DATA : 14-3-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

/* Functions Implementation */
#include "../../6-Library/STD_TYPES.h"

#include "../../1-MCAL/01-GPIO/GPIO_interface.h"

#include "LED_config.h"
#include "LED_interface.h"
#include "LED_private.h"

//Turning LED On
void LED_voidLedOn(LED_t* Copy_pLED_tStructLed)
{
	if(Copy_pLED_tStructLed->LED_u8Connection == LED_ACTIVE_HIGH)
		GPIO_u8SetPinValue(Copy_pLED_tStructLed->LED_u8Port, Copy_pLED_tStructLed->LED_u8Pin, GPIO_PIN_HIGH);
	else
		GPIO_u8SetPinValue(Copy_pLED_tStructLed->LED_u8Port, Copy_pLED_tStructLed->LED_u8Pin, GPIO_PIN_LOW);
}

//Turning LED Off
void LED_voidLedOff(LED_t* Copy_pLED_tStructLed)
{
	if(Copy_pLED_tStructLed->LED_u8Connection == LED_ACTIVE_HIGH)
		GPIO_u8SetPinValue(Copy_pLED_tStructLed->LED_u8Port, Copy_pLED_tStructLed->LED_u8Pin, GPIO_PIN_LOW);
	else
		GPIO_u8SetPinValue(Copy_pLED_tStructLed->LED_u8Port, Copy_pLED_tStructLed->LED_u8Pin, GPIO_PIN_HIGH);
}

//Toggling LED 
void LED_voidLedToggle(LED_t* Copy_pLED_tStructLed)
{
	GPIO_u8TogglePinValue(Copy_pLED_tStructLed->LED_u8Port, Copy_pLED_tStructLed->LED_u8Pin);
}