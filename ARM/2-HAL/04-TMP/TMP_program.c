/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :HAL                    ***********************/
/***********************   SWC (DRIVER):TMP 			 ***********************/
/***********************   DATA : 5-4-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

/* Functions Implementation */
#include "../../6-Library/STD_TYPES.h"

#include "../../1-MCAL/01-GPIO/GPIO_interface.h"
#include "../../1-MCAL/13-ADC/ADC_interface.h"

#include "TMP_config.h"
#include "TMP_interface.h"
#include "TMP_private.h"
u16 data=0;

//Reading Temperature Value
u8 TMP_u8ReadValue(u8 *Copy_pu8TempValue)
{
	u8 Local_u8ErrorState=OK;
	while (1){
		ADC_VidStartConv(&data,GPIO_PIN_0);
		*Copy_pu8TempValue = (data * Voltage*100)/1023;
	}
	return Local_u8ErrorState;
}