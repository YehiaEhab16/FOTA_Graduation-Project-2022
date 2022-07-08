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
#include "../../1-MCAL/01-GPIO/GPIO_interface.h"
#include "../../1-MCAL/07-STK/STK_interface.h"


#include "ISR.h"

/**
 *	USER_APPROVE  ,
	USER_REJECT,
		,
	MAIN_Notification
 *
 *
 */

u8 DATA_SHARED[5] = {'A','B','D','E','M'};

CAN_msg CAN_TXmsg = {0x32,{0},1,CAN_ID_STD, DATA_FRAME};;
CAN_msg CAN_RXmsg;
u8 Global_CAN_DIAG_FLAG = 0;
void ISR_voidCanRecieve(void)
{

	CAN_voidReceive(&CAN_RXmsg, 0);
	Global_CAN_DIAG_FLAG = 0;
	if (CAN_RXmsg.id == CAN_UPDATE_ID)
	{

 		USART_voidTransmitChar(USART1, DATA_SHARED[USER_UPDATE_REQUEST]);

	}
	else if (CAN_RXmsg.id == CAN_DIAG_ID_1 || CAN_RXmsg.id == CAN_DIAG_ID_2)
	{
		USART_voidTransmitChar(USART1, '0'+CAN_RXmsg.data[0]);
	}
}

