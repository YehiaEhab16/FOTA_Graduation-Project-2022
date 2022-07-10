/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer : APP (Receive)         ***********************/
/***********************   DATE : 26-4-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../6-Library/STD_TYPES.h"
#include "../6-Library/BIT_MATH.h"
#include "../3-SERVICE/02-SYS/SYS_interface.h"
#include "../1-MCAL/01-GPIO/GPIO_interface.h"

#include "../1-MCAL/03-NVIC/NVIC_interface.h"
#include "../1-MCAL/06-CAN/CAN_interface.h"
#include "../1-MCAL/05-USART/USART_interface.h"
#include "interface.h"

extern CAN_msg CAN_RxMsg;

extern CAN_msg APP_TxDataMsg;				/* Message to transmit the file */
extern CAN_msg APP_RxDiagnosticsMsg;		/* Msg to receive diagnostics */
extern CAN_msg APP_TxGetDiagMsg;			/* Msg to ask app for diagnostics */

extern CAN_msg USER_TxUpdateMsg;			/* Msg to notify user of new update */
extern CAN_msg APP_RxAckMsg;

extern CAN_msg USER_TxDiagResultMsg;
extern CAN_msg USER_TxUpdateCheckMsg;

extern u8 NotificationReceived;

u8 Global_u8State;
u8 Global_u8NewUpdate;
u8 Global_u8ESPRxMsg;
u8 UpdateRequestFlag;
u8 Global_UpdateFinishedFlag;


void main(void)
{
	/* function init */
	SYS_voidMainInit();
	MainInit();

	/* Initial values */
	Global_u8State = IDLE;

	Global_u8NewUpdate = 0;
	Global_UpdateFinishedFlag = 0;

	while(1)
	{
		switch(Global_u8State)
		{
		case IDLE:
			break;

		case USER_RESPONSE:
			if (NotificationReceived == 1)
			{
				if (CAN_RxMsg.data[0] == ACCEPT_UPDATE)
				{
					Global_u8State = START_UPDATE;
					GPIO_u8SetPinValue(GPIO_PORTA, GPIO_PIN_0, GPIO_PIN_HIGH);
				}
				else if (CAN_RxMsg.data[0] == DECLINE_UPDATE)
				{
					Global_u8State = IDLE;
				}
				Global_u8NewUpdate--;
				NotificationReceived = 0;
			}
			break;

		case START_UPDATE:
			NVIC_u8DisableInterrupt(CAN_RX1_IRQ);
			NVIC_u8DisableInterrupt(USART1_IRQ);
			NVIC_u8EnableInterrupt(USB_LP_CAN_IRQ);
			CAN_u8Transmit(&APP_TxDataMsg);			/* to indicate start of transmission to app */
			Global_u8State = IDLE;
			break;

		case RECEIVE_RECORD:

			if (Global_UpdateFinishedFlag == 1)
			{
				Global_u8State = IDLE;
				Global_UpdateFinishedFlag = 0;
				//				USART_voidTransmitChar(USART1,'n');
				//				NVIC_u8EnableInterrupt(USB_LP_CAN_IRQ);
				NVIC_u8EnableInterrupt(CAN_RX1_IRQ);
				NVIC_u8EnableInterrupt(USART1_IRQ);

				GPIO_u8SetPinValue(GPIO_PORTA, GPIO_PIN_1, GPIO_PIN_HIGH);
				break;
			}
			GetUpdate();
			break;

		case USER_REQUEST:
			if (CAN_RxMsg.data[0] == UPDATE_REQUEST)
			{
				Global_u8State = START_UPDATE;
				break;
			}
			else if (CAN_RxMsg.data[0] == DIAGNOSTICS_REQUEST)
			{
				CAN_u8Transmit(&APP_TxGetDiagMsg);
			}
			Global_u8State = IDLE;
			break;


		case DIAGNOSTICS:
			if ((USER_TxDiagResultMsg.id == APP_DIAG_M1) && (USER_TxDiagResultMsg.data[0] != 0))
			{
				USART_voidTransmitChar(USART1 ,CAN_RxMsg.data[0]);
			}
			USER_TxDiagResultMsg.data[0] = CAN_RxMsg.data[0];
			CAN_u8Transmit(&USER_TxDiagResultMsg);
			Global_u8State = IDLE;
			break;
		}
	}
}
