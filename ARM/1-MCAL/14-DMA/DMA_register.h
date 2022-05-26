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

//DMA Registers
typedef struct
{				
  volatile u32 ISR;   
  volatile u32 IFCR;  
  volatile u32 CCR1;  
  volatile u32 CNDTR1;
  volatile u32 CPAR1;
  volatile u32 CMAR1;
  volatile u32 RESERVED1;
  volatile u32 CCR2;  
  volatile u32 CNDTR2;
  volatile u32 CPAR2;
  volatile u32 CMAR2;
  volatile u32 RESERVED2;
  volatile u32 CCR3;  
  volatile u32 CNDTR3;
  volatile u32 CPAR3;
  volatile u32 CMAR3;
  volatile u32 RESERVED3;
  volatile u32 CCR4;  
  volatile u32 CNDTR4;
  volatile u32 CPAR4;
  volatile u32 CMAR4;
  volatile u32 RESERVED4;
  volatile u32 CCR5;  
  volatile u32 CNDTR5;
  volatile u32 CPAR5;
  volatile u32 CMAR5;
  volatile u32 RESERVED5;
  volatile u32 CCR6;  
  volatile u32 CNDTR6;
  volatile u32 CPAR6;
  volatile u32 CMAR6;
  volatile u32 RESERVED6;
  volatile u32 CCR7;  
  volatile u32 CNDTR7;
  volatile u32 CPAR7;
  volatile u32 CMAR7;
  volatile u32 RESERVED7;
}DMA_r;

//DMA Base Addresses
#define DMA1						((volatile DMA_r *)0x40020000)
#define DMA2						((volatile DMA_r *)0x40020400)

//DMA CCR Control Pins
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
