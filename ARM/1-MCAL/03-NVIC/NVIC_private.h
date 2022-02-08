/**********************************************************/
/* GRADUATION PROJECT : (FOTA)							  */
/* Version   : V01                                        */
/**********************************************************/
#ifndef NVIC_PRIVATE_H
#define NVIC_PRIVATE_H

#define NVIC_ISER0       *((u32*)0xE000E100) /*Interrupt Set Enable _ Enable External interrupts from 0  to 31 */    
#define NVIC_ISER1       *((u32*)0xE000E104) /*Interrupt Set Enable _ Enable External interrupts from 32 to 63 */

#define NVIC_ICER0       *((u32*)0xE000E180) /*Interrupt Clear Enable _ Clear External interrupts from 0  to 31 */
#define NVIC_ICER1       *((u32*)0xE000E184) /*Interrupt Clear Enable _ Clear External interrupts from 32 to 63 */

#define NVIC_ISPR0       *((u32*)0xE000E200) /*Interrupt Set Pending _ Set pending flags for External interrupts from 0  to 31 */
#define NVIC_ISPR1       *((u32*)0xE000E204) /*Interrupt Set Pending _ Set pending flags for External interrupts from 32 to 63 */

#define NVIC_ICPR0       *((u32*)0xE000E280) /*Interrupt Clear Pending _ Clear pending flags for External interrupts from 0  to 31 */
#define NVIC_ICPR1       *((u32*)0xE000E284) /*Interrupt Clear Pending _ Clear pending flags for External interrupts from 32 to 63 */

#define NVIC_IABR0       *((volatile u32*)0xE000E300) 			/*Interrupt Active Bit _ External interrupts from 0  to 31 */
#define NVIC_IABR1       *((volatile u32*)0xE000E304) 			/*Interrupt Active Bit _ External interrupts from 32 to 63 */

#define NVIC_IPR         ((volatile u8*)0xE000E100 + 0x300)     /*Interrupt Priority Register _ External interrupts from 32 to 63 */
#define SCB_AIRCR		 *((volatile u32*)0xE000ED00 + 0x0C)    /*Application interrupt and reset control register*/


#endif
