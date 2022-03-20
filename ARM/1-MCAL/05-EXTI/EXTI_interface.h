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

#define		 FALLING_EDGE		1
#define		 RISING_EDGE		3
#define		 ON_CHANGE			5

#define		 EXTI_LINE0			0
#define		 EXTI_LINE1			1
#define		 EXTI_LINE2			2

void EXTI_voidInit(void);
void EXTI_voidSetSignalLatch(u8 Copy_u8EXTILine , u8 Copy_u8EXTISenseMode);
void EXTI_voidEnableEXTI(u8 Copy_u8EXTILine);
void EXTI_voidDisableEXTI(u8 Copy_u8EXTILine);
void EXTI_voidSoftwareTrigger(u8 Copy_u8EXTILine);

void EXTI_voidSetCallBack(void (*ptr) (void));


#endif