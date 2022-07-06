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
#define		 FALLING_EDGE		1
#define		 RISING_EDGE		3
#define		 ON_CHANGE			5

//EXTI Line Options
#define		 EXTI_LINE0			0
#define		 EXTI_LINE1			1
#define		 EXTI_LINE2			2

/**
 * @def function to initialize EXTI
 */
void EXTI_voidInit(void);

/**
 * @def function to set EXTI Sense Mode
 */
void EXTI_voidSetSignalLatch(u8 Copy_u8EXTILine , u8 Copy_u8EXTISenseMode);

/**
 * @def function to enable EXTI
 */
void EXTI_voidEnableEXTI(u8 Copy_u8EXTILine);

/**
 * @def function to disable EXTI
 */
void EXTI_voidDisableEXTI(u8 Copy_u8EXTILine);

/**
 * @def function to set software trigger on certain EXTI
 */
void EXTI_voidSoftwareTrigger(u8 Copy_u8EXTILine);

/**
 * @def function to set callback function
 */
void EXTI_voidSetCallBack(void (*Copy_pvCallBackFunc) (void));


#endif