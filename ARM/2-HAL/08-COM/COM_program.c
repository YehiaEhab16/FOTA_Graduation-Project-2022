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

#include "COM_interface.h"
#include "COM_private.h"
#include "COM_config.h"

u8 Global_u8DiagnosticsResponse=1, Global_u8UpdateResponse=COM_IDLE;
static u8 Global_u8Flag=0;

void COM_voidSendUpdateRequest(void)
{
	Global_u8Flag=1;
	GPIO_u8SetPinValue(COM_PORT, COM_DIAG_DATA0, 0);
	GPIO_u8SetPinValue(COM_PORT, COM_DIAG_DATA1, 0);
	GPIO_u8SetPinValue(COM_PORT, COM_DIAG_DATA0, 0);
	GPIO_u8SetPinValue(COM_PORT, COM_UPDATE_OUT, GPIO_PIN_LOW);
	GPIO_u8SetPinValue(COM_PORT, COM_UPDATE_OUT, GPIO_PIN_HIGH);
}

void COM_voidSendUpdateProgress(void)
{
	GPIO_u8SetPinValue(COM_PORT, COM_DIAG_DATA0, 1);
	GPIO_u8SetPinValue(COM_PORT, COM_DIAG_DATA1, 0);
	GPIO_u8SetPinValue(COM_PORT, COM_UPDATE_OUT, GPIO_PIN_LOW);
	GPIO_u8SetPinValue(COM_PORT, COM_UPDATE_OUT, GPIO_PIN_HIGH);
}

void COM_voidSendUpdateComplete(void)
{
	GPIO_u8SetPinValue(COM_PORT, COM_DIAG_DATA0, 0);
	GPIO_u8SetPinValue(COM_PORT, COM_DIAG_DATA1, 1);
	GPIO_u8SetPinValue(COM_PORT, COM_UPDATE_OUT, GPIO_PIN_LOW);
	GPIO_u8SetPinValue(COM_PORT, COM_UPDATE_OUT, GPIO_PIN_HIGH);
	Global_u8Flag=0;
}

void COM_voidSendDaignosticsData(u8 Copy_u8Data)
{
	GPIO_u8SetPinValue(COM_PORT, COM_DIAG_DATA0, GET_BIT(Copy_u8Data,0));
	GPIO_u8SetPinValue(COM_PORT, COM_DIAG_DATA1, GET_BIT(Copy_u8Data,1));
	GPIO_u8SetPinValue(COM_PORT, COM_DIAG_DATA2, GET_BIT(Copy_u8Data,2));
	GPIO_u8SetPinValue(COM_PORT, COM_DIAG_OUT, GPIO_PIN_LOW);
	GPIO_u8SetPinValue(COM_PORT, COM_DIAG_OUT, GPIO_PIN_HIGH);
}

void COM_voidRecieveUpdateResponse(void)
{
	GPIO_u8GetPinValue(COM_PORT, COM_UPDATE_IN, &Global_u8UpdateResponse);
	if(Global_u8UpdateResponse)
	{
		if(!Global_u8Flag)
				Global_u8UpdateResponse++;
		Global_u8UpdateResponse++;
	}
}

void COM_voidRecieveDaignosticsRequest(void)
{
	Global_u8DiagnosticsResponse=COM_DAIG_REQUESTED;
}
