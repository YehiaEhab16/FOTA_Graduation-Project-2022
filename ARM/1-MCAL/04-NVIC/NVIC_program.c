/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):NVIC 			 ***********************/
/***********************   DATA : 2-4-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "NVIC_interface.h"
#include "NVIC_private.h"
#include "NVIC_config.h"
#include "NVIC_regisiter.h"

void NVIC_voidInit (void)
{
	//configuration Number of Groups and number of sub group
	SCB_AIRCR = (VETKEY)|(NVIC_GROUP<<8);
}

u8 NVIC_u8GetRegisterNumber (u8 Copy_u8NameInterrupt,u8*Copy_u8RegisterNumberVal )
{
	u8 Local_u8ErrorState = OK ;
	if (Copy_u8NameInterrupt<60)
	{
		*Copy_u8RegisterNumberVal = (u8)(Copy_u8NameInterrupt/32);

	}
	else
	{
		Local_u8ErrorState =NOK ;
	}



	return Local_u8ErrorState ;


}
u8 NVIC_u8GetRegisterBit (u8 Copy_u8NameInterrupt,u8*Copy_u8RegisterBitVal )
{
	u8 Local_u8ErrorState = OK ;
	if (Copy_u8NameInterrupt<60)
	{
		*Copy_u8RegisterBitVal =Copy_u8NameInterrupt-(32*((u8)(Copy_u8NameInterrupt/32)));


	}
	else
	{
		Local_u8ErrorState =NOK ;
	}



	return Local_u8ErrorState ;


}

u8 NVIC_u8EnableInterrupt (u8 Copy_u8NameInterrupt)
{
	u8 Local_u8ErrorState = OK ;
	u8 Local_u8RegisterNum = 0 ;
	u8 Local_u8RegisterBit =0 ;
	if (Copy_u8NameInterrupt<60)
	{
		NVIC_u8GetRegisterBit(Copy_u8NameInterrupt,&Local_u8RegisterBit);
		NVIC_u8GetRegisterNumber(Copy_u8NameInterrupt,&Local_u8RegisterNum);
		SET_BIT(NVIC ->ISER[Local_u8RegisterNum],Local_u8RegisterBit);

	}
	else
	{
		Local_u8ErrorState =NOK ;
	}



	return Local_u8ErrorState ;
}

u8 NVIC_u8disableInterrupt (u8 Copy_u8NameInterrupt)
{
	u8 Local_u8ErrorState = OK ;
	u8 Local_u8RegisterNum = 0 ;
	u8 Local_u8RegisterBit =0 ;
	if (Copy_u8NameInterrupt<60)
	{
		NVIC_u8GetRegisterBit(Copy_u8NameInterrupt,&Local_u8RegisterBit);
		NVIC_u8GetRegisterNumber(Copy_u8NameInterrupt,&Local_u8RegisterNum);
		SET_BIT(NVIC->ICER[Local_u8RegisterNum],Local_u8RegisterBit);


	}
	else
	{
		Local_u8ErrorState =NOK ;
	}


	return Local_u8ErrorState ;

}

u8 NVIC_u8EnablePendingFlag (u8 Copy_u8NameInterrupt)
{
	u8 Local_u8ErrorState = OK ;
	u8 Local_u8RegisterNum = 0 ;
	u8 Local_u8RegisterBit =0 ;
	if (Copy_u8NameInterrupt<60)
	{
		NVIC_u8GetRegisterBit(Copy_u8NameInterrupt,&Local_u8RegisterBit);
		NVIC_u8GetRegisterNumber(Copy_u8NameInterrupt,&Local_u8RegisterNum);
		SET_BIT(NVIC->ISPR[Local_u8RegisterNum],Local_u8RegisterBit);


	}
	else
	{
		Local_u8ErrorState =NOK ;
	}


	return Local_u8ErrorState ;

}

u8 NVIC_u8disablePendingFlag (u8 Copy_u8NameInterrupt)
{
	u8 Local_u8ErrorState = OK ;
	u8 Local_u8RegisterNum = 0 ;
	u8 Local_u8RegisterBit =0 ;
	if (Copy_u8NameInterrupt<60)
	{
		NVIC_u8GetRegisterBit(Copy_u8NameInterrupt,&Local_u8RegisterBit);
		NVIC_u8GetRegisterNumber(Copy_u8NameInterrupt,&Local_u8RegisterNum);
		SET_BIT(NVIC->ICPR[Local_u8RegisterNum],Local_u8RegisterBit);

	}
	else
	{
		Local_u8ErrorState =NOK ;
	}


	return Local_u8ErrorState ;

}

u8 NVIC_u8GetActiveFlage (u8 Copy_u8NameInterrupt , u8*Copy_u8ActiveFlagVal)
{
	u8 Local_u8ErrorState = OK ;
	u8 Local_u8RegisterNum = 0 ;
	u8 Local_u8RegisterBit =0 ;
	if (Copy_u8NameInterrupt<60)
	{
		NVIC_u8GetRegisterBit(Copy_u8NameInterrupt,&Local_u8RegisterBit);
		NVIC_u8GetRegisterNumber(Copy_u8NameInterrupt,&Local_u8RegisterNum);
		*Copy_u8ActiveFlagVal = GET_BIT(NVIC->IABR[Local_u8RegisterNum],Local_u8RegisterBit);

	}
	else
	{
		Local_u8ErrorState =NOK ;
	}


	return Local_u8ErrorState ;

}

u8 NVIC_u8SetPriority (u8 Copy_u8NameInterrupt , u8 Copy_u8NumbePriority)
{
	u8 Local_u8ErrorState = OK ;
	if (Copy_u8NameInterrupt<60)
	{
		NVIC->IPR[Copy_u8NameInterrupt] = Copy_u8NumbePriority ;

	}
	else
	{
		Local_u8ErrorState =NOK ;
	}


	return Local_u8ErrorState ;


}







