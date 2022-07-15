/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :SERVICE                ***********************/
/***********************   SWC (DRIVER):ICU 			 ***********************/
/***********************   DATE : 15-7-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../../6-Library/STD_TYPES.h"

#include "../../1-MCAL/12-TIMER/TIMER_interface.h"
#include "../../1-MCAL/04-EXTI/EXTI_interface.h"

#include "../09-ICU/ICU_config.h"
#include "../09-ICU/ICU_interface.h"
#include "../09-ICU/ICU_private.h"

u16 Capture_u16Value =0 ;

volatile u8 Global_u8Counter =0 ;


void ICU_voidInit (void)
{

	GPT_Config ICU_TIM1 = {8 ,100,ONE_PULSE_MODE, UP_COUNT , DIV_1, EDGE_ALIGNED_MODE  ,TIM_ENABLE ,TIM_ENABLE,TIM_ENABLE, TIM_ENABLE};
	TIMER_voidTimerConfig (TIM1,&ICU_TIM1);

}

void ICU_voidGetCaptureValue (void)
{
	if (Global_u8Counter == 0 )
	{
		TIMER_StartTimer(TIM1);
		EXTI_voidSetSenseMode(ICU_EXTI,EXTI_FALLING_EDGE);
		Global_u8Counter =1 ;
	}
	else
	{
		Capture_u16Value = TIMER_u16GetCount(TIM1);
		TIMER_StopTimer(TIM1);
		EXTI_voidSetSenseMode(ICU_EXTI,EXTI_RISING_EDGE);
		Global_u8Counter =0 ;
	}




}

