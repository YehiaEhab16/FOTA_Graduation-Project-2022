/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):NVIC 			 ***********************/
/***********************   DATA : 2-4-2022 			 ***********************/
/*******************************************************************************/


#ifndef NVIC_REGISTER_H_
#define NVIC_REGISTER_H_

//NVIC Registers
typedef struct
{
	volatile u32 ISER[3];
	volatile u32 EXTRA_BYTE[29];
	volatile u32 ICER[3];
	volatile u32 EXTRA_BYTE1[2];
	volatile u32 ISPR[3];
	volatile u32 EXTRA_BYTE2[29];
	volatile u32 ICPR[3];
	volatile u32 EXTRA_BYTE3[29];
	volatile u32 IABR[3];
	volatile u32 EXTRA_BYTE4[29];
	volatile u8  IPR[59];
}NVIC_t;

//NVIC Base Address
#define NVIC 	((volatile NVIC_t*) 0xE000E100)

//Register that control Type of interrupt Grouping
#define  SCB_AIRCR *((volatile u32 *)  0xE000E008 +0x0C)





#endif
