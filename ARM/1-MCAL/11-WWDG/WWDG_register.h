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


typedef struct
{
	volatile u32 CR;	//Control Register
	volatile u32 CFR;	//Configuration register
	volatile u32 SR;	//Status Register
}WWDG_t;

#define WWDG					(*((volatile WWDG_t *)0x40002C00))

#define WWDG_CR_WDGA			7
#define WWDG_CR_T6				6
#define WWDG_CFR_WDGTB0			7
#define WWDG_CFR_WDGTB1			8
#define WWDG_CFR_EWI			9
#define WWDG_SR_EWIF			0

#endif
