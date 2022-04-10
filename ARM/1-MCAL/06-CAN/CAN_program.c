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
#include "CAN_config.h"
#include "CAN_interface.h"
#include "CAN_register.h"

CAN_msg CAN_TXmsg;
CAN_msg CAN_RXmsg;

u8 CAN_msgReceived = 0;

//Initializing CAN
void CAN_voidInit(CAN_HandleTypeDef* hcan)
{
	/* Exit from sleep mode */
	CAN1->MCR &= ~CAN_MCR_SLEEP;
	/* Request initialization */
	CAN1->MCR |= CAN_MCR_INRQ;
	/* wait for initialization mode*/
	while(((CAN1->MSR & CAN_MCR_SLEEP) == CAN_MCR_SLEEP)
			|| ((CAN1->MSR & CAN_MSR_INAK) != CAN_MSR_INAK));
	/* Enable interrupt for receiving in fifo 0*/
	CAN1->IER |= CAN_IER_FMPIE0 ;

	/* Check acknowledge */
	if ((CAN1->MSR & CAN_MSR_INAK) == CAN_MSR_INAK)
	{
		/* Set the time triggered communication mode */
		if (hcan->Init.CAN_TTCM == ENABLE)
		{
			CAN1->MCR |= CAN_MCR_TTCM;
		}
		else
		{
			CAN1->MCR &= ~(u32)CAN_MCR_TTCM;
		}

		/* Set the automatic bus-off management */
		if (hcan->Init.CAN_ABOM == ENABLE)
		{
			CAN1->MCR |= CAN_MCR_ABOM;
		}
		else
		{
			CAN1->MCR &= ~(u32)CAN_MCR_ABOM;
		}

		/* Set the automatic wake-up mode */
		if (hcan->Init.CAN_AWUM == ENABLE)
		{
			CAN1->MCR |= CAN_MCR_AWUM;
		}
		else
		{
			CAN1->MCR &= ~(u32)CAN_MCR_AWUM;
		}

		/* Set the no automatic retransmission */
		if (hcan->Init.CAN_NART == ENABLE)
		{
			CAN1->MCR |= CAN_MCR_NART;
		}
		else
		{
			CAN1->MCR &= ~(u32)CAN_MCR_NART;
		}

		/* Set the receive FIFO locked mode */
		if (hcan->Init.CAN_RFLM == ENABLE)
		{
			CAN1->MCR |= CAN_MCR_RFLM;
		}
		else
		{
			CAN1->MCR &= ~(u32)CAN_MCR_RFLM;
		}

		/* Set the transmit FIFO priority */
		if (hcan->Init.CAN_TXFP == ENABLE)
		{
			CAN1->MCR |= CAN_MCR_TXFP;
		}
		else
		{
			CAN1->MCR &= ~(u32)CAN_MCR_TXFP;
		}

		CAN1->BTR =(u32)     ((u32)hcan->Init.CAN_MODE << 30   )
									 |     ((u32)hcan->Init.CAN_SJW  << 24   )
									 |     ((u32)hcan->Init.CAN_BS1  << 16   )
									 |     ((u32)hcan->Init.CAN_BS2  << 20   )
									 |     ((u32)hcan->Init.CAN_Prescaler-1  ) ;

		/* exit initialization mode */
		CAN1->MCR &= ~CAN_MCR_INRQ;
	}
}

