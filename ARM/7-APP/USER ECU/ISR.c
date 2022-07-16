/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)  ***********************/
/***********************   Layer :USER ECU Application   ***********************/
/***********************   DATE : 3/7/2022 				***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../../6-Library/STD_TYPES.h"

#include "../../1-MCAL/06-CAN/CAN_interface.h"

#include "../../2-HAL/01-LED/LED_interface.h"
#include "../../2-HAL/08-COM/COM_interface.h"

#include "ISR.h"


CAN_msg CAN_TXmsg = {0x32,{0},1,CAN_ID_STD, DATA_FRAME};;
CAN_msg CAN_RXmsg;

extern LED_t Global_LED_tUpdateInd,Global_LED_tDiagInd;

void ISR_voidCanRecieve(void)
{

	CAN_voidReceive(&CAN_RXmsg, 0);
	if (CAN_RXmsg.id == CAN_UPDATE_ID)
	{
		if(CAN_RXmsg.data[0]==ISR_UPDATE_NOTF)
			COM_voidSendUpdateRequest();
		else if(CAN_RXmsg.data[0]==ISR_UPDATE_PROG)
			COM_voidSendUpdateProgress();
		else if(CAN_RXmsg.data[0]==ISR_UPDATE_COMP)
			COM_voidSendUpdateComplete();
		LED_voidLedToggle(&Global_LED_tUpdateInd);
	}
	else if (CAN_RXmsg.id == CAN_DIAG_ID)
	{
		COM_voidSendDaignosticsData(CAN_RXmsg.data[0]);
		LED_voidLedToggle(&Global_LED_tDiagInd);
	}
}

