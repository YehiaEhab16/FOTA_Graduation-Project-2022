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

	ADC_voidStartConv(&Local_u16Data,GPIO_PIN_0);
	Local_u16Data = (Local_u16Data *100)/(1500.0);

	return Local_u16Data;
}
