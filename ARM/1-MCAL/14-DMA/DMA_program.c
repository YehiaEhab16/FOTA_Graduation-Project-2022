/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer : MCAL                  ***********************/
/***********************   SWC (DRIVER):DMA				 ***********************/
/***********************   DATE : 26-5-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../../6-Library/STD_TYPES.h"
#include "../../6-Library/BIT_MATH.h"

#include "DMA_interface.h"
#include "DMA_config.h"
#include "DMA_private.h"
#include "DMA_register.h"

u8 DMA_u8ReadRegisterContent(DMA_t* Copy_DMA_tTransferConfig)
{
	u8 Local_u8ErrorState=OK;
	u32 DMA_CCR, DMA_CNDTR, DMA_CPAR, DMA_CMAR;

	if((Copy_DMA_tTransferConfig->DMA_u8PeripheralID >= DMA_PER_ADC1) &&(Copy_DMA_tTransferConfig->DMA_u8PeripheralID <= DMA_PER_TIMER4))
	{
		DMA_CCR   = DMA1_CCR1   + (Copy_DMA_tTransferConfig->DMA_u8ChannelID-1)*DMA_CHANNEL_OFFSET;
		DMA_CNDTR = DMA1_CNDTR1 + (Copy_DMA_tTransferConfig->DMA_u8ChannelID-1)*DMA_CHANNEL_OFFSET;
		DMA_CPAR  = DMA1_CPAR1  + (Copy_DMA_tTransferConfig->DMA_u8ChannelID-1)*DMA_CHANNEL_OFFSET;
		DMA_CMAR  = DMA1_CMAR1  + (Copy_DMA_tTransferConfig->DMA_u8ChannelID-1)*DMA_CHANNEL_OFFSET;
	}
	else if((Copy_DMA_tTransferConfig->DMA_u8PeripheralID >= DMA_PER_ADC3) &&(Copy_DMA_tTransferConfig->DMA_u8PeripheralID <= DMA_PER_TIMER8))
	{
		DMA_CCR   = DMA2_CCR1   + (Copy_DMA_tTransferConfig->DMA_u8ChannelID-1)*DMA_CHANNEL_OFFSET;
		DMA_CNDTR = DMA2_CNDTR1 + (Copy_DMA_tTransferConfig->DMA_u8ChannelID-1)*DMA_CHANNEL_OFFSET;
		DMA_CPAR  = DMA2_CPAR1  + (Copy_DMA_tTransferConfig->DMA_u8ChannelID-1)*DMA_CHANNEL_OFFSET;
		DMA_CMAR  = DMA2_CMAR1  + (Copy_DMA_tTransferConfig->DMA_u8ChannelID-1)*DMA_CHANNEL_OFFSET;
	}
	else 
		Local_u8ErrorState=NOK;
	//Set Peripheral Address
	*DMA_CPAR = Copy_DMA_tTransferConfig->DMA_u8PeripheralID;
	//Set Memory Address 
	*DMA_CMAR = DMA_MEMORY_ADDRESS;
	//Number of data to be transferred 
	*DMA_CNDTR = Copy_DMA_tTransferConfig->DMA_u8DataTransferNum;
	//Set channel priority
	switch(Copy_DMA_tTransferConfig->DMA_u8ChannelPriority)
	{
		case DMA_PRIORITY_LOW:CLR_BIT(DMA_CCR,PL0);
							  CLR_BIT(DMA_CCR,PL1);
							  break;
		case DMA_PRIORITY_MED:SET_BIT(DMA_CCR,PL0);
							  CLR_BIT(DMA_CCR,PL1);
							  break;
		case DMA_PRIORITY_HIGH:CLR_BIT(DMA_CCR,PL0);
							   SET_BIT(DMA_CCR,PL1);
							   break;
		default: Local_u8ErrorState=NOK;
	}
	//Set data direction
	if(Copy_DMA_tTransferConfig->DMA_u8DataDirection == DMA_DIR_MEM2PER)
		CLR_BIT(DMA_CCR,DIR);
	else if(Copy_DMA_tTransferConfig->DMA_u8DataDirection == DMA_DIR_PER2MEM)
		SET_BIT(DMA_CCR,DIR);
	else
		Local_u8ErrorState = NOK;
	//Set Data Size
	if(Copy_DMA_tTransferConfig->DMA_u8DataDirection == 8)
	{
		CLR_BIT(DMA_CCR,MSIZE0);
		CLR_BIT(DMA_CCR,MSIZE1);
		CLR_BIT(DMA_CCR,PSIZE0);
		CLR_BIT(DMA_CCR,PSIZE1);
	}
	else if(Copy_DMA_tTransferConfig->DMA_u8DataDirection == 16)
	{
		SET_BIT(DMA_CCR,MSIZE0);
		CLR_BIT(DMA_CCR,MSIZE1);
		SET_BIT(DMA_CCR,PSIZE0);
		CLR_BIT(DMA_CCR,PSIZE1);
	}
	else if(Copy_DMA_tTransferConfig->DMA_u8DataDirection == 32)
	{
		CLR_BIT(DMA_CCR,MSIZE0);
		SET_BIT(DMA_CCR,MSIZE1);
		CLR_BIT(DMA_CCR,PSIZE0);
		SET_BIT(DMA_CCR,PSIZE1);
	}
	else
		Local_u8ErrorState = NOK;
	//Set transfer modes
	#if DMA_MEM2MEM_MODE == DMA_DISABLE
	CLR_BIT(DMA_CCR,MEM2MEM);
	#else
	SET_BIT(DMA_CCR,MEM2MEM);
	#endif
	#if DMA_MEM_INC_MODE == DMA_DISABLE
	CLR_BIT(DMA_CCR,MINC);
	#else
	SET_BIT(DMA_CCR,MINC);
	#endif
	#if DMA_PER_INC_MODE == DMA_DISABLE
	CLR_BIT(DMA_CCR,PINC);
	#else
	SET_BIT(DMA_CCR,PINC);
	#endif
	#if DMA_CIRCULAR_MODE == DMA_DISABLE
	CLR_BIT(DMA_CCR,CIRC);
	#else
	SET_BIT(DMA_CCR,CIRC);
	#endif
	//Set Interrupt flag
	#if DMA_INT_TE == DMA_DISABLE
	CLR_BIT(DMA_CCR,TEIE);
	#else
	SET_BIT(DMA_CCR,TEIE);
	#endif
	#if DMA_INT_HT == DMA_DISABLE
	CLR_BIT(DMA_CCR,HTIE);
	#else
	SET_BIT(DMA_CCR,HTIE);
	#endif
	#if DMA_INT_TC == DMA_DISABLE
	CLR_BIT(DMA_CCR,TCIE);
	#else
	SET_BIT(DMA_CCR,TCIE);
	#endif
	//Enable Channel
	SET_BIT(DMA_CCR,EN);
	
	return Local_u8ErrorState;
}
