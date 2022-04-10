/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer : MCAL                  ***********************/
/***********************   SWC (DRIVER):WWDG			 ***********************/
/***********************   DATA : 15-3-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef WWDG_CONFIG_H_
#define WWDG_CONFIG_H_


/*
Prescalar Options:
	-IWDG_DIVIDE_BY_1
	-IWDG_DIVIDE_BY_2	
	-IWDG_DIVIDE_BY_4
	-IWDG_DIVIDE_BY_8
*/
#define WWDG_PRESCALAR_VALUE			WWDG_DIVIDE_BY_1

//Select 0 for no interrupts and 1 if an interrupt is needed before reset
#define WWDG_EARLY_WAKEUP_INTERRUPT		0


#endif
