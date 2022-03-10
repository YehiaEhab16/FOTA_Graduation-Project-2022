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



#define PORTA_ODR					(*((volatile u32 *)0x4001080c))
#define PORTB_ODR					(*((volatile u32 *)0x40010c0c))
#define PORTC_ODR					(*((volatile u32 *)0x4001100c))
		
#define DDRA_CRL					(*((volatile u32 *)0x40010800))
#define DDRA_CRH					(*((volatile u32 *)0x40010804))
			
#define DDRB_CRL					(*((volatile u32 *)0x40010c00))
#define DDRB_CRH					(*((volatile u32 *)0x40010c04))
			
#define DDRC_CRH					(*((volatile u32 *)0x40011004))

#define PORTA_IDR					(*((volatile u32 *)0x40010808))
#define PORTB_IDR					(*((volatile u32 *)0x40010C08))
#define PORTC_IDR					(*((volatile u32 *)0x40011008))



#endif
