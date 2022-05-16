/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):FPEC 			 ***********************/
/***********************   DATA : 7-3-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef FPEC_REGISTER_H_
#define FPEC_REGISTER_H_

//FPEC Registers
typedef struct
{
	volatile u32 FLASH_ACR;
	volatile u32 FLASH_KEYR;
	volatile u32 FLASH_OPTKE;
	volatile u32 FLASH_SR;
	volatile u32 FLASH_CR;
	volatile u32 FLASH_AR;
	volatile u32 RESERVED;
	volatile u32 FLASH_OBR;
	volatile u32 FLASH_WRPR;
}FPEC_t;

//FPEC Base Address
#define FPEC			((volatile FPEC_t*)0x40022000)


#endif
