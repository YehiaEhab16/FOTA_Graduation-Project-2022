/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):EXTI 			 ***********************/
/***********************   DATA : 21-3-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include  "STD_TYPES.h"
#include  "BIT_MATH.h"
		  
#include  "EXTI_interface.h"
#include  "EXTI_config.h"
#include  "EXTI_private.h"


static void (* EXTI_CallBack) (void) = NULL ;

void EXTI_voidInit(void)
{
	#if		EXTI_LINE == EXTI_LINE0
			SET_BIT(EXTI_IMR , EXTI_LINE0 );
	#elif	EXTI_LINE == EXTI_LINE1
			SET_BIT(EXTI_IMR , EXTI_LINE1 );
	#elif	EXTI_LINE == EXTI_LINE2
			SET_BIT(EXTI_IMR , EXTI_LINE2 );
	#else
		#error ("Wrong Externl Interrupt Line !")
	#endif
	
	
	#if		EXTI_SENSE_MODE == FALLING_EDGE
			SET_BIT(EXTIvFTSR , EXTI_LINE);
	#elif	EXTI_SENSE_MODE == RISING_EDGE
			SET_BIT(EXTI_RTSR , EXTI_LINE);
	#elif	EXTI_SENSE_MODE == ON_CHANGE
			SET_BIT(EXTI_RTSR , EXTI_LINE);
			SET_BIT(EXTI_FTSR , EXTI_LINE);
	#else
		#error ("Wrong Externl Interrupt Sense Mode !")
	#endif
	
	
}

void EXTI_voidSetSignalLatch(u8 Copy_u8EXTILine , u8 Copy_u8EXTISenseMode)
{	
	switch(Copy_u8EXTISenseMode)
	{
		case	RISING_EDGE		:	SET_BIT(EXTI_RTSR , EXTI_LINE);	break;
		case	FALLING_EDGE	:	SET_BIT(EXTI_FTSR , EXTI_LINE);	break;
		case	ON_CHANGE		:	SET_BIT(EXTI_RTSR , EXTI_LINE);	
									SET_BIT(EXTI_FTSR , EXTI_LINE);	break;
	}
	SET_BIT(EXTI_IMR , Copy_u8EXTILine);
}

void EXTI_voidEnableEXTI(u8 Copy_u8EXTILine)
{
	SET_BIT(EXTI_IMR , Copy_u8EXTILine);
}

void EXTI_voidDisableEXTI(u8 Copy_u8EXTILine)
{
	CLR_BIT(EXTI_IMR , Copy_u8EXTILine);
	
}

void EXTI_voidSoftwareTrigger(u8 Copy_u8EXTILine)
{
	SET_BIT(EXTI_SWIER , Copy_u8EXTILine);
}

void EXTI_voidSetCallBack(void (*ptr) (void)) 
{
		EXTI_CallBack = ptr ; 
}

void	EXTI0_IRQHandler(void)
{
	EXTI_CallBack();
	/*	Clear pending Bit  */
	SET_BIT(EXTI_PR , 0);
	
}