/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)  ***********************/
/***********************   Layer :USER ECU Application   ***********************/
/***********************   DATE : 3/7/2022 				***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../../6-Library/STD_TYPES.h"

#include "../../1-MCAL/01-GPIO/GPIO_interface.h"
#include "../../1-MCAL/06-CAN/CAN_interface.h"
#include "../../3-SERVICE/03-COM/COM_interface.h"

#include "ISR.h"


CAN_msg CAN_TXmsg = {0x32,{0},1,CAN_ID_STD, DATA_FRAME};;
CAN_msg CAN_RXmsg;

void ISR_voidCanRecieve(void)
{

	CAN_voidReceive(&CAN_RXmsg, 0);
	if (CAN_RXmsg.id == CAN_UPDATE_ID)
	{
		COM_voidSendUpdateRequest();
	}
	else if (CAN_RXmsg.id == CAN_DIAG_ID_1 || CAN_RXmsg.id == CAN_DIAG_ID_2)
	{
		COM_voidSendDaignosticsData(CAN_RXmsg.data[0]);
	}
}

