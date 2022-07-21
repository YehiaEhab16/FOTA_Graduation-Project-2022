/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer : APP (Receive)         ***********************/
/***********************   DATE : 26-4-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../6-Library/STD_TYPES.h"

#include "../1-MCAL/01-GPIO/GPIO_interface.h"
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
u8 file_size[5];
u16 FileSize;
u16 num_bytes = 0;
u8 StartUpdateFlag;

CAN_msg CAN_RxMsg;

//CAN_msg APP1_TxDataMsg = {0x34, {0}, 8, CAN_ID_STD, DATA_FRAME};				/* Message to transmit the file */
//CAN_msg APP2_TxDataMsg = {0x50, {0}, 8, CAN_ID_STD, DATA_FRAME};
CAN_msg APP_TxGetDiagMsg = {0x48, {0}, 1, CAN_ID_STD, DATA_FRAME};			/* Msg to ask app for diagnostics */

CAN_msg USER_TxUpdateMsg = {0x33, {U_Notification}, 1, CAN_ID_STD, DATA_FRAME};			/* Msg to notify user of new update */
CAN_msg USER_TxUpdateDoneMsg = {0x33, {UpdateComplete}, 1, CAN_ID_STD, DATA_FRAME};
CAN_msg APP_RxAckMsg;

CAN_msg USER_TxProgressMsg = {0x33, {50}, 1, CAN_ID_STD, DATA_FRAME};
CAN_msg USER_TxDiagResultMsg = {0x73, {0}, 1, CAN_ID_STD, DATA_FRAME};
CAN_msg USER_TxUpdateCheckMsg = {0x57, {0}, 1, CAN_ID_STD, DATA_FRAME};

CAN_msg APP_TxDataMsg = {0x34, {0}, 8, CAN_ID_STD, DATA_FRAME};

//CAN_msg APP_TxDataMsg;
u8 NotificationReceived = 0;

extern u8 Global_u8State;
//extern u8 Global_u8NewUpdate;
extern u8 Global_u8ESPRxMsg;
//extern u8 UpdateRequestFlag;
extern u8 Global_UpdateFinishedFlag;
extern u8 Global_u8App1Diag;
extern u8 Global_u8App2Diag;
u8 APP;

static u8 Rx_Buffer[BUFFER_SIZE];		/* Buffer to hold the received data */


void MainInit()
{
	USART_u8ReceiveAsy(USART1, &UART_callback);
	USART_u8CallBackFunc(USART1, &UART_callback);
	CAN_voidCallBackFunc(CAN_FIFO_0, &CAN_AppAckCallback);
	CAN_voidCallBackFunc(CAN_FIFO_1, &CAN_FIFO1_callback);
}


void UART_callback(void)
{

	Global_u8ESPRxMsg = USART_u8ReceiveChar(USART1);

	if (!NotificationReceived)
	{
		if (Global_u8ESPRxMsg == UPDATE_NOTIFICATION)
		{
			CAN_u8Transmit(&USER_TxUpdateMsg);

			NotificationReceived = 1;
		}
	}

	if (Global_u8ESPRxMsg == APP1_DOWNLOADED)
	{
		APP_TxDataMsg.id = 0x34;
		Global_u8State = START_UPDATE;
	}
	else if (Global_u8ESPRxMsg == APP2_DOWNLOADED)
	{
		APP_TxDataMsg.id = 0x50;
		Global_u8State = START_UPDATE;
	}
}


/* Receive User messages in FIFO_1 */

void CAN_FIFO1_callback(void)
{
	CAN_voidReceive(&CAN_RxMsg,CAN_FIFO_1);
	switch(CAN_RxMsg.id)
	{
	case USER_RESPONSE_ID:
		Global_u8State = USER_RESPONSE;
		NotificationReceived = 1;
		break;

	case Request_ID:
		Global_u8State = USER_REQUEST;
		break;

	case APP2_DIAG_ID:
		//		GPIO_u8SetPinValue(GPIO_PORTB, GPIO_PIN_9, GPIO_PIN_HIGH);
		Global_u8App2Diag = CAN_RxMsg.data[0];
		Global_u8State = DIAGNOSTICS;
		break;

	case APP1_DIAG_ID:
		//		GPIO_u8SetPinValue(GPIO_PORTB, GPIO_PIN_8, GPIO_PIN_HIGH);

		Global_u8App1Diag = CAN_RxMsg.data[0];
		Global_u8State = DIAGNOSTICS;
		break;
	}

}

/* app acknowledgement in FIFO_0 */

void CAN_AppAckCallback (void)
{
	CAN_voidReceive(&CAN_RxMsg,CAN_FIFO_0);
	if (CAN_RxMsg.id == APP_ACKNOWLEDGE)
	{
		if ((CAN_RxMsg.data[0] == 'O') && (CAN_RxMsg.data[1] == 'K'))
		{
			USART_voidTransmitChar(USART1,RECORD_ACK);
		}
		else if (CAN_RxMsg.data[0] == StartTransmission)
		{
			GPIO_u8SetPinValue(GPIO_PORTA, GPIO_PIN_1, GPIO_PIN_LOW);
			StartUpdateFlag = 1;
			//			USART_voidTransmitChar(USART1 ,'s');
		}
		Global_u8State = RECEIVE_RECORD;
	}

}


void GetUpdate(void)
{
	Global_u8State = IDLE;
	reps ++;

	if (num_bytes >= FileSize/10)
	{
		num_bytes = 0;
		CAN_u8Transmit(&USER_TxProgressMsg);
		GPIO_u8TogglePinValue(GPIO_PORTA, GPIO_PIN_1);

	}
	/* Receive another record if last record is sent correctly */
	if (CAN_RxMsg.data[0] != 'F')
	{
		APP_TxDataMsg.len = 8;
		Buffer_Data_Counter = 0;
		index = 0;
		reps=0;

		/* Receive Record */
		do
		{
			Rx_Buffer[index++] = USART_u8ReceiveChar(USART1);
			num_bytes++;
		}while(Rx_Buffer[index-1] != '\n');
	}

	/* Abort update if a record is corrupted in transmission for > 3 times */
	if  ((CAN_RxMsg.data[0] == 'F') && (reps >= 4))
	{
		USART_voidTransmitChar(USART1,'n');
		CAN_VoidDisableFifo0Int();
		CAN_VoidEnableFifo1Int();
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

		STK_voidDelay(1);
		CAN_u8Transmit(&APP_TxDataMsg);
	}

}
