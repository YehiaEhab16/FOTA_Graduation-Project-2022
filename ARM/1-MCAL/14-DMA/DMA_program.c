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

u8 DMA_u8Configuration(DMA_t* Copy_DMA_tTransferConfig)
{
	u8 Local_u8ErrorState=OK;
	u32* DMA_CCR;
	u32*DMA_CNDTR;


	DMA_CCR   = (u32*)(DMA1_CCR1   + (Copy_DMA_tTransferConfig->DMA_u8ChannelID-1)*(u32)DMA_CHANNEL_OFFSET);
	DMA_CNDTR = (u32*)(DMA1_CNDTR1 + (Copy_DMA_tTransferConfig->DMA_u8ChannelID-1)*DMA_CHANNEL_OFFSET);

	//Disable DMA1
	CLR_BIT(*DMA_CCR,EN);
	while (GET_BIT(*DMA_CCR,EN) == 1) ;


	//Number of data to be transferred 
	*DMA_CNDTR = Copy_DMA_tTransferConfig->DMA_u8DataTransferNum;


	//Set channel priority
	switch(Copy_DMA_tTransferConfig->DMA_u8ChannelPriority)
	{
	case DMA_PRIORITY_LOW:CLR_BIT(*DMA_CCR,PL0);
	CLR_BIT(*DMA_CCR,PL1);
	break;
	case DMA_PRIORITY_MED:SET_BIT(*DMA_CCR,PL0);
	CLR_BIT(*DMA_CCR,PL1);
	break;
	case DMA_PRIORITY_HIGH:CLR_BIT(*DMA_CCR,PL0);
	SET_BIT(*DMA_CCR,PL1);
	break;
	case DMA_PRIORITY_VERY_HIGH : CLR_BIT(*DMA_CCR,PL0);
	SET_BIT(*DMA_CCR,PL1);
	break;
	default: Local_u8ErrorState=NOK;
	}


	//Set data direction
	if(Copy_DMA_tTransferConfig->DMA_u8DataDirection == DMA_DIR_MEM2MEM)
	{
		SET_BIT(*DMA_CCR,MEM2MEM);
		SET_BIT(*DMA_CCR,DIR);

	}
	else if(Copy_DMA_tTransferConfig->DMA_u8DataDirection == DMA_DIR_PER2MEM)
	{
		CLR_BIT(*DMA_CCR,MEM2MEM);
		CLR_BIT(*DMA_CCR,DIR);

	}
	else if (Copy_DMA_tTransferConfig ->DMA_u8DataDirection ==DMA_DIR_MEM2PER )
	{
		CLR_BIT(*DMA_CCR,MEM2MEM);
		SET_BIT(*DMA_CCR,DIR);

	}

	else
		Local_u8ErrorState = NOK;


	//Set Periheral  Data Size
	if(Copy_DMA_tTransferConfig->DMA_u8PeripheralDataSize == 8)
	{
		CLR_BIT(*DMA_CCR,PSIZE0);
		CLR_BIT(*DMA_CCR,PSIZE1);
	}
	else if(Copy_DMA_tTransferConfig->DMA_u8PeripheralDataSize == 16)
	{
		SET_BIT(*DMA_CCR,PSIZE0);
		CLR_BIT(*DMA_CCR,PSIZE1);
	}
	else if(Copy_DMA_tTransferConfig->DMA_u8PeripheralDataSize == 32)
	{
		CLR_BIT(*DMA_CCR,PSIZE0);
		SET_BIT(*DMA_CCR,PSIZE1);
	}
	else
		Local_u8ErrorState = NOK;

	//Set Memory  Data Size
	if(Copy_DMA_tTransferConfig->DMA_u8MemDataSize == 8)
	{
		CLR_BIT(*DMA_CCR,MSIZE0);
		CLR_BIT(*DMA_CCR,MSIZE1);

	}
	else if(Copy_DMA_tTransferConfig->DMA_u8MemDataSize == 16)
	{
		SET_BIT(*DMA_CCR,MSIZE0);
		CLR_BIT(*DMA_CCR,MSIZE1);

	}
	else if(Copy_DMA_tTransferConfig->DMA_u8MemDataSize == 32)
	{
		CLR_BIT(*DMA_CCR,MSIZE0);
		SET_BIT(*DMA_CCR,MSIZE1);

	}
	else
		Local_u8ErrorState = NOK;


	//Set transfer modes
#if DMA_MEM2MEM_MODE == DMA_DISABLE
	CLR_BIT(*DMA_CCR,MEM2MEM);
#else
	SET_BIT(*DMA_CCR,MEM2MEM);
#endif
#if DMA_MEM_INC_MODE == DMA_DISABLE
	CLR_BIT(*DMA_CCR,MINC);
#else
	SET_BIT(*DMA_CCR,MINC);
#endif
#if DMA_PER_INC_MODE == DMA_DISABLE
	CLR_BIT(*DMA_CCR,PINC);
#else
	SET_BIT(*DMA_CCR,PINC);
#endif
#if DMA_CIRCULAR_MODE == DMA_DISABLE
	CLR_BIT(*DMA_CCR,CIRC);
#else
	SET_BIT(*DMA_CCR,CIRC);
#endif
	//Set Interrupt flag
#if DMA_INT_TE == DMA_DISABLE
	CLR_BIT(*DMA_CCR,TEIE);
#else
	SET_BIT(*DMA_CCR,TEIE);
#endif
#if DMA_INT_HT == DMA_DISABLE
	CLR_BIT(*DMA_CCR,HTIE);
#else
	SET_BIT(*DMA_CCR,HTIE);
#endif
#if DMA_INT_TC == DMA_DISABLE
	CLR_BIT(*DMA_CCR,TCIE);
#else
	SET_BIT(*DMA_CCR,TCIE);
#endif

	Copy_DMA_tTransferConfig->DMA_Configure = 1 ;
	return Local_u8ErrorState;
}

