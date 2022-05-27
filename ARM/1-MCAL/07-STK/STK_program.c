/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):STK 			 ***********************/
/***********************   DATA : 3-3-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../../6-Library/STD_TYPES.h"
#include "../../6-Library/BIT_MATH.h"

#include "STK_interface.h"
#include "STK_config.h"
#include "STK_private.h"
#include "STK_register.h"

//ISR Func
static void (*STK_voidCallBackFunc)(void)=NULL ;

static u32 STK_u32_MODE = STK_SINGLE_MODE ;

//Initializing STK
void STK_voidInit(void) 						
{
	#if SLK_CLOCK_PRE == AHB_CLOCK_SOURCE
	STK->CTRL = 0x00000004;
	#elif SLK_CLOCK_PRE == AHB_8_CLOCK_SOURCE
	STK->CTRL = 0x00000000;
	#else
	#error "Please enter the correct Prescaler"	//Wrong Input
	#endif
}

//Enabling Timer
void STK_voidEnableTimer (void)
{
	SET_BIT(STK->CTRL, EN_ABLE) ;
}

//Disabling Timer
void STK_voidDisableTimer (void)
{
	CLR_BIT(STK->CTRL, EN_ABLE) ;
	STK->LOAD = 0;
	STK->VAL =  0;
}

//Delay Function
void STK_voidDelay(u32 Copy_u8TimeMilleSecond)
{
	u32 Local_u8LoadVal ;
	Local_u8LoadVal= Copy_u8TimeMilleSecond*1000;
	//Set the value in Load Register
	STK->LOAD = Local_u8LoadVal;
	//Initial Value Register =0
	STK->VAL =0 ;
	//Start The Time
	SET_BIT(STK->CTRL, EN_ABLE) ;

	while(GET_BIT(STK->CTRL,COUNT_FLAG)==0);

	/*Disable the Timer*/
	CLR_BIT(STK->CTRL, EN_ABLE) ;
	STK->LOAD = 0;
	STK->VAL =  0;
}

//Asynchronous Delay (Single)
u8 STK_u8DelayAsySingle (u32 Copy_u32TimeMilleSecond , void(*Copy_pvNotifi)(void))
{
	u8 Local_u8ErrorState = OK ;
	if (Copy_pvNotifi != NULL)
	{
		u32 Local_u32LoadVal;
		Local_u32LoadVal= Copy_u32TimeMilleSecond*1000;
		/*Set the value in Load Register */
		STK->LOAD = Local_u32LoadVal;
		/*Initial Value Register =0 */
		STK->VAL =0 ;
		/*Start The Time */
		SET_BIT(STK->CTRL, EN_ABLE) ;
		/*Set call back function */
		STK_voidCallBackFunc = Copy_pvNotifi ;
		/*Set mode of Single */
		STK_u32_MODE = STK_SINGLE_MODE;
		/*Set the Interrupt */
		SET_BIT(STK->CTRL,TICK_INT);
	}
	else
		Local_u8ErrorState = NOK ;

	return Local_u8ErrorState;
}

//Asynchronous Delay (Periodic)
u8 STK_u8DelayAsyPeriodic (u32 Copy_u32TimeMilleSecond , void(*Copy_pvNotifi)(void))
{
	u8 Local_u8ErrorState = OK ;
	if (Copy_pvNotifi != NULL)
	{
		u32 Local_u32LoadVal ;
		Local_u32LoadVal= Copy_u32TimeMilleSecond*1000;
		/*Set the value in Load Register */
		STK->LOAD = Local_u32LoadVal;
		/*Initial Value Register =0 */
		STK->VAL =0 ;
		/*Start The Time */
		SET_BIT(STK->CTRL, EN_ABLE) ;
		/*Set call back function */
		STK_voidCallBackFunc = Copy_pvNotifi ;
		/*Set mode of Periodic */
		STK_u32_MODE = STK_PERIODIC_MODE;
		/*Set the Interrupt */
		SET_BIT(STK->CTRL,TICK_INT);
	}
	
	else
		Local_u8ErrorState = NOK ;
	
	return Local_u8ErrorState;
}

//Calculate Time
u8 STK_u8GetTime(void)
{
	u32 Local_u8Time ;
	Local_u8Time= (STK->LOAD) - (STK->VAL) ;
	Local_u8Time = (u32)(Local_u8Time/1000);
	return Local_u8Time ;
}

//Calculate Remaining Time
u8 STK_u8GetRemainigTime(void)
{
	u32 Local_u8Time ;
	Local_u8Time=(STK->VAL) ;
	Local_u8Time = (u32)(Local_u8Time/1000);
	return Local_u8Time ;

}

//STK ISR
void SysTick_Handler (void)
{
	u8 Local_u8Val = 0 ;
	
	if (STK_u32_MODE == STK_SINGLE_MODE)
	{
		/*Disable the Timer*/
		CLR_BIT(STK->CTRL, EN_ABLE) ;
		STK->LOAD = 0;
		STK->VAL =  0;
	}
	
	STK_voidCallBackFunc();

	Local_u8Val=GET_BIT(STK->CTRL,COUNT_FLAG);
}
