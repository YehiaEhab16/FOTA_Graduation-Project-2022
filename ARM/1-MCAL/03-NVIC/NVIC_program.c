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

//Initialinzing NVIC 
void NVIC_voidInit(void)
{
	//Configuration Number of Groups and number of sub group
	SCB_AIRCR = (VETKEY)|(NVIC_GROUP<<8);
}

//Enabling Interrupt
u8 NVIC_u8EnableInterrupt(u8 Copy_u8NameInterrupt)
{
	u8 Local_u8ErrorState = OK;
	u8 Local_u8RegisterNum = 0;
	u8 Local_u8RegisterBit = 0;
	if (Copy_u8NameInterrupt<NVIC_MAX_INTERRUPT)	//Input Validation
	{
		NVIC_u8GetRegisterBit(Copy_u8NameInterrupt,&Local_u8RegisterBit);
		NVIC_u8GetRegisterNumber(Copy_u8NameInterrupt,&Local_u8RegisterNum);
		SET_BIT(NVIC ->ISER[Local_u8RegisterNum],Local_u8RegisterBit);
	}
	//Wrong Input
	else
		Local_u8ErrorState = NOK;
	
	return Local_u8ErrorState;
}

//Disabling Interrupt
u8 NVIC_u8DisableInterrupt(u8 Copy_u8NameInterrupt)
{
	u8 Local_u8ErrorState = OK;
	u8 Local_u8RegisterNum = 0;
	u8 Local_u8RegisterBit = 0;
	if (Copy_u8NameInterrupt<NVIC_MAX_INTERRUPT)	//Input Validation
	{
		NVIC_u8GetRegisterBit(Copy_u8NameInterrupt,&Local_u8RegisterBit);
		NVIC_u8GetRegisterNumber(Copy_u8NameInterrupt,&Local_u8RegisterNum);
		SET_BIT(NVIC->ICER[Local_u8RegisterNum],Local_u8RegisterBit);
	}
	//Wrong Input
	else
		Local_u8ErrorState = NOK;

	return Local_u8ErrorState;

}

//Enabling Pending Flag
u8 NVIC_u8EnablePendingFlag(u8 Copy_u8NameInterrupt)
{
	u8 Local_u8ErrorState = OK;
	u8 Local_u8RegisterNum = 0;
	u8 Local_u8RegisterBit = 0;
	if (Copy_u8NameInterrupt<NVIC_MAX_INTERRUPT)	//Input Validation
	{
		NVIC_u8GetRegisterBit(Copy_u8NameInterrupt,&Local_u8RegisterBit);
		NVIC_u8GetRegisterNumber(Copy_u8NameInterrupt,&Local_u8RegisterNum);
		SET_BIT(NVIC->ISPR[Local_u8RegisterNum],Local_u8RegisterBit);
	}
	//Wrong Input
	else
		Local_u8ErrorState = NOK;
	
	return Local_u8ErrorState;
}

//Disabling Pending Flag
u8 NVIC_u8DisablePendingFlag(u8 Copy_u8NameInterrupt)
{
	u8 Local_u8ErrorState = OK;
	u8 Local_u8RegisterNum = 0;
	u8 Local_u8RegisterBit = 0;
	if (Copy_u8NameInterrupt<NVIC_MAX_INTERRUPT)	//Input Validation
	{
		NVIC_u8GetRegisterBit(Copy_u8NameInterrupt,&Local_u8RegisterBit);
		NVIC_u8GetRegisterNumber(Copy_u8NameInterrupt,&Local_u8RegisterNum);
		SET_BIT(NVIC->ICPR[Local_u8RegisterNum],Local_u8RegisterBit);
	}
	//Wrong Input
	else
		Local_u8ErrorState = NOK;
	
	return Local_u8ErrorState;

}

//Getting Active Flag
u8 NVIC_u8GetActiveFlag(u8 Copy_u8NameInterrupt , u8 *Copy_u8ActiveFlagVal)
{
	u8 Local_u8ErrorState = OK;
	u8 Local_u8RegisterNum = 0;
	u8 Local_u8RegisterBit = 0;
	if (Copy_u8NameInterrupt<NVIC_MAX_INTERRUPT)	//Input Validation
	{
		NVIC_u8GetRegisterBit(Copy_u8NameInterrupt,&Local_u8RegisterBit);
		NVIC_u8GetRegisterNumber(Copy_u8NameInterrupt,&Local_u8RegisterNum);
		*Copy_u8ActiveFlagVal = GET_BIT(NVIC->IABR[Local_u8RegisterNum],Local_u8RegisterBit);
	}	
	//Wrong Input
	else
		Local_u8ErrorState = NOK;
	
	return Local_u8ErrorState;
}

//Setting Interrupt Priority
u8 NVIC_u8SetPriority(u8 Copy_u8NameInterrupt , u8 Copy_u8Priority)
{
	u8 Local_u8ErrorState = OK ;
	if (Copy_u8NameInterrupt<NVIC_MAX_INTERRUPT)	//Input Validation
		NVIC->IPR[Copy_u8NameInterrupt] = Copy_u8Priority;
	//Wrong Input
	else
		Local_u8ErrorState = NOK;
	
	return Local_u8ErrorState;
}

//Getting Register Number
u8 NVIC_u8GetRegisterNumber(u8 Copy_u8NameInterrupt,u8 *Copy_u8RegisterNumberVal)
{
	u8 Local_u8ErrorState = OK ;
	if (Copy_u8NameInterrupt<NVIC_MAX_INTERRUPT)	//Input Validation
		*Copy_u8RegisterNumberVal = (u8)(Copy_u8NameInterrupt/32);
	//Wrong Input
	else
		Local_u8ErrorState = NOK;

	return Local_u8ErrorState;
}

//Getting Register Bit
u8 NVIC_u8GetRegisterBit(u8 Copy_u8NameInterrupt,u8 *Copy_u8RegisterBitVal )
{
	u8 Local_u8ErrorState = OK ;
	if (Copy_u8NameInterrupt<NVIC_MAX_INTERRUPT)	//Input Validation
		*Copy_u8RegisterBitVal =Copy_u8NameInterrupt-(32*((u8)(Copy_u8NameInterrupt/32)));
	//Wrong Input
	else
		Local_u8ErrorState = NOK;

	return Local_u8ErrorState;
}