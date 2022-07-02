/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer : APP (Receive)         ***********************/
/***********************   DATE : 26-4-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../6-Library/STD_TYPES.h"

#include "../1-MCAL/03-NVIC/NVIC_interface.h"
#include "../1-MCAL/06-CAN/CAN_interface.h"
#include "../1-MCAL/05-USART/USART_interface.h"
#include "interface.h"


extern CAN_Init_t  CAN_InitStruct;
extern CAN_FilterInit_t  CAN_FilterUserResponse;
extern CAN_FilterInit_t  CAN_FilterAppDiagnostics;
extern CAN_FilterInit_t	 CAN_FilterAppAck;
extern CAN_FilterInit_t  CAN_FilterUserRequest;

CAN_msg CAN_RxMsg;

CAN_msg APP_TxDataMsg = {0x55, {0}, 8, CAN_ID_STD, DATA_FRAME};				/* Message to transmit the file */
CAN_msg APP_RxDiagnosticsMsg;												/* Msg to receive diagnostics */
CAN_msg APP_TxGetDiagMsg = {0x23, {0}, 1, CAN_ID_STD, DATA_FRAME};			/* Msg to ask app for diagnostics */

CAN_msg USER_TxUpdateMsg = {0x55, {0}, 8, CAN_ID_STD, DATA_FRAME};			/* Msg to notify user of new update */
CAN_msg APP_RxAckMsg;

CAN_msg USER_TxDiagResultMsg = {0x56, {0}, 8, CAN_ID_STD, DATA_FRAME};
CAN_msg USER_TxUpdateCheckMsg = {0x57, {0}, 8, CAN_ID_STD, DATA_FRAME};


extern u8 Global_u8State;
extern u8 Global_u8NewUpdate;
extern u8 Global_u8ESPRxMsg;
extern u8 UpdateRequestFlag;
extern u8 Global_UpdateFinishedFlag;

static u8 Rx_Buffer[BUFFER_SIZE];		/* Buffer to hold the received data */


void MainInit()
{
	USART_u8CallBackFunc(USART1, &UART_callback);
	CAN_voidCallBackFunc(CAN_FIFO_0, &CAN_FIFO0_callback);
	CAN_voidCallBackFunc(CAN_FIFO_1, &CAN_AppAckCallback);
}


void UART_callback(void)
{
	Global_u8ESPRxMsg = USART_u8ReceiveChar(USART1);
	Global_u8State = ESP_MSG;
}


/* Receive User msgs in FIFO_1 and app diagnostics in FIFO_0 */

void CAN_FIFO0_callback(void)
{
	CAN_voidReceive(&CAN_RxMsg,CAN_FIFO_0);
	switch(CAN_RxMsg.id)
	{
	case USER_RESPONSE_ID:
		Global_u8State = USER_RESPONSE;
		break;

	case Request_ID:
		Global_u8State = USER_REQUEST;
		break;

	case APP_DIAG_M1:
	case APP_DIAG_M2:
		Global_u8State = DIAGNOSTICS;
		break;
	}
}


void CAN_AppAckCallback (void)
{
	CAN_voidReceive(&APP_RxAckMsg,CAN_FIFO_1);
	if (APP_RxAckMsg.id == APP_ACKNOWLEDGE)
	{
		if ((APP_RxAckMsg.data[0] == 'O') && (APP_RxAckMsg.data[0] == 'K'))
		{
			USART_voidTransmitChar(USART1,RECORD_ACK);
			Global_u8State = RECEIVE_RECORD;
		}
		else
		{
			USART_voidTransmitChar(USART1,'n');
			NVIC_u8EnableInterrupt(USB_LP_CAN_IRQ);
			NVIC_u8DisableInterrupt(CAN_RX1_IRQ);
			NVIC_u8EnableInterrupt(USART1_IRQ);
		}
	}

}


void GetUpdate(void)
{
	u16 Buffer_Data_Counter=0;
	u16 index=0;
	u8 NumOfCanFrames;
	u8 ExtraBytes;
	u8 frame_counter;
	u8 data_counter;

	APP_TxDataMsg.len = 8;
	Buffer_Data_Counter = 0;
	index = 0;

	/* Receive Record */
	do
	{
		Rx_Buffer[index++] = USART_u8ReceiveChar(USART1);
	}while(Rx_Buffer[index-1] != '\n');

	NumOfCanFrames = (index)/8;
	ExtraBytes = (index)%8;


	/* Send Record */
	for(frame_counter=0; frame_counter<=NumOfCanFrames; frame_counter++)
	{
		if(frame_counter == NumOfCanFrames)
		{
			if (ExtraBytes!=0)	APP_TxDataMsg.len = ExtraBytes;
			else break;
		}

		for(data_counter=0; data_counter<APP_TxDataMsg.len; data_counter++)
		{
			APP_TxDataMsg.data[data_counter]= Rx_Buffer[Buffer_Data_Counter];
		}
		CAN_u8Transmit(&APP_TxDataMsg);
	}

	if ((Rx_Buffer[index-2] == 'F') && (Rx_Buffer[index-3] == 'F'))
	{
		Global_UpdateFinishedFlag = 1;
	}

}
