/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer : MCAL                  ***********************/
/***********************   SWC (DRIVER):IWDG			 ***********************/
/***********************   DATA : 15-3-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef IWDG_REGISTER_H_
#define IWDG_REGISTER_H_


#define IWDG_KR					(*((volatile u32 *)0x40003000))	//Key Register
#define IWDG_PR					(*((volatile u32 *)0x40003004))	//Prescalar Register
#define IWDG_RLR				(*((volatile u32 *)0x40003008))	//Reload Register
#define IWDG_SR					(*((volatile u32 *)0x4000300C))	//Status Register

#define IWDG_SR_PVU				0	//Watchdog prescaler value update
#define IWDG_SR_RVU				1	//Watchdog counter reload value update


#endif
