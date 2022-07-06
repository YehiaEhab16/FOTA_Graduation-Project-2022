/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer : MCAL                  ***********************/
/***********************   SWC (DRIVER):IWDG			 ***********************/
/***********************   DATA : 15-3-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef IWDG_INTERFACE_H_
#define IWDG_INTERFACE_H_


//Prescalar Configurations
#define IWDG_DIVIDE_BY_4			0
#define IWDG_DIVIDE_BY_8			1
#define IWDG_DIVIDE_BY_16			2
#define IWDG_DIVIDE_BY_32			3
#define IWDG_DIVIDE_BY_64			4
#define IWDG_DIVIDE_BY_128			5
#define IWDG_DIVIDE_BY_256			6

/**
 * @def reset controller
 * @param Copy_u16TimeoutValue Countdown value
 */
void IWDG_voidReset(u16 Copy_u16TimeoutValue);


#endif
