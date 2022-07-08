/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :SERVICE                ***********************/
/***********************   SWC (DRIVER):COM 			 ***********************/
/***********************   DATE : 8-7-2022	 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../../6-Library/STD_TYPES.h"
#include "../../6-Library/BIT_MATH.h"

#include "../../1-MCAL/01-GPIO/GPIO_interface.h"
#include "../../1-MCAL/07-STK/STK_interface.h"

#include "COM_interface.h"
#include "COM_private.h"
#include "COM_config.h"

u8 Global_u8Flag=0;

void COM_voidSendUpdateRequest(void)
{
	GPIO_u8SetPinValue(COM_PORT, COM_UPDATE_OUT, GPIO_PIN_LOW);
	Global_u8Flag=1;
}

void COM_voidSendDaignosticsData(u8 Copy_u8Data)
{
	GPIO_u8SetPinValue(COM_PORT, COM_DIAG_DATA0, GET_BIT(Copy_u8Data,0));
	GPIO_u8SetPinValue(COM_PORT, COM_DIAG_DATA1, GET_BIT(Copy_u8Data,1));
	GPIO_u8SetPinValue(COM_PORT, COM_DIAG_DATA2, GET_BIT(Copy_u8Data,2));
	GPIO_u8SetPinValue(COM_PORT, COM_DIAG_OUT, GPIO_PIN_LOW);
	STK_voidDelay(500);
}

u8 COM_u8RecieveUpdateResponse(void)
{
	u8 Local_u8Flag, Local_u8Response=1;
	if(Global_u8Flag)
	{
		GPIO_u8GetPinValue(COM_PORT, COM_RES_FLAG, &Local_u8Flag);
		while(Local_u8Flag);
		GPIO_u8SetPinValue(COM_PORT, COM_UPDATE_OUT, GPIO_PIN_HIGH);
		GPIO_u8GetPinValue(COM_PORT, COM_UPDATE_IN, &Local_u8Response);
		if(Local_u8Response==1)
			Local_u8Response++;
		Global_u8Flag=0;
	}
	return Local_u8Response;
}

u8 COM_u8RecieveDaignosticsRequest(void)
{
	u8 Local_u8Data=1;
	GPIO_u8GetPinValue(COM_PORT, COM_RES_FLAG, &Local_u8Data);
	return Local_u8Data;
}
