/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer : MCAL                  ***********************/
/***********************   SWC (DRIVER):DMA				 ***********************/
/***********************   DATE : 26-5-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef DMA_REGISTER_H_
#define DMA_REGISTER_H_


//DMA1 Registers
#define DMA1_ISR					((volatile u32 *)0x40020000)
#define DMA1_IFCR					((volatile u32 *)0x40020004)
#define DMA1_CCR1					((volatile u32 *)0x40020008)
#define DMA1_CNDTR1					((volatile u32 *)0x4002000C)
#define DMA1_CPAR1					((volatile u32 *)0x40020010)
#define DMA1_CMAR1					((volatile u32 *)0x40020014)

/**
 *
 * This pin about the DMA1_CCR1
 *
 */
#define	MEM2MEM						14
#define	PL1							13
#define PL0							12
#define MSIZE1						11
#define	MSIZE0						10
#define PSIZE1						9
#define	PSIZE0						8
#define MINC						7
#define PINC						6	
#define CIRC						5
#define DIR							4
#define	TEIE						3		
#define	HTIE						2
#define	TCIE						1
#define	EN							0


#endif
