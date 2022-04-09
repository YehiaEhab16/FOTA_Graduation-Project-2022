/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):Dec 22, 2021	 ***********************/
/***********************   DATA : 15-11-2021 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/


#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

#include "STD_TYPES.h"

typedef struct
{
  volatile u32 CR[2];				/*Control Registers 1 & 2*/
  volatile u32 SMCR;                /*slave mode control register*/
  volatile u32 DIER;                /*DMA/Interrupt enable register*/
  volatile u32 SR;                  /*status register*/
  volatile u32 EGR;                 /*event generation register*/
  volatile u32 CCMR[2];             /*capture/compare mode registers 1 & 2*/
  volatile u32 CCER;                /*capture/compare enable register*/
  volatile u32 CNT;                 /*Counter*/
  volatile u32 PSC;                 /*Prescaler*/
  volatile u32 ARR;                 /*auto-reload register __ Address offset: 0x2C*/
  u32 RESERVED1;
  volatile u32 CCR[4];              /*capture/compare registers 1, 2, 3 & 4 __ Address offset: 0x34*/
  volatile u32 BDTR;				/* break and dead-time register for TIM1 ONLY __ Address offset: 0x44*/
  volatile u32 DCR;                 /*DMA control register__ Address offset: 0x48*/
  volatile u32 DMAR;                /*DMA address for full transfer*/
} TIMER_t;

typedef struct
{
	u8 timer;
	u8 channel;
}TIM_CH_t;

static TIM_CH_t* GET_TIM_CH(u8 Port_Pin)
{
	TIM_CH_t *TIM_CH;
	if(Port_Pin<4)
	{
		TIM_CH->timer = 1;
		TIM_CH->channel = Port_Pin+1;
	}
	else if(Port_Pin<8)
	{
		TIM_CH->timer = 2;
		TIM_CH->channel = Port_Pin-3;
	}
	else if(Port_Pin<12)
	{
		TIM_CH->timer = 3;
		TIM_CH->channel = Port_Pin-7;
	}

	return TIM_CH;
}

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
