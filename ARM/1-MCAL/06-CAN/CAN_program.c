/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):CAN 			 ***********************/
/***********************   DATA : 10-04-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "CAN_private.h"
#include "CAN_register.h"
#include "CAN_config.h"
#include "CAN_interface.h"


u8 CAN_msgReceived = 0;
void (*CAN_CallBack)(void) = NULL;


void CAN_voidInit(CAN_Init_t* hcan)
{
	/* Exit from sleep mode */
	CAN->MCR &= ~CAN_MCR_SLEEP;
	/* Request initialization */
	CAN->MCR |= CAN_MCR_INRQ;
	/* wait for initialization mode*/
	while(((CAN->MSR & CAN_MCR_SLEEP) == CAN_MCR_SLEEP)
			|| ((CAN->MSR & CAN_MSR_INAK) != CAN_MSR_INAK));
	/* Enable interrupt for receiving in fifo 0*/
	CAN->IER |= CAN_IER_FMPIE0 ;

	/* Check acknowledge */
	if ((CAN->MSR & CAN_MSR_INAK) == CAN_MSR_INAK)
	{
		/* Set the time triggered communication mode */
		if (hcan->CAN_TTCM == CAN_ENABLE)
		{
			CAN->MCR |= CAN_MCR_TTCM;
		}
		else
		{
			CAN->MCR &= ~(u32)CAN_MCR_TTCM;
		}

		/* Set the automatic bus-off management */
		if (hcan->CAN_ABOM == CAN_ENABLE)
		{
			CAN->MCR |= CAN_MCR_ABOM;
		}
		else
		{
			CAN->MCR &= ~(u32)CAN_MCR_ABOM;
		}

		/* Set the automatic wake-up mode */
		if (hcan->CAN_AWUM == CAN_ENABLE)
		{
			CAN->MCR |= CAN_MCR_AWUM;
		}
		else
		{
			CAN->MCR &= ~(u32)CAN_MCR_AWUM;
		}

		/* Set the no automatic retransmission */
		if (hcan->CAN_NART == CAN_ENABLE)
		{
			CAN->MCR |= CAN_MCR_NART;
		}
		else
		{
			CAN->MCR &= ~(u32)CAN_MCR_NART;
		}

		/* Set the receive FIFO locked mode */
		if (hcan->CAN_RFLM == CAN_ENABLE)
		{
			CAN->MCR |= CAN_MCR_RFLM;
		}
		else
		{
			CAN->MCR &= ~(u32)CAN_MCR_RFLM;
		}

		/* Set the transmit FIFO priority */
		if (hcan->CAN_TXFP == CAN_ENABLE)
		{
			CAN->MCR |= CAN_MCR_TXFP;
		}
		else
		{
			CAN->MCR &= ~(u32)CAN_MCR_TXFP;
		}

		CAN->BTR =(u32)     ((u32)hcan->CAN_MODE << 30   )
						|   ((u32)hcan->CAN_SJW  << 24   )
						|   ((u32)hcan->CAN_BS1  << 16   )
						|   ((u32)hcan->CAN_BS2  << 20   )
						|   ((u32)hcan->CAN_Prescaler-1  ) ;


		/* exit initialization mode */
		CAN->MCR &= ~CAN_MCR_INRQ;

	}
}

/****************************************************************************************/
/****************************************************************************************/

