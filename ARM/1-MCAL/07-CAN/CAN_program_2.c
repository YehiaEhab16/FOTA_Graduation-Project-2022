/**********************************************************/
/* GRADUATION PROJECT : (FOTA)							  */
/* Version   : V01                                        */
/**********************************************************/

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "CAN_Interface.h"
#include "CAN_Private.h"
#include "CAN_config.h"


void CAN_VidInit(CAN_HandleTypeDef* hcan)
{
  u32 status = CAN_INITSTATUS_FAILED;  /* Default init status */
 
  
  /* Initialize the CAN state*/
  hcan->State = HAL_CAN_STATE_BUSY;
  
  /* Exit from sleep mode */
  CLEAR_BIT(hcan->Instance->MCR, CAN_MCR_SLEEP);

  /* Request initialisation */
  SET_BIT(hcan->Instance->MCR, CAN_MCR_INRQ);


  /* Check acknowledge */
  if ((hcan->Instance->MSR & CAN_MSR_INAK) == CAN_MSR_INAK)
  {
    /* Set the time triggered communication mode */
    if (hcan->Init.TTCM == ENABLE)
    {
      hcan->Instance->MCR |= CAN_MCR_TTCM;
    }
    else
    {
      hcan->Instance->MCR &= ~(u32)CAN_MCR_TTCM;

    /* Set the automatic bus-off management */
    if (hcan->Init.ABOM == ENABLE)
    {
      hcan->Instance->MCR |= CAN_MCR_ABOM;
    }
    else
    {
      hcan->Instance->MCR &= ~(u32)CAN_MCR_ABOM;
    }

    /* Set the automatic wake-up mode */
    if (hcan->Init.AWUM == ENABLE)
    {
      hcan->Instance->MCR |= CAN_MCR_AWUM;
    }
    else
    {
      hcan->Instance->MCR &= ~(u32)CAN_MCR_AWUM;
    }
    
    /* Set the no automatic retransmission */
    if (hcan->Init.NART == ENABLE)
    {
      hcan->Instance->MCR |= CAN_MCR_NART;
    }
    else
    {
      hcan->Instance->MCR &= ~(u32)CAN_MCR_NART;
    }

    /* Set the receive FIFO locked mode */
    if (hcan->Init.RFLM == ENABLE)
	{
      hcan->Instance->MCR |= CAN_MCR_RFLM;
    }
    else
    {
      hcan->Instance->MCR &= ~(u32)CAN_MCR_RFLM;
    }
    
    /* Set the transmit FIFO priority */
    if (hcan->Init.TXFP == ENABLE)
    {
      hcan->Instance->MCR |= CAN_MCR_TXFP;
    }
    else
    {
      hcan->Instance->MCR &= ~(u32)CAN_MCR_TXFP;
    }

	hcan->Instance->BTR =(u32)     ((u32)hcan->Init.Mode << 30   )  
							 |     ((u32)hcan->Init.SJW  << 24   )  
							 |     ((u32)hcan->Init.BS1  << 16   )  
							 |     ((u32)hcan->Init.BS2  << 20   )  
							 |     ((u32)hcan->Init.Prescaler-1  ) ;
		
    /* Request leave initialisation */
    CLEAR_BIT(hcan->Instance->MCR, CAN_MCR_INRQ);

}



/****************************************************************************************/
void CAN_VidTransmit(CAN_HandleTypeDef* hcan)
{
	u32 transmitmailbox = CAN_TXSTATUS_NOMAILBOX;


  hcan->txState = CAN_RXTX_STATE_BUSY;
  
  /* Select one empty transmit mailbox */
  if ((hcan->Instance->TSR & CAN_TSR_TME0) == CAN_TSR_TME0)			//check if mailox 0 is empty
  {
    transmitmailbox = 0;
  }
  else if (hcan->Instance->TSR & CAN_TSR_TME1) == CAN_TSR_TME1))	//check if mailox 1 is empty
  {
    transmitmailbox = 1;
  }
  else if (hcan->Instance->TSR & CAN_TSR_TME2) == CAN_TSR_TME2))	//check if mailox 2 is empty
  {
    transmitmailbox = 2;
  }
  else
  {
    transmitmailbox = CAN_TXSTATUS_NOMAILBOX;
  }

  if (transmitmailbox != CAN_TXSTATUS_NOMAILBOX)
  {
    /* Set up the Id */
    hcan->Instance->sTxMailBox[transmitmailbox].TIR &= CAN_TI0R_TXRQ;
    if (hcan->pTxMsg->IDE == CAN_ID_STD)
    {											   
	  hcan->Instance->sTxMailBox[transmitmailbox].TIR |= (hcan->pTxMsg->->IDE << 3); //extended
    }
    else
    {
	  hcan->Instance->sTxMailBox[transmitmailbox].TIR |= (hcan->pTxMsg->->IDE << 21); //standard
    }
    
    /* Set up the DLC */
    hcan->pTxMsg->DLC &= (u8)0x0000000F;
    hcan->Instance->sTxMailBox[transmitmailbox].TDTR &= (u32)0xFFFFFFF0;
    hcan->Instance->sTxMailBox[transmitmailbox].TDTR |= hcan->pTxMsg->DLC;

    /* Set up the data field */
    hcan->Instance->sTxMailBox[transmitmailbox].TDLR= (u32) ((u32)hcan->pTxMsg->Data[3] << CAN_TDL0R_DATA3_BIT_POSITION)
														|	((u32)hcan->pTxMsg->Data[2] << CAN_TDL0R_DATA2_BIT_POSITION)
														|	((u32)hcan->pTxMsg->Data[1] << CAN_TDL0R_DATA1_BIT_POSITION)
														|	((u32)hcan->pTxMsg->Data[0] << CAN_TDL0R_DATA0_BIT_POSITION);
														
    hcan->Instance->sTxMailBox[transmitmailbox].TDHR= (u32) ((u32)hcan->pTxMsg->Data[7] << CAN_TDL0R_DATA3_BIT_POSITION)
														|	((u32)hcan->pTxMsg->Data[6] << CAN_TDL0R_DATA2_BIT_POSITION)
														|	((u32)hcan->pTxMsg->Data[5] << CAN_TDL0R_DATA1_BIT_POSITION)
														|	((u32)hcan->pTxMsg->Data[4] << CAN_TDL0R_DATA0_BIT_POSITION);
															
	
    /* Request transmission */
    SET_BIT(hcan->Instance->sTxMailBox[transmitmailbox].TIR, CAN_TI0R_TXRQ);
}
}
  


