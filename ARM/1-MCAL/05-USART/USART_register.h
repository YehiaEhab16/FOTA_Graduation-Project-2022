/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):USART 			 ***********************/
/***********************   DATA : 09-04-2021 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/
 
#ifndef USART_REGISTER_H_
#define USART_REGISTER_H_


//USART Registers
typedef struct
{
	volatile u32    SR;
	volatile u32    DR;
	volatile u32    BRR;
	volatile u32    CR1;
	volatile u32    CR2;
	volatile u32    CR3;
	volatile u32    GRPR;
}USART_t;

//USART Base Addresses
#define USART1_BASE	    		((volatile USART_t*)0x40013800)
#define USART2_BASE	    		((volatile USART_t*)0x40004400)
#define USART3_BASE	   			((volatile USART_t*)0x40004800)


#endif