void CAN_VoidFilterSet(CAN_FilterInit_t* CAN_FilterInitStruct)
{

	    u32 Local_u32filterNumberPosition ; // filter posotion number in the register

	    u8  Local_u8FilterBankExidId ;	   //contain exdended [15 :17] of filter id
	    u8  Local_u8FilterBankRtrId  ; //contain rtr offilter id
	    u8  Local_u8FilterBankIdeId  ; //contain ide of filter id
	    u16 Local_u16FilterBankStdId ;//contain std id of filter id

		u8  Local_u8FilterBankExidMaskId ;	//contain exdended [15 :17] of filter mask id
	    u8  Local_u8FilterBankRtrMaskId  ;  //contain rtr of filter  mask id
	    u8  Local_u8FilterBankIdeIdMask  ;  //contain ide of filter  mask id
	    u16 Local_u16FilterBankStdIdMask ; //contain std id of filter mask id

		u16 Local_u16FilterbankId  ;  // new id to set in 16-scale filter bank
		u16 Local_u16FilterbankMaskId  ;  // new maske id to set in 16-scale filter bank


	            /*Get STID[10:3] STID[2:0] RTR IDE EXID[17:15] of filter id */
		Local_u8FilterBankExidId   = (u8)   ((0x00038000 & CAN_FilterInitStruct->CAN_FilterId) >> 15  ) ;
		Local_u8FilterBankRtrId    = (u8)   ((0x00000002 & CAN_FilterInitStruct->CAN_FilterId) << 3   ) ;
		Local_u8FilterBankIdeId    = (u8)   ((0x00000004 & CAN_FilterInitStruct->CAN_FilterId) << 1   ) ;
		Local_u16FilterBankStdId   = (u16)  ((0xFFE00000 & CAN_FilterInitStruct->CAN_FilterId) >> 16  );

			            /*Get STID[10:3] STID[2:0] RTR IDE EXID[17:15] of  filter mask id */
		Local_u8FilterBankExidMaskId = (u8) ((0x00038000 & CAN_FilterInitStruct->CAN_FilterMaskId) >> 15  ) ;
		Local_u8FilterBankRtrMaskId  = (u8) ((0x00000002 & CAN_FilterInitStruct->CAN_FilterMaskId) << 3   ) ;
		Local_u8FilterBankIdeIdMask  = (u8) ((0x00000004 & CAN_FilterInitStruct->CAN_FilterMaskId) << 1   ) ;
		Local_u16FilterBankStdIdMask =(u16) ((0xFFE00000 & CAN_FilterInitStruct->CAN_FilterMaskId) >> 16  ) ;



		Local_u32filterNumberPosition = ( (u32)(1 << CAN_FilterInitStruct->CAN_FilterBankNumber));

	/* Initialisation mode for the filter */
	CAN->FMR |= CAN_FMR_FINIT;
	/* Filter Deactivation */
	CAN->FA1R &= ~(u32)Local_u32filterNumberPosition;


	switch (CAN_FilterInitStruct->CAN_FilterBankScale )
	{
		case (CAN_FILTERSCALE_16BIT):
			/* 16-bit scale for the filter */
			CAN->FS1R &= ~(u32)Local_u32filterNumberPosition;

				/* Filter mapping
			 *   15-8        7-5    4   3     2-0
			 * STID[10:3] STID[2:0] RTR IDE EXID[17:15]
			 * */
										   /*Get masked filter id and filter mask id*/
			Local_u16FilterbankId         = (u16) ( Local_u8FilterBankExidId       | Local_u8FilterBankRtrId
										 			 | Local_u8FilterBankIdeId        | Local_u16FilterBankStdId    );

			Local_u16FilterbankMaskId      = (u16)( Local_u8FilterBankExidMaskId   | Local_u8FilterBankRtrMaskId
													 | Local_u8FilterBankIdeIdMask    | Local_u16FilterBankStdIdMask);

			/* Filter Mode */
			switch (CAN_FilterInitStruct->CAN_FilterMode)
			{
				case(CAN_FILTERMODE_IDMASK):
				/*Id/Mask mode for the filter*/
					CAN->FM1R &= ~(u32)Local_u32filterNumberPosition;
														 /*FR1 =FR2 = [Local_u16FilterbankMaskId |Local_u16FilterbankId]*/
					CAN->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR1 = ((0x0000FFFF &  (u32)Local_u16FilterbankMaskId) << 16 )
																							 | (0x0000FFFF &  (u32)Local_u16FilterbankId           ) ;
					CAN->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR2 = ((0x0000FFFF &  (u32)Local_u16FilterbankMaskId) << 16 )
																							 | (0x0000FFFF &  (u32)Local_u16FilterbankId           ) ;
				break;

				case (CAN_FILTERMODE_IDLIST):
				/* ( CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdList )*/

					/*Identifier list mode for the filter*/
					CAN->FM1R |= (u32)Local_u32filterNumberPosition;

									   /*FR1 =FR2 = [Local_u16FilterbankId |Local_u16FilterbankId]*/
					CAN->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR1 = ((0x0000FFFF &  (u32)Local_u16FilterbankId) << 16 )
																							| (0x0000FFFF &  (u32)Local_u16FilterbankId       ) ;
					CAN->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR2 =	((0x0000FFFF &  (u32)Local_u16FilterbankId) << 16 )
																							| (0x0000FFFF &  (u32)Local_u16FilterbankId       ) ;
					break;
			}
		break;

		case(CAN_FILTERSCALE_32BIT):
			/* 32-bit scale for the filter */
			CAN->FS1R |= (u32)Local_u32filterNumberPosition;

			/* Filter Mode */
			switch (CAN_FilterInitStruct->CAN_FilterMode )
			{
				case (CAN_FILTERMODE_IDMASK):
					/*Id/Mask mode for the filter*/
					CAN->FM1R &= ~(u32)Local_u32filterNumberPosition;

					/* for scale 32bit FilterbankID = FR1 and FilterbankMASK = FR2 */
					CAN->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR1 = (u32)CAN_FilterInitStruct->CAN_FilterId ;
					CAN->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR2 = (u32)CAN_FilterInitStruct->CAN_FilterMaskId ;
				break;

				case (CAN_FILTERMODE_IDLIST):
				/* ( CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdList )*/

					/*Id list mode for the filter*/
					CAN->FM1R |= (u32)Local_u32filterNumberPosition;
					/* for scale 32bit FilterbankID = FilterbankMASK = FR1 = FR2 */
					CAN->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR1 = (u32)CAN_FilterInitStruct->CAN_FilterId ;
					CAN->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR2 = (u32)CAN_FilterInitStruct->CAN_FilterId ;
				break;
			}
		break;
	}
		/* specify Filter FIFO  */
	switch(CAN_FilterInitStruct->CAN_FilterFIFONumber)
	{
		case (CAN_FIFO_0):
			CAN->FFA1R &= ~(u32)Local_u32filterNumberPosition;     // FIFO 0 chosen for the filter
		break;
		case (CAN_FIFO_1):
			CAN->FFA1R |= (u32)Local_u32filterNumberPosition;   // FIFO 1 chosen for the filter
 		break;
	}
	// Filter activation
	if (CAN_FilterInitStruct->CAN_FilterActivation == 1)
		CAN->FA1R |= Local_u32filterNumberPosition;

    CAN->FMR &= ~CAN_FMR_FINIT;     //release init mode for the input filter */
}