/****************************************************************************************/
void CAN_vidTransmit_IT(CAN_HandleTypeDef* hcan)
{
  u32 transmitmailbox = CAN_TXSTATUS_NOMAILBOX;


  if((hcan->State == CAN_STATE_READY) && (hcan->txState == CAN_RXTX_STATE_READY))
  {
    /* Process Locked */
    //__HAL_LOCK(hcan);
    
	/* Select one empty transmit mailbox */
	if ((hcan->Instance->TSR & CAN_TSR_TME0) == CAN_TSR_TME0)			//check if mailox 0 is empty
	{
		transmitmailbox = 0;
	}
	else if (hcan->Instance->TSR & CAN_TSR_TME1) == CAN_TSR_TME1))		//check if mailox 1 is empty
	{
		transmitmailbox = 1;
	}
	else if (hcan->Instance->TSR & CAN_TSR_TME2) == CAN_TSR_TME2))		//check if mailox 2 is empty
	{
		transmitmailbox = 2;
	}
	else
	{
		transmitmailbox = CAN_TXSTATUS_NOMAILBOX;
	}
	
	

    if(transmitmailbox != CAN_TXSTATUS_NOMAILBOX)
    {
      /* Set up the Id */
      hcan->Instance->sTxMailBox[transmitmailbox].TIR &= CAN_TI0R_TXRQ;
      if (hcan->pTxMsg->IDE == CAN_ID_STD)
      {											   
        hcan->Instance->sTxMailBox[transmitmailbox].TIR |= (hcan->pTxMsg->->IDE << 3); //extended
      }
      else
      {
        hcan->Instance->sTxMailBox[transmitmailbox].TIR |= (hcan->pTxMsg->->IDE << 21); //standard
      }
      
      /* Set up the DLC */
      hcan->pTxMsg->DLC &= (u8)0x0000000F;
      hcan->Instance->sTxMailBox[transmitmailbox].TDTR &= (u32)0xFFFFFFF0;
      hcan->Instance->sTxMailBox[transmitmailbox].TDTR |= hcan->pTxMsg->DLC;
      
      /* Set up the data field */
      hcan->Instance->sTxMailBox[transmitmailbox].TDLR= (u32) ((u32)hcan->pTxMsg->Data[3] << CAN_TDL0R_DATA3_BIT_POSITION)
      													|	((u32)hcan->pTxMsg->Data[2] << CAN_TDL0R_DATA2_BIT_POSITION)
      													|	((u32)hcan->pTxMsg->Data[1] << CAN_TDL0R_DATA1_BIT_POSITION)
      													|	((u32)hcan->pTxMsg->Data[0] << CAN_TDL0R_DATA0_BIT_POSITION);
      													
      hcan->Instance->sTxMailBox[transmitmailbox].TDHR= (u32) ((u32)hcan->pTxMsg->Data[7] << CAN_TDL0R_DATA3_BIT_POSITION)
      													|	((u32)hcan->pTxMsg->Data[6] << CAN_TDL0R_DATA2_BIT_POSITION)
      													|	((u32)hcan->pTxMsg->Data[5] << CAN_TDL0R_DATA1_BIT_POSITION)
      													|	((u32)hcan->pTxMsg->Data[4] << CAN_TDL0R_DATA0_BIT_POSITION);
      
      
      
      
    
      hcan->txState = CAN_RXTX_STATE_BUSY;
      
      /* Set CAN error code to none */
      hcan->ErrorCode = CAN_ERROR_NONE;
      
      /* Process Unlocked */
      //__HAL_UNLOCK(hcan);
      
      /* Enable interrupts: */
      /*  - Enable Error warning Interrupt */
      /*  - Enable Error passive Interrupt */
      /*  - Enable Bus-off Interrupt */
      /*  - Enable Last error code Interrupt */
      /*  - Enable Error Interrupt */
      /*  - Enable Transmit mailbox empty Interrupt */

      hcan->Instance->IER =  CAN_IT_EWG 
                            |CAN_IT_EPV
                            |CAN_IT_BOF
                            |CAN_IT_LEC
                            |CAN_IT_ERR
                            |CAN_IT_TME;
      
      /* Request transmission */
      hcan->Instance->sTxMailBox[transmitmailbox].TIR |= CAN_TI0R_TXRQ;
    }
  }
}
