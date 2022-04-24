
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "CAN_interface.h"
#include "CAN_private.h"
#include "CAN_config.h"

CAN_msg CAN_TXmsg;
CAN_msg CAN_RXmsg;

u8 CAN_msgReceived = 0;


void CAN_VoidInit(CAN_HandleTypeDef* hcan)
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


//		  CAN1->FMR |= CAN_FMR_FINIT;
//
//		  /* Set filer mode, 1 and 3 list, 2 and 4 mask */
//		  CAN1->FM1R &= ~(4 | 16);
//		  CAN1->FM1R |= (2 | 8);
//
//		  /* Set FIFO 0 for all filters */
//		  CAN1->FFA1R &= ~(2 | 4
//		      | 8 | 16);
//
//		  /* Filter mapping
//		   *   15-8          7-5    4   3    2-0
//		   * STID[10:3] STID[2:0] RTR IDE EXID[17:15]
//		   * */
//
//		  /* Filter 0 Deactivated ID Mask (16-bit) No. 0, 1 */
//
////		  /* Set filter 1, list mode with ID = 0x25 */
////		  CAN1->sFilterRegister[1].FR1 = 0x04A004A0; /* No. 2, 3 */
////		  CAN1->sFilterRegister[1].FR2 = 0x04A004A0; /* No. 4, 5 */
////
////		  /* Set filter 2, mask mode with ID = 0x10:0x1F */
////		  CAN1->sFilterRegister[2].FR1 = 0xFE1F0200; /* No. 6 */
////		  CAN1->sFilterRegister[2].FR2 = 0xFE1F0200; /* No. 7 */
//
//		  /* Set filter 3, list mode with ID = 0x15 */
//		  CAN1->sFilterRegister[3].FR1 = 0x02A002A0; /* No. 8, 9 */
//		  CAN1->sFilterRegister[3].FR2 = 0x02A002A0; /* No. 10, 11 */
//
////		  /* Set filter 4, mask mode with ID = 0x20:0x2F */
////		  CAN1->sFilterRegister[4].FR1 = 0xFE1F0400; /* No. 12 */
////		  CAN1->sFilterRegister[4].FR2 = 0xFE1F0400; /* No. 13 */
//
//		  /* Activate filters */
//		  CAN1->FA1R |= (2 | 4
//		      | 8 | 16);
//
//		  /* Active filters mode */
//		  CAN1->FMR &= ~CAN_FMR_FINIT;


		/* exit initialization mode */
		CAN1->MCR &= ~CAN_MCR_INRQ;

	}
}

/****************************************************************************************/
/****************************************************************************************/

void CAN_VoidFilterSet(CAN_FilterInit_t* CAN_FilterInitStruct)
{

//	CAN_t *CAN = CAN_Get(Copy_u8CAN);

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
					CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR1 = 0x02A002A0;
//							((0x0000FFFF &  (u32)Local_u16FilterbankMaskId) << 16 )
//																							 | (0x0000FFFF &  (u32)Local_u16FilterbankId           ) ;
					CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR2 = 0x02A002A0;
//							((0x0000FFFF &  (u32)Local_u16FilterbankMaskId) << 16 )
//																							 | (0x0000FFFF &  (u32)Local_u16FilterbankId           ) ;
				break;

				case (CAN_FILTERMODE_IDLIST):
				/* ( CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdList )*/

					/*Identifier list mode for the filter*/
					CAN1->FM1R |= (u32)Local_u32filterNumberPosition;

									   /*FR1 =FR2 = [Local_u16FilterbankId |Local_u16FilterbankId]*/
					CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR1 = 0x02A002A0;
							//((0x0000FFFF &  (u32)Local_u16FilterbankId) << 16 )
							//																| (0x0000FFFF &  (u32)Local_u16FilterbankId       ) ;
					CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR2 =0x02A002A0;
//							((0x0000FFFF &  (u32)Local_u16FilterbankId) << 16 )
//																						| (0x0000FFFF &  (u32)Local_u16FilterbankId       ) ;
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
	if (CAN_FilterInitStruct->CAN_FilterActivation == 1)
		CAN1->FA1R |= Local_u32filterNumberPosition;

    CAN1->FMR &= ~CAN_FMR_FINIT;     //release init mode for the input filter */
}



