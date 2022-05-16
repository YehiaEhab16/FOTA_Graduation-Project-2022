/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):GPIO 			 ***********************/
/***********************   DATA : 15-11-2021 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef GPIO_REGISTER_H_
#define GPIO_REGISTER_H_


//GPIO Registers
typedef struct
{
	volatile u32 CRL;
	volatile u32 CRH;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 BRR;
	volatile u32 LCKR;
}GPIO_t;

//GPIO Base Addresses
#define GPIOA					((volatile GPIO_t*)0x40010800)
#define GPIOB					((volatile GPIO_t*)0x40010C00)
#define GPIOC					((volatile GPIO_t*)0x40011000)


#endif
