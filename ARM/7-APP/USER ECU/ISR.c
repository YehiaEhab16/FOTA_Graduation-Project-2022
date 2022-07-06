/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)  ***********************/
/***********************   Layer :USER ECU Application   ***********************/
/***********************   DATE : 3/7/2022 				***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../../6-Library/STD_TYPES.h"

#include "../../1-MCAL/05-USART/USART_interface.h"
#include "../../1-MCAL/06-CAN/CAN_interface.h"

#include "ISR.h"

CAN_msg CAN_TXmsg;
CAN_msg CAN_RXmsg;
u8 Global_CAN_DIAG_FLAG = 0;
void ISR_voidCanRecieve(void)
{
	CAN_voidReceive(&CAN_RXmsg, 0);
	Global_CAN_DIAG_FLAG = 0;
	if (CAN_RXmsg.id == CAN_UPDATE_ID)
	{
		USART_voidTransmitChar(USART1, USER_UPDATE_ID);
	}
	else if (CAN_RXmsg.id == CAN_DIAG_ID_1 || CAN_RXmsg.id == CAN_DIAG_ID_2)
	{
		USART_voidTransmitChar(USART1, CAN_RXmsg.data[0]);
	}
}

void ISR_voidUsartRecieve(void)
{
	u8 Local_u8Data = USART_u8ReceiveChar(USART1);

	CAN_TXmsg.len = 1;
	CAN_TXmsg.format = CAN_ID_STD;
	CAN_TXmsg.type = CAN_RTR_DATA;

	if (Local_u8Data == USER_APPROVE_ID)
	{
		CAN_TXmsg.id = CAN_UPDATE_ID;
		CAN_TXmsg.data[0] = USER_APPROVED;
	}
	else if (Local_u8Data == USER_REQUEST_ID)
	{
		CAN_TXmsg.id = CAN_UPDATE_ID;
		CAN_TXmsg.data[0] = USER_REQUEST;
	}
	else if (Local_u8Data == USER_DIAG_ID)
	{
		CAN_TXmsg.id = CAN_DIAG_ID_1;
		CAN_TXmsg.data[0] = USER_REQUEST;
	}

	CAN_u8Transmit(&CAN_TXmsg);
}