/****************************************************************************************/
/****************************************************************************************/



u8 CAN_u8Transmit( CAN_msg* pTxMsg)
{

	u8 transmitmailbox = 0;       //empty
	u8 DataCounter ;              //counter to set data into Transit Data register byte by byte

	if ((CAN->TSR & CAN_TSR_TME0) == CAN_TSR_TME0)      //check if mailox 0 is empty
	{
		transmitmailbox = 0;
	}
	else if ((CAN->TSR & CAN_TSR_TME1) == CAN_TSR_TME1) //check if mailox 1 is empty
	{
		transmitmailbox = 1;
	}
	else if ((CAN->TSR & CAN_TSR_TME2) == CAN_TSR_TME2) //check if mailox 2 is empty
	{
		transmitmailbox = 2;
	}
	else
	{
		transmitmailbox = CAN_TXSTATUS_NOMAILBOX;                   // No mail box is empty

	}

	if (transmitmailbox != CAN_TXSTATUS_NOMAILBOX)
	{
		CAN->sTxMailBox[transmitmailbox].TIR = 0;                                               //Reset Identifier Register

		CAN->sTxMailBox[transmitmailbox].TIR |= (pTxMsg->format << 2) | (pTxMsg->type << 1 ) ;//set RTR and IDE of input frame

		//set CAN identifier
		if (pTxMsg->format) //extended
		{
			CAN->sTxMailBox[transmitmailbox].TIR |= (pTxMsg->id << 3); //extended
		}

		else //standard
		{
			CAN->sTxMailBox[transmitmailbox].TIR |= (pTxMsg->id << 21); //standard
		}

		CAN->sTxMailBox[transmitmailbox].TDTR = (CAN->sTxMailBox[transmitmailbox].TDTR & (~0x0f))		//set data length
				                                            												   | pTxMsg->len ;

		//reset transmit data registers
		CAN->sTxMailBox[transmitmailbox].TDLR = 0;
		CAN->sTxMailBox[transmitmailbox].TDHR = 0;

		for ( DataCounter = 0; DataCounter < pTxMsg->len; DataCounter++)
		{

			if (DataCounter < 4)                //set LSB (16 bits) of the Data
			{

				CAN->sTxMailBox[transmitmailbox].TDLR |= (pTxMsg->data[DataCounter] << (8 * DataCounter)); // masking word byte by byte to low register

			}
			else                                //(DataCounter >= 4) - //set MSB (16 bits) of the Data
			{

				CAN->sTxMailBox[transmitmailbox].TDHR |= (pTxMsg->data[DataCounter] << (8 * (DataCounter - 4)));// masking word byte by byte to high register

			}

		}

	}
	CAN->sTxMailBox[transmitmailbox].TIR |= CAN_TI0R_TXRQ;  //Transmit Mailbox Request

	return transmitmailbox;           // result state

}


