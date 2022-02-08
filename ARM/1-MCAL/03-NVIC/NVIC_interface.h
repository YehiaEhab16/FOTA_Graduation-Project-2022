/**********************************************************/
/* GRADUATION PROJECT : (FOTA)							  */
/* Version   : V01                                        */
/**********************************************************/
#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H

u8 NVIC_voidEnableInterrupt  (u8 Copy_u8IntNumber);
u8 NVIC_voidDisableInterrupt (u8 Copy_u8IntNumber);
u8 NVIC_voidSetPendingFlag   (u8 Copy_u8IntNumber);
u8 NVIC_voidClearPendingFlag (u8 Copy_u8IntNumber);
u8 NVIC_u8GetActiveFlag      (u8 Copy_u8IntNumber);
void NVIC_VidSetPriority( s8 Copy_u8INTID , u8 Copy_u8GroupPriority , u8 Copy_u8SubPriority , u32 Copy_u8Group );

#define Group3		0x05FA0300		//4 bits for group (IPR)
#define Group4		0x05FA0400		//3 bits for group and 1 bit for sub
#define Group5		0x05FA0500		//2 bits for group and 2 bit for sub
#define Group6		0x05FA0600		//1 bits for group and 3 bit for sub
#define Group7		0x05FA0700		//0 bits for 4 bits for sub

#endif