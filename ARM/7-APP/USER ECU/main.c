/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :USER ECU Application   ***********************/
/***********************   DATE : 3/7/2022 				 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../../6-Library/STD_TYPES.h"

#include "../../1-MCAL/06-CAN/CAN_interface.h"

#include "../../3-SERVICE/02-SYS/SYS_interface.h"
#include "../../3-SERVICE/03-COM/COM_interface.h"


#include "ISR.h"

extern CAN_msg CAN_TXmsg ;

int main(void)
{

	SYS_voidUserInit(&ISR_voidCanRecieve);

	while (1)
	{
		if (COM_u8RecieveUpdateResponse()==COM_UPDATE_APPROVED)
		{
			CAN_TXmsg.id =CAN_UPDATE_ID;
			CAN_TXmsg.data[0]= ISR_UPDATE_APPROVED;
			CAN_u8Transmit(&CAN_TXmsg);
		}
		else if (COM_u8RecieveUpdateResponse()==COM_UPDATE_REJECTED)
		{
			CAN_TXmsg.id =CAN_UPDATE_ID;
			CAN_TXmsg.data[0]= ISR_UPDATE_REJECTED;
			CAN_u8Transmit(&CAN_TXmsg);
		}

		COM_u8RecieveDaignosticsRequest();
		if (COM_u8RecieveDaignosticsRequest()==COM_DAIG_REQUESTED)
		{
			CAN_TXmsg.id =CAN_DIAG_ID_1;
			CAN_TXmsg.data[0]= ISR_DAIG_REQUESTED;
			CAN_u8Transmit(&CAN_TXmsg);

		}
	}
}
