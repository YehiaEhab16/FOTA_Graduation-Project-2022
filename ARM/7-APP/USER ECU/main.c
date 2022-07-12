/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :USER ECU Application   ***********************/
/***********************   DATE : 3/7/2022 				 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../../6-Library/STD_TYPES.h"

#include "../../1-MCAL/06-CAN/CAN_interface.h"

#include "../../1-MCAL/01-GPIO/GPIO_interface.h"

#include "../../2-HAL/01-LED/LED_interface.h"
#include "../../2-HAL/08-COM/COM_interface.h"

#include "../../3-SERVICE/02-SYS/SYS_interface.h"

#include "ISR.h"

LED_t Global_LED_tIndication = {LED_PORTB, LED_PIN0, LED_ACTIVE_HIGH};

extern CAN_msg CAN_TXmsg;
extern u8 Global_u8DiagnosticsResponse, Global_u8UpdateResponse;

int main(void)
{

	SYS_voidUserInit(&ISR_voidCanRecieve);

	while (1)
	{
		if (Global_u8UpdateResponse==COM_UPDATE_APPROVED)
		{
			CAN_TXmsg.id =CAN_UPDATE_ID_TX;
			CAN_TXmsg.data[0]= ISR_UPDATE_APPROVED;
			CAN_u8Transmit(&CAN_TXmsg);
			GPIO_u8TogglePinValue(GPIO_PORTB, GPIO_PIN_1);
			Global_u8UpdateResponse=COM_IDLE;
		}
		else if (Global_u8UpdateResponse==COM_UPDATE_REJECTED)
		{
			CAN_TXmsg.id =CAN_UPDATE_ID_TX;
			CAN_TXmsg.data[0]= ISR_UPDATE_REJECTED;
			CAN_u8Transmit(&CAN_TXmsg);
			Global_u8UpdateResponse=COM_IDLE;
		}
		if (Global_u8DiagnosticsResponse==COM_DAIG_REQUESTED)
		{
			CAN_TXmsg.id =CAN_DIAG_ID_TX;
			CAN_TXmsg.data[0]= ISR_DAIG_REQUESTED;
			CAN_u8Transmit(&CAN_TXmsg);
			GPIO_u8TogglePinValue(GPIO_PORTB, GPIO_PIN_0);
			Global_u8DiagnosticsResponse=COM_DAIG_NOT_REQUESTED;
		}
	}
}
