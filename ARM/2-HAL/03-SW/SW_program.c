/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :HAL                    ***********************/
/***********************   SWC (DRIVER):SW 			 ***********************/
/***********************   DATA : 14-3-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/


/* Functions Implementation */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "STK_interface.h"

#include "SW_config.h"
#include "SW_interface.h"
#include "SW_private.h"

u8 SW_u8ReadSwicth(SW_t* Copy_pSW_tStruct)
{
	u8 Local_u8SwicthValue, Local_u8Value;
	if(Copy_pSW_tStruct->SW_u8Connection==SW_u8PULL_UP)
	{
		GPIO_u8GetPinValue(Copy_pSW_tStruct->SW_u8Port, Copy_pSW_tStruct->SW_u8Pin, &Local_u8Value);
		if(Local_u8Value==0)
			Local_u8SwicthValue = PRESSED;
		else
			Local_u8SwicthValue = NOT_PRESSED;
	}
	else
	{
		GPIO_u8GetPinValue(Copy_pSW_tStruct->SW_u8Port, Copy_pSW_tStruct->SW_u8Pin, &Local_u8Value);
		Local_u8SwicthValue = Local_u8Value;
	}
	STK_voidDelay(Copy_pSW_tStruct->SW_u32DebounceTime);
	return Local_u8SwicthValue;
}