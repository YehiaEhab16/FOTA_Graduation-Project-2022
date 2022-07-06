/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :HAL                    ***********************/
/***********************   SWC (DRIVER):SW 				 ***********************/
/***********************   DATE : 11-5-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

/* Functions Implementation */
#include "../../7-Library/STD_TYPES.h"

#include "../../1-MCAL/01-GPIO/GPIO_interface.h"

#include "SW_config.h"
#include "SW_interface.h"
#include "SW_private.h"

//Reading Switch Value
u8 SW_u8ReadSwitch(SW_t* Copy_pSW_tStruct)
{
	u8 Local_u8SwicthValue, Local_u8Value;
	if(Copy_pSW_tStruct->SW_u8Connection==SW_PULL_UP)
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
	return Local_u8SwicthValue;
} 
