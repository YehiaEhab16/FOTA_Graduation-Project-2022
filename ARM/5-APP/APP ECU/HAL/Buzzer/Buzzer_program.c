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
#include "Buzzer_interface.h"

u8 Buzzer_u8Pulses(void)
{
    u8 Local_u8ErrorState = OK;
    GPIO_u8SetPinValue(GPIO_PORTB,  GPIO_PIN_3 , GPIO_PIN_HIGH);
	STK_voidDelay(2000);
    GPIO_u8SetPinValue(GPIO_PORTB,  GPIO_PIN_3 , GPIO_PIN_LOW);
	STK_voidDelay(2000);

    return Local_u8ErrorState ; 
}

u8 Buzzer_u8Signal(void)
{
    u8 Local_u8ErrorState = OK;
    GPIO_u8SetPinValue(GPIO_PORTB,  GPIO_PIN_3 , GPIO_PIN_HIGH);
	STK_voidDelay(20000);

    return Local_u8ErrorState ; 
}