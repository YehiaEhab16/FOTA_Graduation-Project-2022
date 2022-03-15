/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer : MCAL                  ***********************/
/***********************   SWC (DRIVER):WWDG			 ***********************/
/***********************   DATA : 15-3-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef WWDG_REGISTER_H_
#define WWDG_REGISTER_H_


#define WWDG_CR					(*((volatile u32 *)0x40002C00))	//Control Register
#define WWDG_CFR				(*((volatile u32 *)0x40002C04))	//Configuration register
#define WWDG_SR					(*((volatile u32 *)0x40002C08))	//Status Register

#define WWDG_CR_WDGA			7
#define WWDG_CR_T6				6
#define WWDG_CFR_WDGTB0			7
#define WWDG_CFR_WDGTB1			8
#define WWDG_CFR_EWI			9
#define WWDG_SR_EWIF			0

#endif