u8 DMA_u8Enable (DMA_t* Copy_DMA_tTransferConfig , u32* Copy_u32PeripheralAddress, u32* Copy_u32MemoryAddress )
{
	u8 Local_u8ErrorState = OK ;
	u32*DMA_CPAR;
	u32*DMA_CMAR;

	u32* DMA_CCR;
	DMA_CPAR  = (u32*)(DMA1_CPAR1  + (Copy_DMA_tTransferConfig->DMA_u8ChannelID-1)*DMA_CHANNEL_OFFSET);
	DMA_CMAR  = (u32*)(DMA1_CMAR1  + (Copy_DMA_tTransferConfig->DMA_u8ChannelID-1)*DMA_CHANNEL_OFFSET);
	DMA_CCR   = (u32*)(DMA1_CCR1   + (Copy_DMA_tTransferConfig->DMA_u8ChannelID-1)*DMA_CHANNEL_OFFSET);

	if (Copy_DMA_tTransferConfig->DMA_Configure == 1)
	{
		*DMA_CPAR = (u32)Copy_u32PeripheralAddress ;
		*DMA_CMAR = (u32)Copy_u32MemoryAddress ;

		//Enable Channel
		SET_BIT(*DMA_CCR,EN);
	}
	else
	{
		Local_u8ErrorState = NOK ;

	}
	return Local_u8ErrorState ;


}

u8 DMA_u8Disable (DMA_t* Copy_DMA_tTransferConfig)
{
	u8 Local_u8ErrorState = OK ;


	u32* DMA_CCR;

	DMA_CCR   = (u32*)(DMA1_CCR1   + (Copy_DMA_tTransferConfig->DMA_u8ChannelID-1)*DMA_CHANNEL_OFFSET);

	if (Copy_DMA_tTransferConfig->DMA_Configure == 1)
	{
		//Enable Channel
		CLR_BIT(*DMA_CCR,EN);
	}
	else
	{
		Local_u8ErrorState = NOK ;

	}
	return Local_u8ErrorState ;




}

