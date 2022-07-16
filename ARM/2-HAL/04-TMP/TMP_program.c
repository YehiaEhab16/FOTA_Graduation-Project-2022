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

//Reading Temperature Value
u16 TMP_u16ReadValue(void)
{
	u16 Local_u16Data=0;
	f32 Local_u8Temp =0 ;
	ADC_voidStartConv(&Local_u16Data,CHANNEL_0);
	Local_u16Data = TEMP_RESOLUTION * Local_u16Data ;
	Local_u8Temp = (f32)(Local_u16Data /10)*TEMP_RELATION;
	Local_u16Data = (u16)Local_u8Temp ;
	return Local_u16Data;
}