/****************************************************************************************/
/****************************************************************************************/



u8 CAN_u8Transmit(CAN_HandleTypeDef* hcan)
{


  u8 transmitmailbox = 0;       //empty
  u8 DataCounter ;              //counter to set data into Transit Data register byte by byte

  if ((hcan->Instance->TSR & CAN_TSR_TME0) == CAN_TSR_TME0)      //check if mailox 0 is empty
  {
    transmitmailbox = 0;
  }
  else if ((hcan->Instance->TSR & CAN_TSR_TME1) == CAN_TSR_TME1) //check if mailox 1 is empty
  {
    transmitmailbox = 1;
  }
  else if ((hcan->Instance->TSR & CAN_TSR_TME2) == CAN_TSR_TME2) //check if mailox 2 is empty
  {
    transmitmailbox = 2;
  }
  else
  {
    transmitmailbox = CAN_TXSTATUS_NOMAILBOX;                   // No mail box is empty

  }

 if (transmitmailbox != CAN_TXSTATUS_NOMAILBOX)
 {
	hcan->Instance->sTxMailBox[transmitmailbox].TIR = 0;                                               //Reset Identifier Register

	hcan->Instance->sTxMailBox[transmitmailbox].TIR |= (hcan->pTxMsg->format << 2) | (hcan->pTxMsg->type << 1 ) ;//set RTR and IDE of input frame

		//set CAN identifier
		if (hcan->pTxMsg->format) //extended
		{
			hcan->Instance->sTxMailBox[transmitmailbox].TIR |= (hcan->pTxMsg->id << 3); //extended
		}

		else //standard
		{
			hcan->Instance->sTxMailBox[transmitmailbox].TIR |= (hcan->pTxMsg->id << 21); //standard
		}

		hcan->Instance->sTxMailBox[transmitmailbox].TDTR = (hcan->Instance->sTxMailBox[transmitmailbox].TDTR & (~0x0f))		//set data length
				                                               | hcan->pTxMsg->len ;

		//reset transmit data registers
		hcan->Instance->sTxMailBox[transmitmailbox].TDLR = 0;
		hcan->Instance->sTxMailBox[transmitmailbox].TDHR = 0;

		for ( DataCounter = 0; DataCounter < hcan->pTxMsg->len; DataCounter++)
		{

			if (DataCounter < 4)                //set LSB (16 bits) of the Data
			{

				hcan->Instance->sTxMailBox[transmitmailbox].TDLR |= (hcan->pTxMsg->data[DataCounter] << (8 * DataCounter)); // masking word byte by byte to low register

			}
			else                                //(DataCounter >= 4) - //set MSB (16 bits) of the Data
			{

				hcan->Instance->sTxMailBox[transmitmailbox].TDHR |= (hcan->pTxMsg->data[DataCounter] << (8 * (DataCounter - 4)));// masking word byte by byte to high register

			}

		}

}
		hcan->Instance->sTxMailBox[transmitmailbox].TIR |= CAN_TI0R_TXRQ;  //Transmit Mailbox Request

 return transmitmailbox;           // result state

}


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

	// message type
	if ((CAN->sFIFOMailBox[Copy_u8FIFOIndex].RIR & 0x2) ==0)
	{ msg->type = DATA_FRAME;}

	else { msg->type = REMOTE_FRAME;}

	//length (number of received bytes)
	msg->len = (u8)0x0000000F & CAN->sFIFOMailBox[Copy_u8FIFOIndex].RDTR;

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

void CAN_voidReceive( CAN_msg *msg, u8 Copy_u8FIFOIndex)
{
	volatile u32* Receive_FIFO_Reg ;
	if (Copy_u8FIFOIndex==0) {Receive_FIFO_Reg = &(CAN1->RF0R);}
	else {Receive_FIFO_Reg = &(CAN1->RF1R);}

	/* Check that there is a message pending */
	if ((*Receive_FIFO_Reg & 0x0003) != 0)		//check FMP bits
	{

		CAN_voidRead(CAN1, msg, Copy_u8FIFOIndex);

	}
	*Receive_FIFO_Reg |= RELEASE_FIFO;
}


