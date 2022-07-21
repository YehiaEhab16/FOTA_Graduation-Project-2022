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

//extern CAN_msg APP1_TxDataMsg;				/* Message to transmit the file */
extern CAN_msg APP_TxDataMsg;				/* Message to transmit the file */
extern CAN_msg APP_TxGetDiagMsg;			/* Msg to ask app for diagnostics */

extern CAN_msg USER_TxUpdateMsg;			/* Msg to notify user of new update */
extern CAN_msg USER_TxUpdateDoneMsg;
//extern CAN_msg APP_RxAckMsg;

extern CAN_msg USER_TxDiagResultMsg;
//extern CAN_msg USER_TxUpdateCheckMsg;

extern u8 NotificationReceived;
extern u8 file_size[5];
extern u16 FileSize;
extern u16 num_bytes;
extern u8 StartUpdateFlag;

u8 Global_u8State;
u8 Global_u8NewUpdate;
u8 Global_u8ESPRxMsg;
u8 UpdateRequestFlag;
u8 Global_DiagReqFlag;
u8 Global_UpdateFinishedFlag;
u8 Global_u8App1Diag;
u8 Global_u8App2Diag;
u8 Mode1,Mode2;
u16 multiplier;
u8 a;

void main(void)
{
	/* function init */
	SYS_voidMainInit();
	MainInit();

	/* Initial values */
	Global_u8State = IDLE;
	multiplier = 1;
	Global_u8App1Diag = 0;
	Global_u8App2Diag = 0;
	Global_u8NewUpdate = 0;
	Global_UpdateFinishedFlag = 0;
	NotificationReceived = 0;

//	Global_u8App2Diag = 4;

	while(1)
	{
		switch(Global_u8State)
		{
		case IDLE:
			break;

		case USER_RESPONSE:
			if (NotificationReceived == 1)
			{
				Global_u8State = IDLE;
				if (CAN_RxMsg.data[0] == ACCEPT_UPDATE)
				{
					//					Global_u8State = START_UPDATE;
					USART_voidTransmitChar(USART1 ,DOWNLOAD_FILE);
					GPIO_u8SetPinValue(GPIO_PORTA, GPIO_PIN_0, GPIO_PIN_HIGH);
				}
				NotificationReceived = 0;
			}
			break;

		case START_UPDATE:
			Global_u8State = IDLE;
			CAN_VoidDisableFifo1Int();
			NVIC_u8DisableInterrupt(USART1_IRQ);
			CAN_VoidEnableFifo0Int();
			USART_ReceiveStr(USART1, file_size);
			a = USART_u8ReceiveChar(USART1);
			for (int i = 0; i<5; i++)
			{
				FileSize += (file_size[4-i]-0x30)*multiplier;
				multiplier *= 10;
			}
			CAN_u8Transmit(&APP_TxDataMsg);			/* To indicate start of transmission to app */
			GPIO_u8TogglePinValue(GPIO_PORTB, GPIO_PIN_8);
			break;

		case RECEIVE_RECORD:
			if (Global_UpdateFinishedFlag == 1)
			{
				Global_u8State = IDLE;
				Global_UpdateFinishedFlag = 0;
				FileSize = 0;
				multiplier = 1;
				num_bytes = 0;
				USART_voidTransmitChar(USART1,'n');
				CAN_u8Transmit(&USER_TxUpdateDoneMsg);
				CAN_VoidDisableFifo0Int();
				CAN_VoidEnableFifo1Int();
				NVIC_u8EnableInterrupt(USART1_IRQ);
				GPIO_u8SetPinValue(GPIO_PORTB, GPIO_PIN_8, GPIO_PIN_HIGH);

				//	GPIO_u8SetPinValue(GPIO_PORTA, GPIO_PIN_1, GPIO_PIN_HIGH);
				break;
			}
			if (StartUpdateFlag == 1)
			{
				StartUpdateFlag = 0;
				USART_voidTransmitChar(USART1 ,'s');
			}
			GetUpdate();
			break;

		case USER_REQUEST:
			Global_u8State = IDLE;
			if (CAN_RxMsg.data[0] == UPDATE_REQUEST)
			{
				USART_voidTransmitChar(USART1 ,DOWNLOAD_FILE);
			}
			else if (CAN_RxMsg.data[0] == DIAGNOSTICS_REQUEST)
			{
				CAN_u8Transmit(&APP_TxGetDiagMsg);
				Global_DiagReqFlag = 1;
				GPIO_u8SetPinValue(GPIO_PORTB, GPIO_PIN_9, GPIO_PIN_HIGH);
				/********************** Temporary ***********************/
				//				Global_u8App1Diag = 0;
				/********************************************************/
			}
			break;


		case DIAGNOSTICS:
			//			Global_u8State = IDLE;
			USER_TxDiagResultMsg.data[0] = 0;

			if ((Global_u8App2Diag <= 3) && (Global_u8App1Diag != 2))
				Mode1 = 1;
			else if (((Global_u8App2Diag > 3) && (Global_u8App2Diag <= 6)) || (Global_u8App1Diag == 2))
				Mode2 = 1;

			/* in case of mode 1 (user requested diagnostics) */
			if (Global_DiagReqFlag && Mode1)
			{
				if (Global_u8App1Diag)
				{
					SET_BIT(USER_TxDiagResultMsg.data[0], 0);
				}
				if(Global_u8App2Diag)
				{
					switch(Global_u8App2Diag)
					{
					case DIST_DIR_M1: SET_BIT(USER_TxDiagResultMsg.data[0], 1);
									  SET_BIT(USER_TxDiagResultMsg.data[0], 2);
									  break;
					case DIST_M1: SET_BIT(USER_TxDiagResultMsg.data[0], 2); break;
					case DIR_M1 : SET_BIT(USER_TxDiagResultMsg.data[0], 1); break;
					}
					//SET_BIT(USER_TxDiagResultMsg.data[0], (Global_u8App1Diag-1));
				}
			}
			/* in case of mode 2 */
			else if (Mode2)
			{
				switch(Global_u8App2Diag)
				{
				case DIST_DIR_M2: SET_BIT(USER_TxDiagResultMsg.data[0], 1);
								  SET_BIT(USER_TxDiagResultMsg.data[0], 2);
								  break;
				case DIST_M2: SET_BIT(USER_TxDiagResultMsg.data[0], 2); break;
				case DIR_M2 : SET_BIT(USER_TxDiagResultMsg.data[0], 1); break;
				}
//				SET_BIT(USER_TxDiagResultMsg.data[0], (Global_u8App2Diag-3));
				Mode2 = 0;
			}

			if ((USER_TxDiagResultMsg.data[0] != 0) || (Mode1))
			{
				CAN_u8Transmit(&USER_TxDiagResultMsg);
				if (!Mode1)
				{
					USART_voidTransmitChar(USART1 ,'X');
					USART_voidTransmitChar(USART1 ,(USER_TxDiagResultMsg.data[0] + 0x30));
				}
				Mode1 = 0;
			}

			Global_u8State = IDLE;
			GPIO_u8SetPinValue(GPIO_PORTB, GPIO_PIN_8, GPIO_PIN_LOW);
			break;
		}
	}
}
