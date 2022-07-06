/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):EXTI 			 ***********************/
/***********************   DATA : 21-3-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef EXTI_REGISTER_H
#define EXTI_REGISTER_H


//EXTI Registers
typedef struct
{
	volatile u32 IMR;	
	volatile u32 EMR;	
	volatile u32 RTSR;	
	volatile u32 FTSR;	
	volatile u32 SWIER;	
	volatile u32 PR;
}EXTI_t;

//EXTI Base Address
#define EXTI				((volatile EXTI_t*)0x40010400)


#endif
