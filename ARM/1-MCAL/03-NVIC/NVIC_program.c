/**********************************************************/
/* GRADUATION PROJECT : (FOTA)							  */
/* Version   : V01                                        */
/**********************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "NVIC_interface.h"
#include "NVIC_private.h"
#include "NVIC_config.h"


u8 NVIC_voidEnableInterrupt (u8 Copy_u8IntNumber)
{
	u8 ErrorStatus;
	
	if ( Copy_u8IntNumber <= 31 )
	{
		NVIC_ISER0 = (1 << Copy_u8IntNumber);
		ErrorStatus = 0;
	}
	 
	else if ( Copy_u8IntNumber <= 59 )
	{
		Copy_u8IntNumber -= 32; 
		NVIC_ISER1 = (1 << Copy_u8IntNumber);
		ErrorStatus = 0;
	}
	
	else
	{
		ErrorStatus = 1;
	}
	
	return ErrorStatus;
}


u8 NVIC_voidDisableInterrupt (u8 Copy_u8IntNumber)
{
	u8 ErrorStatus;
	if ( Copy_u8IntNumber <= 31 )
	{
		NVIC_ICER0 = (1 << Copy_u8IntNumber);
		ErrorStatus = 0;
	}
	
	else if ( Copy_u8IntNumber <= 59 )
	{
		Copy_u8IntNumber -= 32;
		NVIC_ICER1 = (1 << Copy_u8IntNumber);
		ErrorStatus = 0;
	}
	
	else
	{
		ErrorStatus = 1;
	}
	
	return ErrorStatus;
}


u8 NVIC_voidSetPendingFlag(u8 Copy_u8IntNumber)
{
	u8 ErrorStatus;
	if ( Copy_u8IntNumber <= 31 )
	{
		NVIC_ISPR0 = (1 << Copy_u8IntNumber);
		ErrorStatus = 0;
	}
	
	else if ( Copy_u8IntNumber <= 59 )
	{
		Copy_u8IntNumber -= 32;
		NVIC_ISPR1 = (1 << Copy_u8IntNumber);
		ErrorStatus = 0;
	}
	
	else
	{
		ErrorStatus = 1;
	}
	
	return ErrorStatus;
}


u8 NVIC_voidClearPendingFlag(u8 Copy_u8IntNumber)
{
	u8 ErrorStatus;
	if ( Copy_u8IntNumber <= 31)
	{
		NVIC_ICPR0 = (1 << Copy_u8IntNumber);
		ErrorStatus = 0;
	}
	
	else if (  Copy_u8IntNumber <= 59)
	{
		Copy_u8IntNumber -= 32;
		NVIC_ICPR1 = (1 << Copy_u8IntNumber);
		ErrorStatus = 0;
	}
	
	else
	{
		ErrorStatus = 1;
	}
	
	return ErrorStatus;
	
}


u8 NVIC_u8GetActiveFlag(u8 Copy_u8IntNumber)
{
	u8 Local_u8Result;
	
	if ( Copy_u8IntNumber <= 31)
	{
		Local_u8Result = GET_BIT(NVIC_IABR0,Copy_u8IntNumber);
	}
	
	else if (  Copy_u8IntNumber <= 59)
	{
		Copy_u8IntNumber -= 32;
		Local_u8Result = GET_BIT(NVIC_IABR1,Copy_u8IntNumber);
	}
	
	else
	{
		/* Return Error */
	}
	
	return Local_u8Result;
	
}

void NVIC_VidSetPriority( s8 Copy_u8INTID , u8 Copy_u8GroupPriority , u8 Copy_u8SubPriority , u32 Copy_u8Group )
{
	u8 Priority =  Copy_u8SubPriority | Copy_u8GroupPriority << ( (Copy_u8Group - 0x05FA0300) / 256 )  ;
	//Core Peripheral
	if( Copy_u8INTID < 0  ){

		if( Copy_u8INTID == MEMORY_MANAGE || Copy_u8INTID == BUS_FAULT || Copy_u8INTID == USAGE_FAULT ){

			Copy_u8INTID += 3;
			SCB->SHPR1 = ( Priority ) << ( (8 * Copy_u8INTID) + 4 );

		}
		else if ( Copy_u8INTID == SV_CALL ){

			Copy_u8INTID += 7;
			SCB->SHPR2 = ( Priority ) << ( (8 * Copy_u8INTID) + 4 );

		}
		else if( Copy_u8INTID == PEND_SV || Copy_u8INTID == SYSTICK ){

			Copy_u8INTID += 8;

			SCB->SHPR3 = ( Priority ) << ( (8 * Copy_u8INTID) + 4 );

		}

	}
    //External Peripheral
	else if( Copy_u8INTID >= 0 ){

		MNVIC->IPR[ Copy_u8INTID ] = Priority << 4 ;

	}

	SCB_AIRCR = Copy_u32Group ;
}


