/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):EXTI 			 ***********************/
/***********************   DATA : 21-3-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../../6-Library/STD_TYPES.h"
#include "../../6-Library/BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_config.h"
#include "EXTI_private.h"
#include "EXTI_register.h"

//ISR function prototype
static void (* EXTI_CallBack) (void) = NULL;

//Initializing EXTI 
void EXTI_voidInit(void)
{
	#if		EXTI_LINE == EXTI_LINE0
			SET_BIT(EXTI->IMR , EXTI_LINE0 );
	#elif	EXTI_LINE == EXTI_LINE1
			SET_BIT(EXTI->IMR , EXTI_LINE1 );
	#elif	EXTI_LINE == EXTI_LINE2
			SET_BIT(EXTI->IMR , EXTI_LINE2 );
	#else
		#error ("Wrong Externl Interrupt Line !")	//Input Validation
	#endif
	
	
	#if		EXTI_SENSE_MODE == FALLING_EDGE
			SET_BIT(EXTI->FTSR , EXTI_LINE);
	#elif	EXTI_SENSE_MODE == RISING_EDGE
			SET_BIT(EXTI->RTSR , EXTI_LINE);
	#elif	EXTI_SENSE_MODE == ON_CHANGE
			SET_BIT(EXTI->RTSR , EXTI_LINE);
			SET_BIT(EXTI->FTSR , EXTI_LINE);
	#else
		#error ("Wrong Externl Interrupt Sense Mode !")	//Input Validation
	#endif
	
	
}

//Setting EXTI Sense Mode
void EXTI_voidSetSignalLatch(u8 Copy_u8EXTILine , u8 Copy_u8EXTISenseMode)
{	
	switch(Copy_u8EXTISenseMode)
	{
		case	RISING_EDGE		:	SET_BIT(EXTI->RTSR , EXTI_LINE);	break;
		case	FALLING_EDGE	:	SET_BIT(EXTI->FTSR , EXTI_LINE);	break;
		case	ON_CHANGE		:	SET_BIT(EXTI->RTSR , EXTI_LINE);	
									SET_BIT(EXTI->FTSR , EXTI_LINE);	break;
	}
	SET_BIT(EXTI->IMR , Copy_u8EXTILine);
}

//Enabling EXTI 
void EXTI_voidEnableEXTI(u8 Copy_u8EXTILine)
{
	SET_BIT(EXTI->IMR , Copy_u8EXTILine);
}

//Disabling EXTI 
void EXTI_voidDisableEXTI(u8 Copy_u8EXTILine)
{
	CLR_BIT(EXTI->IMR , Copy_u8EXTILine);
}

//Setting Software Trigger for EXTI
void EXTI_voidSoftwareTrigger(u8 Copy_u8EXTILine)
{
	SET_BIT(EXTI->SWIER , Copy_u8EXTILine);
}

//Setting Callback function
void EXTI_voidSetCallBack(void (*Copy_pvCallBackFunc) (void)) 
{
	EXTI_CallBack = Copy_pvCallBackFunc ; 
}

void EXTI0_IRQHandler(void)
{
	EXTI_CallBack();
	/*	Clear pending Bit  */
	SET_BIT(EXTI->PR, 0);
	
}