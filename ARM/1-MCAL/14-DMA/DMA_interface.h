/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer : MCAL                  ***********************/
/***********************   SWC (DRIVER):DMA				 ***********************/
/***********************   DATE : 26-5-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef DMA_INTERFACE_H_
#define DMA_INTERFACE_H_

//DMA Peipherals
#define DMA_PER_ADC1			0
#define DMA_PER_SPI				1
#define DMA_PER_USART			2
#define DMA_PER_I2C				3
#define DMA_PER_TIMER1			4
#define DMA_PER_TIMER2			5
#define DMA_PER_TIMER3			6
#define DMA_PER_TIMER4			7

#define DMA_PER_ADC3			8
#define DMA_PER_SPI2			9
#define DMA_PER_UART4			10
#define DMA_PER_SDIO			11
#define DMA_PER_TIMER5			12
#define DMA_PER_TIMER6			13
#define DMA_PER_TIMER7			14
#define DMA_PER_TIMER8			15

//DMA Priorities
#define DMA_PRIORITY_LOW			0
#define DMA_PRIORITY_MED			1
#define DMA_PRIORITY_HIGH			2
#define DMA_PRIORITY_VERY_HIGH		3


//DMA Transfer Direction
#define DMA_DIR_MEM2MEM			0
#define DMA_DIR_PER2MEM			1
#define DMA_DIR_MEM2PER			2


typedef struct
{
	u8 DMA_u8PeripheralID;
	u8 DMA_u8ChannelID;			//0 -> 7 in case if DMA1 and 0->5 in case of DMA2
	u8 DMA_u8DataTransferNum;
	u8 DMA_u8ChannelPriority;
	u8 DMA_u8DataDirection;
	u8 DMA_u8PeripheralDataSize; //8 or 16 or 32
	u8 DMA_u8MemDataSize; //8 or 16 or 32
	u8 DMA_Configure ; // make sure channel of dma comfigure
}DMA_t;


u8 DMA_u8ReadRegisterContent(DMA_t* Copy_DMA_tTransferConfig);

u8 DMA_u8Enable (DMA_t* Copy_DMA_tTransferConfig);

u8 DMA_u8Disable (DMA_t* Copy_DMA_tTransferConfig);





#endif
