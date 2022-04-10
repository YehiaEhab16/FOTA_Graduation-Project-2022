/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):STK 			 ***********************/
/***********************   DATA : 3-3-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef STK_PRIVATE_H_
#define STK_PRIVATE_H_

/*
Prescaller Options:
	-AHB_CLOCK_SOURCE : Divided by one
	-AHB_8_CLOCK_SOURCE Divided by Eight
*/
#define AHB_CLOCK_SOURCE 		0
#define AHB_8_CLOCK_SOURCE 		1

//Pins of STK_CTRL Register
#define COUNT_FLAG				16
#define CLKSO_URCE				2
#define TICK_INT				1
#define EN_ABLE					0


//Periodic or Single SoftWare Flag
#define	STK_SINGLE_MODE			0
#define STK_PERIODIC_MODE		1


#endif
