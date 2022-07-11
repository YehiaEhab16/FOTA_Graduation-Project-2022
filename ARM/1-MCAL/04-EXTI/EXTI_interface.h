/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):EXTI 			 ***********************/
/***********************   DATA : 21-3-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

//Sensing Modes
#define		 EXTI_FALLING_EDGE		1
#define		 EXTI_RISING_EDGE		3
#define		 EXTI_ON_CHANGE			5

//EXTI Line Options
#define		 EXTI_LINE0			0
#define		 EXTI_LINE1			1
#define		 EXTI_LINE2			2
#define		 EXTI_LINE3			3
#define		 EXTI_LINE4			4

/**
 * @def function to initialize EXTI
 */
void EXTI_voidInit(u8 Copy_u8InterruptLine, u8 Copy_u8SenseMode);

/**
 * @def function to set EXTI Sense Mode
 */
void EXTI_voidSetSenseMode(u8 Copy_u8InterruptLine , u8 Copy_u8EXTISenseMode);

/**
 * @def function to enable EXTI
 */
void EXTI_voidEnableEXTI(u8 Copy_u8InterruptLine);

/**
 * @def function to disable EXTI
 */
void EXTI_voidDisableEXTI(u8 Copy_u8InterruptLine);

/**
 * @def function to set software trigger on certain EXTI
 */
void EXTI_voidSoftwareTrigger(u8 Copy_u8InterruptLine);

/**
 * @def function to set callback function
 */
void EXTI_voidSetCallBack(u8 Copy_u8InterruptLine,void (*Copy_pvCallBackFunc) (void)) ;


#endif
