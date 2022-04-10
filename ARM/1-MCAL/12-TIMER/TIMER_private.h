/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):TIMER			 ***********************/
/***********************   DATA : 11-04-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/
#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_


typedef struct
{
	u8 timer;
	u8 channel;
}TIM_CH_t;

#define 	TIM2_CH1      GET_TIM_CH(0)
#define 	TIM2_CH2      GET_TIM_CH(1)
#define 	TIM2_CH3      GET_TIM_CH(2)
#define 	TIM2_CH4      GET_TIM_CH(3)
#define 	TIM3_CH1      GET_TIM_CH(4)
#define 	TIM3_CH2      GET_TIM_CH(5)
#define 	TIM3_CH3      GET_TIM_CH(6)
#define 	TIM3_CH4      GET_TIM_CH(7)
#define 	TIM1_CH1      GET_TIM_CH(8)
#define 	TIM1_CH2      GET_TIM_CH(9)
#define 	TIM1_CH3      GET_TIM_CH(10)
#define 	TIM1_CH4      GET_TIM_CH(11)


#endif
