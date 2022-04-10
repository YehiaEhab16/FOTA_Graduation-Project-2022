/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):RCC 			 ***********************/
/***********************   DATA : 21-3-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/
#ifndef RCC_REGISTER_H_
#define RCC_REGISTER_H_

//RCC Registers
typedef struct
{
	volatile u32 CR;
	volatile u32 CFGR;
	volatile u32 CIR;   
	volatile u32 APB2RSTR;
	volatile u32 APB1RSTR;
	volatile u32 AHBENR;
	volatile u32 APB2ENR; 
	volatile u32 APB1ENR;	
	volatile u32 BDCR;
	volatile u32 CSR; 
}RCC_t;

//RCC Base Address
#define RCC		     (*(volatile RCC_t*)0x40021000)

//Control Register Pins
#define RCC_CR_HSI				0
#define RCC_CR_HSE		 		16
#define RCC_CR_PLL				24


#endif
