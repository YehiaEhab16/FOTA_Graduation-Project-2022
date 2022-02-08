/**********************************************************/
/* GRADUATION PROJECT : (FOTA)							  */
/* Version   : V01                                        */
/**********************************************************/
#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H


void EXTI_voidInit();
void EXTI_voidEnableEXTI(u8 Copy_u8Line);
void EXTI_voidDisableEXTI(u8 Copy_u8Line);
void EXTI_voidSwTrigger(u8 Copy_u8Line);
void EXTI_voidSetSignalLatch(u8 Copy_u8Line , u8 Copy_u8Mode);

#endif