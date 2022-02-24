/**********************************************************/
/* GRADUATION PROJECT : (FOTA)							  */
/* Version   : V01                                        */
/**********************************************************/
#ifndef EXTI0_INTERFACE_H
#define EXTI0_INTERFACE_H

void EXTI_voidInit(void);
void EXTI_voidSetSignalLatch(u8 Copy_u8EXTILine , u8 Copy_u8EXTISenseMode);
void EXTI_voidEnableEXTI(u8 Copy_u8EXTILine);
void EXTI_voidDisableEXTI(u8 Copy_u8EXTILine);
void EXTI_voidSoftwareTrigger(u8 Copy_u8EXTILine);

void EXTI_voidSetCallBack(void (*ptr) (void));

#define		 FALLING_EDGE		1

#define		 RISING_EDGE		3

#define		 ON_CHANGE			5

#define		 EXTI_LINE0			0

#define		 EXTI_LINE1			1

#define		 EXTI_LINE2			2

#endif