//Transmition Function
u8 CAN_u8Transmit(CAN_HandleTypeDef* hcan)
{
	u8 Local_u8TransmitMailBox = 0;       //Empty
	u8 Local_u8DataCounter ;              //Counter to set data into Transit Data register byte by byte

	if ((hcan->Instance->TSR & CAN_TSR_TME0) == CAN_TSR_TME0)      //check if mailox 0 is empty
		Local_u8TransmitMailBox = 0;

	else if ((hcan->Instance->TSR & CAN_TSR_TME1) == CAN_TSR_TME1) //check if mailox 1 is empty
		Local_u8TransmitMailBox = 1;
	
	else if ((hcan->Instance->TSR & CAN_TSR_TME2) == CAN_TSR_TME2) //check if mailox 2 is empty
		Local_u8TransmitMailBox = 2;
	
	else
		Local_u8TransmitMailBox = CAN_TXSTATUS_NOMAILBOX;                      // No mail box is empty

	if (Local_u8TransmitMailBox != CAN_TXSTATUS_NOMAILBOX)
	{
		hcan->Instance->sTxMailBox[Local_u8TransmitMailBox].TIR = 0;	//Reset Identifier Register
	
		//Set RTR and IDE of input frame
		hcan->Instance->sTxMailBox[Local_u8TransmitMailBox].TIR |= (hcan->pTxMsg->format << 2) | (hcan->pTxMsg->type << 1 ) ;
	
		//Set CAN identifier
		if (hcan->pTxMsg->format) //Extended
			hcan->Instance->sTxMailBox[Local_u8TransmitMailBox].TIR |= (hcan->pTxMsg->id << 3); //extended
	
		else //standard
			hcan->Instance->sTxMailBox[Local_u8TransmitMailBox].TIR |= (hcan->pTxMsg->id << 21); //standard
	
		hcan->Instance->sTxMailBox[Local_u8TransmitMailBox].TDTR = (hcan->Instance->sTxMailBox[Local_u8TransmitMailBox].TDTR & (~0x0f))		//Set data length
															| hcan->pTxMsg->len ;
		//Reset transmit data registers
		hcan->Instance->sTxMailBox[Local_u8TransmitMailBox].TDLR = 0;
		hcan->Instance->sTxMailBox[Local_u8TransmitMailBox].TDHR = 0;

		for(Local_u8DataCounter = 0; Local_u8DataCounter < hcan->pTxMsg->len; Local_u8DataCounter++)
			if (Local_u8DataCounter < 4)	//Set LSB (16 bits) of the Data
				hcan->Instance->sTxMailBox[Local_u8TransmitMailBox].TDLR |= (hcan->pTxMsg->data[Local_u8DataCounter] << (8 * Local_u8DataCounter)); 
				//Masking word byte by byte to low register
			else                                //(Local_u8DataCounter >= 4) - //set MSB (16 bits) of the Data
			hcan->Instance->sTxMailBox[Local_u8TransmitMailBox].TDHR |= (hcan->pTxMsg->data[Local_u8DataCounter] << (8 * (Local_u8DataCounter - 4)));
			//Masking word byte by byte to high register}	

	}
		hcan->Instance->sTxMailBox[Local_u8TransmitMailBox].TIR |= CAN_TI0R_TXRQ;  //Transmit Mailbox Request
		return Local_u8TransmitMailBox;           // result state

}

//Receiving Function
void CAN_voidReceive( CAN_msg *msg, u8 Copy_u8FIFOIndex)
{
	volatile u32* Local_u32Receive_FIFO_Reg;
	if (Copy_u8FIFOIndex==0) 
		Local_u32Receive_FIFO_Reg = &(CAN1->RF0R);
	else 
		Local_u32Receive_FIFO_Reg = &(CAN1->RF1R);

	//Check that there is a message pending 
	if ((*Local_u32Receive_FIFO_Reg & 0x0003) != 0)		//check FMP bits
		CAN_voidRead(CAN1, msg, Copy_u8FIFOIndex);
		
	*Local_u32Receive_FIFO_Reg |= RELEASE_FIFO;
}

