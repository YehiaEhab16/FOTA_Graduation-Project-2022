/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):EXTI 			 ***********************/
/***********************   DATA : 21-3-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include  "../../6-Library/STD_TYPES.h"
#include  "../../6-Library/BIT_MATH.h"
		  
#include  "EXTI_interface.h"
#include  "EXTI_config.h"
#include  "EXTI_private.h"
#include  "EXTI_register.h"

//ISR function prototype
static void (* EXTI_CallBack[5]) (void) = {NULL};

//Initializing EXTI 
void EXTI_voidInit(u8 Copy_u8InterruptLine, u8 Copy_u8SenseMode)
{
	if(Copy_u8InterruptLine>=EXTI_LINE0 && Copy_u8InterruptLine<=EXTI_LINE4)
	{
		SET_BIT(EXTI->IMR,  Copy_u8InterruptLine);
		switch(Copy_u8SenseMode)
		{
			case	EXTI_RISING_EDGE	:	SET_BIT(EXTI->RTSR , Copy_u8InterruptLine);	break;
			case	EXTI_FALLING_EDGE	:	SET_BIT(EXTI->FTSR , Copy_u8InterruptLine);	break;
			case	EXTI_ON_CHANGE		:	SET_BIT(EXTI->RTSR , Copy_u8InterruptLine);	
											SET_BIT(EXTI->FTSR , Copy_u8InterruptLine);	break;
		}
	}
}
//Setting EXTI Sense Mode
void EXTI_voidSetSenseMode(u8 Copy_u8InterruptLine , u8 Copy_u8EXTISenseMode)
{	
	switch(Copy_u8EXTISenseMode)
	{
		case	EXTI_RISING_EDGE	:	SET_BIT(EXTI->RTSR , Copy_u8InterruptLine);	break;
		case	EXTI_FALLING_EDGE	:	SET_BIT(EXTI->FTSR , Copy_u8InterruptLine);	break;
		case	EXTI_ON_CHANGE		:	SET_BIT(EXTI->RTSR , Copy_u8InterruptLine);	
										SET_BIT(EXTI->FTSR , Copy_u8InterruptLine);	break;
	}
}

//Enabling EXTI 
void EXTI_voidEnableEXTI(u8 Copy_u8InterruptLine)
{
	SET_BIT(EXTI->IMR , Copy_u8InterruptLine);
}

//Disabling EXTI 
void EXTI_voidDisableEXTI(u8 Copy_u8InterruptLine)
{
	CLR_BIT(EXTI->IMR , Copy_u8InterruptLine);
}

//Setting Software Trigger for EXTI
void EXTI_voidSoftwareTrigger(u8 Copy_u8InterruptLine)
{
	SET_BIT(EXTI->SWIER , Copy_u8InterruptLine);
}

//Setting Callback function
void EXTI_voidSetCallBack(u8 Copy_u8InterruptLine,void (*Copy_pvCallBackFunc) (void)) 
{
	EXTI_CallBack[Copy_u8InterruptLine] = Copy_pvCallBackFunc; 
}

void EXTI0_IRQHandler(void)
{
	EXTI_CallBack[EXTI_LINE0]();
	/*	Clear pending Bit  */
	SET_BIT(EXTI->PR, EXTI_LINE0);
}

void EXTI1_IRQHandler(void)
{
	EXTI_CallBack[EXTI_LINE1]();
	/*	Clear pending Bit  */
	SET_BIT(EXTI->PR, EXTI_LINE1);
}

void EXTI2_IRQHandler(void)
{
	EXTI_CallBack[EXTI_LINE2]();
	/*	Clear pending Bit  */
	SET_BIT(EXTI->PR, EXTI_LINE2);
}

void EXTI3_IRQHandler(void)
{
	EXTI_CallBack[EXTI_LINE3]();
	/*	Clear pending Bit  */
	SET_BIT(EXTI->PR, EXTI_LINE3);
}

void EXTI4_IRQHandler(void)
{
	EXTI_CallBack[EXTI_LINE4]();
	/*	Clear pending Bit  */
	SET_BIT(EXTI->PR, EXTI_LINE4);
}
