/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):Dec 22, 2021	 ***********************/
/***********************   DATA : 15-11-2021 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/


#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

#include "STD_TYPES.h"

typedef struct
{
	u16 Prescaler;
	u16 Period;
	u8 Period_Mode;					/* PERIODIC_MODE or ONE_PULSE_MODE */
	u8 Direction;					/* UP_COUNT or DOWN_COUNT */
	u8 Clock_Div;					/* DIV_1, DIV_2 or DIV_3 */
	u8 Center_Aligned_Mode;			/* EDGE_ALIGNED_MODE, CENTER_ALIGNED_MODE_(1,2 OR 3)*/
	u8 Update_State;	            /* ENABLE or DISABLE */
	u8 AutoReloadBuffer;            /* ENABLE or DISABLE */
	u8 Counter_State;               /* ENABLE or DISABLE */
	u8 UDI_State;                   /* ENABLE or DISABLE */
}GPT_Config;



#endif
