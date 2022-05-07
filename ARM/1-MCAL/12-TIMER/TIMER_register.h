/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):Dec 22, 2021	 ***********************/
/***********************   DATA : 15-11-2021 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef TIMER_REG_H_
#define TIMER_REG_H_

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

#define TIM1_BASE		0x40012C00u
#define TIM2_BASE		0x40000000u
#define TIM3_BASE		0x40000400u
#define TIM4_BASE		0x40000800u



#endif
