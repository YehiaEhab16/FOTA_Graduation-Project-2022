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
#include "../1-MCAL/07-STK/STK_interface.h"
#include "interface.h"

u16 Buffer_Data_Counter;
u16 index;
u8 NumOfCanFrames;	//Total number of can frames in a single record
u8 ExtraBytes;
u8 frame_counter;	//counter for complete can frames in a single record
u8 data_counter;	//counter for data bytes in a can frame
u8 reps; 			// Number of times a corrupted frame is repeated (max 3)


CAN_msg CAN_RxMsg;

CAN_msg APP_TxDataMsg = {0x32, {0}, 8, CAN_ID_STD, DATA_FRAME};				/* Message to transmit the file */
CAN_msg APP_RxDiagnosticsMsg;												/* Msg to receive diagnostics */
CAN_msg APP_TxGetDiagMsg = {0x31, {0}, 1, CAN_ID_STD, DATA_FRAME};			/* Msg to ask app for diagnostics */

CAN_msg USER_TxUpdateMsg = {0x33, {0}, 8, CAN_ID_STD, DATA_FRAME};			/* Msg to notify user of new update */
CAN_msg APP_RxAckMsg;

CAN_msg USER_TxDiagResultMsg = {0x56, {0}, 8, CAN_ID_STD, DATA_FRAME};
CAN_msg USER_TxUpdateCheckMsg = {0x57, {0}, 8, CAN_ID_STD, DATA_FRAME};

u8 NotificationReceived = 0;

extern u8 Global_u8State;
extern u8 Global_u8NewUpdate;
extern u8 Global_u8ESPRxMsg;
extern u8 UpdateRequestFlag;
extern u8 Global_UpdateFinishedFlag;

static u8 Rx_Buffer[BUFFER_SIZE];		/* Buffer to hold the received data */


void MainInit()
{
	USART_u8ReceiveAsy(USART1, &UART_callback);
	USART_u8CallBackFunc(USART1, &UART_callback);
	CAN_voidCallBackFunc(CAN_FIFO_0, &CAN_FIFO0_callback);
	CAN_voidCallBackFunc(CAN_FIFO_1, &CAN_AppAckCallback);
}


void UART_callback(void)
{
	if (!NotificationReceived)
	{
	Global_u8ESPRxMsg = USART_u8ReceiveChar(USART1);
	}
	if (Global_u8ESPRxMsg == UPDATE_NOTIFICATION)
	{
		CAN_u8Transmit(&USER_TxUpdateMsg);
		NotificationReceived = 1;
	}
	Global_u8State = IDLE;
}


/* Receive User messages in FIFO_0 */

void CAN_FIFO0_callback(void)
{
	CAN_voidReceive(&CAN_RxMsg,CAN_FIFO_0);
	switch(CAN_RxMsg.id)
	{
	case USER_RESPONSE_ID:
		Global_u8State = USER_RESPONSE;
		NotificationReceived = 0;
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

/* app acknowledgement in FIFO_1 */

void CAN_AppAckCallback (void)
{
	CAN_voidReceive(&APP_RxAckMsg,CAN_FIFO_1);
	if (APP_RxAckMsg.id == APP_ACKNOWLEDGE)
	{
		if ((APP_RxAckMsg.data[0] == 'O') && (APP_RxAckMsg.data[1] == 'K'))
		{
			USART_voidTransmitChar(USART1,RECORD_ACK);
			Global_u8State = RECEIVE_RECORD;
		}
	}

}


void GetUpdate(void)
{
	Global_u8State = IDLE;
	reps ++;

	/* Receive another record if last record is sent correctly */
	if (APP_RxAckMsg.data[0] != 'F')
	{
		APP_TxDataMsg.len = 8;
		Buffer_Data_Counter = 0;
		index = 0;
		reps=0;

		/* Receive Record */
		do
		{
			Rx_Buffer[index++] = USART_u8ReceiveChar(USART1);
		}while(Rx_Buffer[index-1] != '\n');
	}

	/* Abort update if a record is corrupted in transmission for > 3 times */
	if  ((APP_RxAckMsg.data[0] == 'F') && (reps >= 4))
	{
		USART_voidTransmitChar(USART1,'n');
		NVIC_u8DisableInterrupt(USB_LP_CAN_IRQ);
		NVIC_u8DisableInterrupt(CAN_RX1_IRQ);
		NVIC_u8EnableInterrupt(USART1_IRQ);
		return;
	}

	if ((Rx_Buffer[7] == '0') && (Rx_Buffer[8] == '5'))
	{
		Global_UpdateFinishedFlag = 1;
	}

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
			APP_TxDataMsg.data[data_counter]= Rx_Buffer[Buffer_Data_Counter++];
		}

		//		USART_voidTransmitSync(USART2, APP_TxDataMsg.data, APP_TxDataMsg.len);
		STK_voidDelay(100);
		CAN_u8Transmit(&APP_TxDataMsg);

	}

}