/****************************************************************************************/
/****************************************************************************************/


void CAN_voidReceive( CAN_msg *msg, u8 Copy_u8FIFOIndex)
{
	u8 Local_u8RxDataCount;
	volatile u32* Receive_FIFO_Reg ;

	if (Copy_u8FIFOIndex==0) {Receive_FIFO_Reg = &(CAN->RF0R);}
	else {Receive_FIFO_Reg = &(CAN->RF1R);}

	/* Check that there is a message pending */
	if ((*Receive_FIFO_Reg & CAN_FIFO_FMP) != 0)		//check FMP bits
	{
		/* Start reading received message */
		if ((CAN->sFIFOMailBox[Copy_u8FIFOIndex].RIR & 0x4)==0)
		{
			msg->format = CAN_ID_STD;
			msg->id     = ((u32)0x000007FF) & (CAN->sFIFOMailBox[Copy_u8FIFOIndex].RIR >> 21);
		}
		else
		{
			msg->format = CAN_ID_EXT;
			msg->id     = ((u32)0x1FFFFFFF) & ((CAN->sFIFOMailBox[Copy_u8FIFOIndex].RIR >> 3));
		}

		// message type
		if ((CAN->sFIFOMailBox[Copy_u8FIFOIndex].RIR & RIR_RTR) ==0)
		{ msg->type = DATA_FRAME;}

		else { msg->type = REMOTE_FRAME;}

		//length (number of received bytes)
		msg->len = (u8)(0x0000000F & CAN->sFIFOMailBox[Copy_u8FIFOIndex].RDTR);

		// Reading data
		for ( Local_u8RxDataCount = 0;  Local_u8RxDataCount < msg->len; Local_u8RxDataCount++)
		{
			if (Local_u8RxDataCount < 4)  //data from the FIFO mailbox data low register
			{
				msg->data[Local_u8RxDataCount] = (CAN->sFIFOMailBox[Copy_u8FIFOIndex].RDLR >> (Local_u8RxDataCount * 8))  & 0xFF;
			}
			else if(Local_u8RxDataCount >= 4) //data from the FIFO mailbox data high register
			{
				msg->data[Local_u8RxDataCount] = (CAN->sFIFOMailBox[Copy_u8FIFOIndex].RDHR >> ((Local_u8RxDataCount - 4) * 8)) & 0xFF;
			}

		}
	}

	*Receive_FIFO_Reg |= RELEASE_FIFO;
}


/****************************************************************************************/
void CAN_voidCallBackFunc(void(*pv_CallBack)(void))
{
	if (pv_CallBack != NULL)
	{
		CAN_CallBack = pv_CallBack;
	}
}

void USB_LP_CAN_RX0_IRQHandler(void)
{
	if (CAN->RF0R & CAN_FIFO_FMP)
	{
		CAN_CallBack();
	}

}

