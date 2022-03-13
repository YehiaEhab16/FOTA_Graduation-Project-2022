#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "PORT_interface.h"
#include "PORT_register.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "GPIO_register.h"
#include "CAN_interface.h"
#include "CAN_private.h"
#include "CAN_config.h"


CAN_msg  CAN_TxMsg, CAN_RxMsg;

static CAN_t *CAN_Get(u8 can) {
    switch(can) {
        case CAN1: return (CAN_t*) CAN1_BASE;
        case CAN2: return (CAN_t*) CAN2_BASE;
        default: return (CAN_t*) CAN2_BASE;
    }
}

static void CAN_PinConfig(u8 can) {
    switch(can) {
        case CAN1: RCC_voidEnableClock(RCC_APB2, 2);
        		   GPIO_u8SetPinMode (GPIO_PORTA, GPIO_PIN_11, OUTPUT_SPEED_10MHZ_AFPP);          // CAN RX pin PA.0 input push pull
    			   GPIO_u8SetPinMode (GPIO_PORTA, GPIO_PIN_12, OUTPUT_SPEED_10MHZ_AFPP);         //TX pin PA.1 AF output push pull
    			   break;
        case CAN2: RCC_voidEnableClock(RCC_APB2, 3);
        		   GPIO_u8SetPinMode (GPIO_PORTB, GPIO_PIN_8, OUTPUT_SPEED_10MHZ_AFPP);          // CAN RX pin PA.0 input push pull
				   GPIO_u8SetPinMode (GPIO_PORTB, GPIO_PIN_9, OUTPUT_SPEED_10MHZ_AFPP);         //TX pin PA.1 AF output push pull
				   break;
        default: RCC_voidEnableClock(RCC_APB2, 2);
        		 GPIO_u8SetPinMode (GPIO_PORTA, GPIO_PIN_11, INPUT_PULLUP_PULLDOWN);
                 GPIO_u8SetPinMode (GPIO_PORTA, GPIO_PIN_12, OUTPUT_SPEED_10MHZ_AFPP);
    }
}

PERIPHERAL_t CAN_Peripherals[] = {{RCC_APB1,RCC_APB1_CAN_EN},
								  {RCC_APB1,RCC_APB1_CAN_EN}};

void CAN_voidInit(u8 Copy_u8CAN, u32 Copy_u32Mode)
{
	CAN_t *CAN = CAN_Get(Copy_u8CAN);
	RCC_u8EnableClock (&CAN_Peripherals[Copy_u8CAN]);	       	  // enable clock for CAN1
	RCC_voidEnableClock(RCC_APB2,0);            	// enable clock for Alternate Function

	CAN_PinConfig(Copy_u8CAN);

	CAN->MCR |= CAN_MCR_TXFP;					  //set TXFP (priority by request order)
	CAN->MCR &= ~CAN_MCR_RFLM;					  //overrun fifo
	CAN->MCR |= CAN_MCR_NART;                     //no auto retransmission
	CAN->MCR |= CAN_MCR_ABOM;					  //auto bus off management

	CAN->BTR =  0x031C0009;    			          //bit-timing /***** temporary *****/
    CAN->BTR |= Copy_u32Mode;

    CAN->MCR &= ~CAN_MCR_SLEEP;                   // exit sleep mode
    CAN->MCR |= CAN_MCR_INRQ;                     // init mode
    /* wait for initialization mode*/
    while(((CAN->MSR & CAN_MCR_SLEEP) == CAN_MCR_SLEEP)
    	|| ((CAN->MSR & CAN_MCR_INRQ) != CAN_MCR_INRQ));

    CAN->MCR &= ~1;                      // reset INRQ (normal operating mode)
}