/****************************************************************************************/

/*
void CAN_voidTransmit_IT(CAN_HandleTypeDef* hcan)
{
  u32 transmitmailbox = CAN_TXSTATUS_NOMAILBOX;
  if((hcan->State == CAN_STATE_READY) && (hcan->txState == CAN_RXTX_STATE_READY))
  {

	// Select one empty transmit mailbox
	if ((CAN1->TSR & CAN_TSR_TME0) == CAN_TSR_TME0)			//check if mailox 0 is empty
	{
		transmitmailbox = 0;
	}
	else if ((CAN1->TSR & CAN_TSR_TME1) == CAN_TSR_TME1)		//check if mailox 1 is empty
	{
		transmitmailbox = 1;
	}
	else if ((CAN1->TSR & CAN_TSR_TME2) == CAN_TSR_TME2)		//check if mailox 2 is empty
	{
		transmitmailbox = 2;
	}
	else
	{
		transmitmailbox = CAN_TXSTATUS_NOMAILBOX;
	}


    if(transmitmailbox != CAN_TXSTATUS_NOMAILBOX)
    {
      // Set up the Id
      CAN1->sTxMailBox[transmitmailbox].TIR &= CAN_TI0R_TXRQ;
      if (hcan->pTxMsg->IDE == CAN_ID_STD)
      {
        CAN1->sTxMailBox[transmitmailbox].TIR |= (hcan->pTxMsg->->IDE << 3); //extended
      }
      else
      {
        CAN1->sTxMailBox[transmitmailbox].TIR |= (hcan->pTxMsg->->IDE << 21); //standard
      }

      // Set up the DLC
      hcan->pTxMsg->DLC &= (u8)0x0000000F;
      CAN1->sTxMailBox[transmitmailbox].TDTR &= (u32)0xFFFFFFF0;
      CAN1->sTxMailBox[transmitmailbox].TDTR |= hcan->pTxMsg->DLC;

      // Set up the data field
      CAN1->sTxMailBox[transmitmailbox].TDLR= (u32) ((u32)hcan->pTxMsg->Data[3] << CAN_TDL0R_DATA3_BIT_POSITION)
      													|	((u32)hcan->pTxMsg->Data[2] << CAN_TDL0R_DATA2_BIT_POSITION)
      													|	((u32)hcan->pTxMsg->Data[1] << CAN_TDL0R_DATA1_BIT_POSITION)
      													|	((u32)hcan->pTxMsg->Data[0] << CAN_TDL0R_DATA0_BIT_POSITION);

      CAN1->sTxMailBox[transmitmailbox].TDHR= (u32) ((u32)hcan->pTxMsg->Data[7] << CAN_TDL0R_DATA3_BIT_POSITION)
      													|	((u32)hcan->pTxMsg->Data[6] << CAN_TDL0R_DATA2_BIT_POSITION)
      													|	((u32)hcan->pTxMsg->Data[5] << CAN_TDL0R_DATA1_BIT_POSITION)
      													|	((u32)hcan->pTxMsg->Data[4] << CAN_TDL0R_DATA0_BIT_POSITION);



      // Enable interrupts:
      //  - Enable Error warning Interrupt
      //  - Enable Error passive Interrupt
      //  - Enable Bus-off Interrupt
      //  - Enable Last error code Interrupt
      //  - Enable Error Interrupt
      //  - Enable Transmit mailbox empty Interrupt
      CAN1->IER =  CAN_IT_EWG
                            |CAN_IT_EPV
                            |CAN_IT_BOF
                            |CAN_IT_LEC
                            |CAN_IT_ERR
                            |CAN_IT_TME;

      // Request transmission
      CAN1->sTxMailBox[transmitmailbox].TIR |= CAN_TI0R_TXRQ;
    }
  }
}
*/
/************************************************************************/


