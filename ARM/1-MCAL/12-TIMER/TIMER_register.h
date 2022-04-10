/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):TIMER			 ***********************/
/***********************   DATA : 11-04-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef TIMER_REGISTER_H_
#define TIMER_REGISTER_H_


//Timer Registers
typedef struct
{
  volatile u32 CR[2];				//Control Registers 1 & 2
  volatile u32 SMCR;                //slave mode control register
  volatile u32 DIER;                //DMA/Interrupt enable register
  volatile u32 SR;                  //status register
  volatile u32 EGR;                 //event generation register
  volatile u32 CCMR[2];             //capture/compare mode registers 1 & 2
  volatile u32 CCER;                //capture/compare enable register
  volatile u32 CNT;                 //Counter
  volatile u32 PSC;                 //Prescaler
  volatile u32 ARR;                 //auto-reload register __ Address offset: 0x2C
  u32 RESERVED1;                     
  volatile u32 CCR[4];              //capture/compare registers 1, 2, 3 & 4 __ Address offset: 0x34
  volatile u32 BDTR;				// break and dead-time register for TIM1 ONLY __ Address offset: 0x44
  volatile u32 DCR;                 //DMA control register__ Address offset: 0x48
  volatile u32 DMAR;                //DMA address for full transfer
}TIMER_t;

//Timer Base Addresses
#define TIM1_BASE					(*((volatile TIMER_t *)0x40012C00))
#define TIM2_BASE					(*((volatile TIMER_t *)0x40000000))
#define TIM3_BASE					(*((volatile TIMER_t *)0x40000400))
#define TIM4_BASE					(*((volatile TIMER_t *)0x40000800))


#endif