static void CAN_write (CAN_t *CAN, CAN_msg *msg, u8 Copy_u8MailBoxIndex)
{
	while(!(CAN->TSR & CAN_TSR_TME0));
	switch (Copy_u8MailBoxIndex)
	{
		case CAN_TXMAILBOX_0: while(!(CAN->TSR & CAN_TSR_TME0)); break;
		case CAN_TXMAILBOX_1: while(!(CAN->TSR & CAN_TSR_TME1)); break;
		case CAN_TXMAILBOX_2: while(!(CAN->TSR & CAN_TSR_TME2)); break;
		default : CAN->sTxMailBox[Copy_u8MailBoxIndex].TIR  = (u32)(msg->id << 21) ;
	}

	switch (msg->format)
	{
		case CAN_ID_STD: CAN->sTxMailBox[Copy_u8MailBoxIndex].TIR  = (u32)(msg->id << 21) ; break;
		case CAN_ID_EXT: CAN->sTxMailBox[Copy_u8MailBoxIndex].TIR  = (u32)(msg->id <<3) | 4; break;
		default : CAN->sTxMailBox[Copy_u8MailBoxIndex].TIR  = (u32)(msg->id << 21) ;
	}

	switch (msg->type)
	{
		case DATA_FRAME  : CAN->sTxMailBox[Copy_u8MailBoxIndex].TIR &= ~(1<<1); break;
		case REMOTE_FRAME: CAN->sTxMailBox[Copy_u8MailBoxIndex].TIR |= 1<<1; break;
		default: CAN->sTxMailBox[Copy_u8MailBoxIndex].TIR |= 1<<1;
	}

	CAN->sTxMailBox[Copy_u8MailBoxIndex].TDLR = (((u32)msg->data[3] << 24)|
												((u32)msg->data[2] << 16) |
												((u32)msg->data[1] <<  8) |
												((u32)msg->data[0]));

	CAN->sTxMailBox[Copy_u8MailBoxIndex].TDHR =  (((u32)msg->data[7] << 24)|
											     ((u32)msg->data[6] << 16) |
											     ((u32)msg->data[5] <<  8) |
											     ((u32)msg->data[4]));

	CAN->sTxMailBox[Copy_u8MailBoxIndex].TDTR &= ~0xf; 					// Setup length
	CAN->sTxMailBox[Copy_u8MailBoxIndex].TDTR |=  (msg->len & 0xf);
	CAN->sTxMailBox[Copy_u8MailBoxIndex].TIR |=  1;                     // transmit message
}
/*
	 Copy_u8CAN : 		 CAN1 or CAN2
	 Copy_u32ID :		 Message ID
	 Copy_u8IDType :	 (EXTENDED \OR STANDARD)
	 Copy_u8FrameType :  (DATA_FRAME \OR REMOTE_FRAME)
     Mailbox :			 to send the Message

//*/
void CAN_voidTransmit(u8 Copy_u8CAN, u32 Copy_u32ID, u8 Copy_u8IDType, u8 Copy_u8FrameType, u8 *m, u8 mailIndex)
{  	u8 Local_u8ByteCount;
	CAN_t *CAN = CAN_Get(Copy_u8CAN);
   	CAN_TxMsg.id = Copy_u32ID;     // initialize message to send
   	for (Local_u8ByteCount = 0; Local_u8ByteCount < 8; Local_u8ByteCount++)
   	{
   		CAN_TxMsg.data[Local_u8ByteCount] = m[Local_u8ByteCount];
   	}
  	CAN_TxMsg.len = 8;
  	CAN_TxMsg.format = Copy_u8IDType;
  	CAN_TxMsg.type = Copy_u8FrameType;
  	CAN_write(CAN, &CAN_TxMsg, mailIndex);   // transmit message
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

void CAN_voidReceive(u8 Copy_u8CAN, CAN_msg *msg, u8 Copy_u8FIFOIndex)
{
	CAN_t *CAN = CAN_Get(Copy_u8CAN);
	u32 Receive_FIFO_Reg ;
	if (Copy_u8FIFOIndex==0) {Receive_FIFO_Reg = CAN->RF0R;}
	else {Receive_FIFO_Reg = CAN->RF1R;}

	/* Check that there is a message pending */
	if ((Receive_FIFO_Reg & 0x0003) != 0)		//check FMP bits
	{
		CAN_voidRead(CAN, msg, Copy_u8FIFOIndex);
	}
	//Receive_FIFO_Reg |= RELEASE;		// Release FIFO
}

void CAN_VoidFilterSet(u8 Copy_u8CAN,CAN_FilterInitTypeDef* CAN_FilterInitStruct)
{

	CAN_t *CAN = CAN_Get(Copy_u8CAN);

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



		Local_u32filterNumberPosition = ( (u32)(1) ) << CAN_FilterInitStruct->CAN_FilterBankNumber;

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
					CAN->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR1 =  ((0x0000FFFF &  (u32)Local_u16FilterbankMaskId) << 16 )
																							 | (0x0000FFFF &  (u32)Local_u16FilterbankId           ) ;
					CAN->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR2 =  ((0x0000FFFF &  (u32)Local_u16FilterbankMaskId) << 16 )
																							 | (0x0000FFFF &  (u32)Local_u16FilterbankId           ) ;
				break;

				case (CAN_FILTERMODE_IDLIST):
				/* ( CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdList )*/

					/*Identifier list mode for the filter*/
					CAN->FM1R |= (u32)Local_u32filterNumberPosition;

									   /*FR1 =FR2 = [Local_u16FilterbankId |Local_u16FilterbankId]*/
					CAN->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR1 = ((0x0000FFFF &  (u32)Local_u16FilterbankId) << 16 )
																							| (0x0000FFFF &  (u32)Local_u16FilterbankId       ) ;
					CAN->sFilterRegister[CAN_FilterInitStruct->CAN_FilterBankNumber].FR2 = ((0x0000FFFF &  (u32)Local_u16FilterbankId) << 16 )
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
	if (CAN_FilterInitStruct->CAN_FilterActivation == 1) CAN->FA1R |= Local_u32filterNumberPosition;

    CAN->FMR &= ~CAN_FMR_FINIT;     //release init mode for the input filter */
}


//
//////Initialize Filters
////static void CAN_wrFilter (CAN_t *CAN, u32 Copy_u32ID, u8 Copy_u8IDFormat) /***** temporary *****/
////{
////	static u8 Local_u8FilterNumber = FilterNumber;
////		u32   CAN_msgId = 0;
////
////		if (Local_u8FilterNumber > 27) {return;}
////		// Setup identifier information
////		switch (Copy_u8IDFormat)
////		{
////		case CAN_ID_STD: CAN_msgId  |= (u32)(Copy_u32ID << 21) ; break;
////		case CAN_ID_EXT: CAN_msgId  |= (u32)(Copy_u32ID <<3) | 4; break;
////		}
////
////
////		CAN->FA1R &=  ~(u32)(1 << Local_u8FilterNumber); // deactivate filter
////
////		// initialize filter
////		CAN->FS1R |= (u32)(1 << Local_u8FilterNumber);// set 32-bit scale configuration
////		CAN->FM1R |= (u32)(1 << Local_u8FilterNumber);// set 2 32-bit identifier list mode
////
////		CAN->sFilterRegister[Local_u8FilterNumber].FR1 = CAN_msgId; //  32-bit identifier
////		CAN->sFilterRegister[Local_u8FilterNumber].FR2 = CAN_msgId; //  32-bit identifier
////
////		switch (FilterFIFO)
////		{
////			case CAN_FIFO_0: CAN->FFA1R &= ~(u32)(1 << Local_u8FilterNumber); break;  // assign filter to FIFO 0
////			case CAN_FIFO_1: CAN->FFA1R |= (u32)(1 << Local_u8FilterNumber); break;  // assign filter to FIFO 1
////			default: CAN->FFA1R &= ~(u32)(1 << Local_u8FilterNumber);
////		}
////
////		CAN->FA1R  |=  (u32)(1 << Local_u8FilterNumber);  // activate filter
////
////		Local_u8FilterNumber += 1;                             // increase filter index
////		CAN->RF0R=RELEASE;
////
////}
////
////void CAN_voidFiltersInit(u8 Copy_u8CAN, u32 Copy_u32ID)
////{
////	CAN_t *CAN = CAN_Get(Copy_u8CAN);
////	CAN->FMR = 1;                                   		   		 //init mode for filters
////	CAN_wrFilter (CAN, Copy_u32ID, CAN_ID_EXT);
////	CAN->FMR &= ~1;                         						 // Active filters mode.
////
////}
