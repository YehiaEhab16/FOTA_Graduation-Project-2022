/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :USER ECU Application   ***********************/
/***********************   DATE : 3/7/2022 				 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../../6-Library/STD_TYPES.h"
#include "../../3-SERVICE/02-SYS/SYS_interface.h"
#include "../../1-MCAL/07-STK/STK_interface.h"
#include "../../1-MCAL/05-USART/USART_interface.h"
#include "../../1-MCAL/01-GPIO/GPIO_interface.h"
#include "../../1-MCAL/06-CAN/CAN_interface.h"



#include "ISR.h"

extern CAN_msg CAN_TXmsg ;
extern u8 DATA_SHARED[5] ;


int main(void)
{

	SYS_voidUserInit(&ISR_voidCanRecieve);
	u8 Local_u8Data =0  ;
	u8 Local_u8Flag = 0;


	while (1)
	{
		Local_u8Data = USART_u8ReceiveChar(USART1);
		if (Local_u8Data == DATA_SHARED[USER_APPROVE])
		{

			CAN_TXmsg.id = CAN_UPDATE_ID;
			CAN_TXmsg.data[0] = USER_APPROVED;
			CAN_u8Transmit(&CAN_TXmsg);
			Local_u8Flag =1;


		}
		else if (Local_u8Data == DATA_SHARED[USER_REJECT])
		{
			CAN_TXmsg.id = CAN_UPDATE_ID;
			CAN_TXmsg.data[0] = USER_REQUEST;
			CAN_u8Transmit(&CAN_TXmsg);
			Local_u8Flag =1;


		}
		else if (Local_u8Data == DATA_SHARED[USER_DIAG])
		{
			CAN_TXmsg.id = CAN_DIAG_ID_1;
			CAN_TXmsg.data[0] = USER_REQUEST;
			CAN_u8Transmit(&CAN_TXmsg);
			Local_u8Flag =1;


		}
		else
		{
			if (Local_u8Flag ==0)
			{
				USART_voidTransmitChar(USART1, 'O');
			}
		}


	}

}