//Setting CAN Filter
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
	Local_u8FilterBankExidId   = (u8)   ((RI1R_EXID& CAN_FilterInitStruct->CAN_FilterId) << 3 ) ;
	Local_u8FilterBankRtrId    = (u8)   ((RI1R_RTR & CAN_FilterInitStruct->CAN_FilterId) << 1   ) ;
	Local_u8FilterBankIdeId    = (u8)   ((RI1R_IDE & CAN_FilterInitStruct->CAN_FilterId) << 2   ) ;
	Local_u16FilterBankStdId   = (u16)  ((RI1R_STID& CAN_FilterInitStruct->CAN_FilterId) << 21  );

	/*Get STID[10:3] STID[2:0] RTR IDE EXID[17:15] of  filter mask id */
	Local_u8FilterBankExidMaskId = (u8) ((RI1R_EXID& CAN_FilterInitStruct->CAN_FilterMaskId) << 3  ) ;
	Local_u8FilterBankRtrMaskId  = (u8) ((RI1R_RTR & CAN_FilterInitStruct->CAN_FilterMaskId) << 1   ) ;
	Local_u8FilterBankIdeIdMask  = (u8) ((RI1R_IDE & CAN_FilterInitStruct->CAN_FilterMaskId) << 2   ) ;
	Local_u16FilterBankStdIdMask =(u16) ((RI1R_STID& CAN_FilterInitStruct->CAN_FilterMaskId) << 21  ) ;


	Local_u32filterNumberPosition = ( (u32)(1 << CAN_FilterInitStruct->CAN_FilterBankNumber));

	/* Initialisation mode for the filter */
	CAN1->FMR |= CAN_FMR_FINIT;
	/* Filter Deactivation */
	CAN1->FA1R &= ~(u32)Local_u32filterNumberPosition;


	switch (CAN_FilterInitStruct->CAN_FilterBankScale )
	{
		case (CAN_FILTERSCALE_16BIT):
			/* 16-bit scale for the filter */
			CAN1->FS1R &= ~(u32)Local_u32filterNumberPosition;

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
					CAN1->FM1R &= ~(u32)Local_u32filterNumberPosition;
														 /*FR1 =FR2 = [Local_u16FilterbankMaskId |Local_u16FilterbankId]*/
					CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR1 =  ((0x0000FFFF &  (u32)Local_u16FilterbankMaskId) << 16 )
																							 | (0x0000FFFF &  (u32)Local_u16FilterbankId           ) ;
					CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR2 =  ((0x0000FFFF &  (u32)Local_u16FilterbankMaskId) << 16 )
																							 | (0x0000FFFF &  (u32)Local_u16FilterbankId           ) ;
				break;

				case (CAN_FILTERMODE_IDLIST):
				/* ( CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdList )*/

					/*Identifier list mode for the filter*/
					CAN1->FM1R |= (u32)Local_u32filterNumberPosition;

									   /*FR1 =FR2 = [Local_u16FilterbankId |Local_u16FilterbankId]*/
					CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR1 = ((0x0000FFFF &  (u32)Local_u16FilterbankId) << 16 )
																							| (0x0000FFFF &  (u32)Local_u16FilterbankId       ) ;
					CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR2 = ((0x0000FFFF &  (u32)Local_u16FilterbankId) << 16 )
																						| (0x0000FFFF &  (u32)Local_u16FilterbankId       ) ;
					break;
			}
		break;

		case(CAN_FILTERSCALE_32BIT):
			/* 32-bit scale for the filter */
			CAN1->FS1R |= (u32)Local_u32filterNumberPosition;

			/* Filter Mode */
			switch (CAN_FilterInitStruct->CAN_FilterMode )
			{
				case (CAN_FILTERMODE_IDMASK):
					/*Id/Mask mode for the filter*/
					CAN1->FM1R &= ~(u32)Local_u32filterNumberPosition;

					/* for scale 32bit FilterbankID = FR1 and FilterbankMASK = FR2 */
					CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR1 = (u32)CAN_FilterInitStruct->CAN_FilterId ;
					CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR2 = (u32)CAN_FilterInitStruct->CAN_FilterMaskId ;
				break;

				case (CAN_FILTERMODE_IDLIST):
				/* ( CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdList )*/

					/*Id list mode for the filter*/
					CAN1->FM1R |= (u32)Local_u32filterNumberPosition;
					/* for scale 32bit FilterbankID = FilterbankMASK = FR1 = FR2 */
					CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR1 = (u32)CAN_FilterInitStruct->CAN_FilterId ;
					CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR2 = (u32)CAN_FilterInitStruct->CAN_FilterId ;
				break;
			}
		break;
	}
		/* specify Filter FIFO  */
	switch(CAN_FilterInitStruct->CAN_FilterFIFONumber)
	{
		case (CAN_FIFO_0):
			CAN1->FFA1R &= ~(u32)Local_u32filterNumberPosition;     // FIFO 0 chosen for the filter
		break;
		case (CAN_FIFO_1):
			CAN1->FFA1R |= (u32)Local_u32filterNumberPosition;   // FIFO 1 chosen for the filter
 		break;
	}
	// Filter activation
	if (CAN_FilterInitStruct->CAN_FilterActivation == 1) CAN1->FA1R |= Local_u32filterNumberPosition;

    CAN1->FMR &= ~CAN_FMR_FINIT;     //release init mode for the input filter */
}

//Reading Function
static void CAN_voidRead(CAN_t* CAN, CAN_msg *msg, u8 Copy_u8FIFOIndex)
{
	u8 Local_u8RxDataCount;
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

	//Message type
	if ((CAN->sFIFOMailBox[Copy_u8FIFOIndex].RIR & 0x2) ==0)
		msg->type = DATA_FRAME;

	else
		msg->type = REMOTE_FRAME;

	//Length (number of received bytes)
	msg->len = (u8)0x0000000F & CAN->sFIFOMailBox[Copy_u8FIFOIndex].RDTR;

	//Reading data
	for(Local_u8RxDataCount = 0;  Local_u8RxDataCount < msg->len; Local_u8RxDataCount++)
		if (Local_u8RxDataCount < 4)  //data from the FIFO mailbox data low register
			msg->data[Local_u8RxDataCount] = (CAN->sFIFOMailBox[Copy_u8FIFOIndex].RDLR >> (Local_u8RxDataCount * 8))  & 0xFF;
			
		else if(Local_u8RxDataCount >= 4) //data from the FIFO mailbox data high register
			msg->data[Local_u8RxDataCount] = (CAN->sFIFOMailBox[Copy_u8FIFOIndex].RDHR >> ((Local_u8RxDataCount - 4) * 8)) & 0xFF;

}

void USB_LP_CAN_RX0_IRQHandler(void)
{
	if (CAN1->RF0R & CAN_RF0R_FMP0)
	{
		CAN_voidReceive(&CAN_RXmsg, 0);
		CAN_msgReceived = 1;
	}
}
