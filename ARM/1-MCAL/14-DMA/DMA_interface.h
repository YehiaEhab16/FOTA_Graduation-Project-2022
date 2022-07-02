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

//DMA Peripheral
#define DMA_CHANNEL1		1
#define DMA_CHANNEL2		2
#define DMA_CHANNEL3		3
#define DMA_CHANNEL4		4
#define DMA_CHANNEL5		5


//DMA Priorities
#define DMA_PRIORITY_LOW			0
#define DMA_PRIORITY_MED			1
#define DMA_PRIORITY_HIGH			2
#define DMA_PRIORITY_VERY_HIGH		3


//DMA Transfer Direction
#define DMA_DIR_MEM2MEM			0
#define DMA_DIR_PER2MEM			1
#define DMA_DIR_MEM2PER			2

/**
 * DMA_u8ChannelID : DMA_CHANNEL1 : 1- SPI\I2C RX
 * 									2- TIM5_CH4/Trigger
 * 									3- TIM8_CH3/Trigger
 *
 * 					 DMA_CHANNEL2 : 1- SPI/I2S3_TX
 * 					 				2- TIM5_CH3
 * 					 				3- TIM8_CH4
 *
 * 					 DMA_CHANNEL3 : 1- UART4_RX
 * 					 				2- TIM6_UP/DAC_Channel1
 * 					 				3- TIM8_CH1
 *
 * 					 DMA_CHANNEL4 : 1- SDIO
 * 					 				2- TIM5_CH2
 * 					 				3- TIM7_UP/DAC_Channel2
 *
 * 					 DMA_CHANNEL5 : 1- ADC3
 * 					 				2- UART4_TX
 * 					 				3- TIM5_CH1
 *
 *
 */
typedef struct
{
	u32 DMA_u8ChannelID;			//0 -> 7 in case if DMA1 and 0->5 in case of DMA2
	u8 DMA_u8DataTransferNum;
	u8 DMA_u8ChannelPriority;
	u8 DMA_u8DataDirection;
	u8 DMA_u8PeripheralDataSize; //8 or 16 or 32
	u8 DMA_u8MemDataSize; //8 or 16 or 32
	u8 DMA_Configure ; // make sure channel of dma comfigure
}DMA_t;


u8 DMA_u8Configuration(DMA_t* Copy_DMA_tTransferConfig);

u8 DMA_u8Enable (DMA_t* Copy_DMA_tTransferConfig , u32* Copy_u32PeripheralAddress, u32* Copy_u32MemoryAddress );

u8 DMA_u8Disable (DMA_t* Copy_DMA_tTransferConfig);





#endif
