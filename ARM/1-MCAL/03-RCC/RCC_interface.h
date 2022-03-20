/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):RCC 			 ***********************/
/***********************   DATA : 15-11-2021 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/
#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_


#define RCC_AHB				0
#define RCC_APB1			1
#define RCC_APB2			2


#define RCC_HSI				0
#define RCC_HSE		 		17
#define RCC_PLL				24


#define RCC_AHB_SDIO_EN		20
#define RCC_AHB_FSMC_EN		18
#define RCC_AHB_CRC_EN		16
#define RCC_AHB_FLITF_EN	14
#define RCC_AHB_SRAM_EN		12
#define RCC_AHB_DMA2_EN		11
#define RCC_AHB_DMA1_EN		10

#define RCC_APB2_TIM11_EN	51
#define RCC_APB2_TIM10_EN	50
#define RCC_APB2_TIM9_EN	49
#define RCC_APB2_ADC3_EN	45
#define RCC_APB2_USART1_EN	44
#define RCC_APB2_TIM8_EN	43
#define RCC_APB2_SPI1_EN	42
#define RCC_APB2_TIM1_EN	41
#define RCC_APB2_ADC2_EN	40
#define RCC_APB2_ADC1_EN	39
#define RCC_APB2_IOPG_EN	38
#define RCC_APB2_IOPF_EN	37
#define RCC_APB2_IOPE_EN	36
#define RCC_APB2_IOPD_EN	35
#define RCC_APB2_IOPC_EN	34
#define RCC_APB2_IOPB_EN	33
#define RCC_APB2_IOPA_EN	32
#define RCC_APB2_AFIO_EN	30


#define RCC_APB1_DAC_EN		79
#define RCC_APB1_PWR_EN		78
#define RCC_APB1_BKP_EN		77
#define RCC_APB1_CAN_EN		75
#define RCC_APB1_USB_EN		73
#define RCC_APB1_I2C1_EN	72
#define RCC_APB1_I2C2_EN	71
#define RCC_APB1_UART5_EN	70
#define RCC_APB1_UART4_EN	69
#define RCC_APB1_USART3_EN	68
#define RCC_APB1_USART2_EN	67
#define RCC_APB1_SPI3_EN	65
#define RCC_APB1_SPI2_EN	64
#define RCC_APB1_WWDG_EN	61
#define RCC_APB1_TIM14_EN	58
#define RCC_APB1_TIM13_EN	57
#define RCC_APB1_TIM12_EN	56
#define RCC_APB1_TIM7_EN	55
#define RCC_APB1_TIM6_EN	54
#define RCC_APB1_TIM5_EN	53
#define RCC_APB1_TIM4_EN	52
#define RCC_APB1_TIM3_EN	51
#define RCC_APB1_TIM2_EN	50



/*
 * RCC_ENABLE  : Enable Mode
 * RCC_DISABLE : Disable Mode
 *
 * */
#define RCC_ENABLE			1
#define RCC_DISABLE 		0



/*
 * RCC_u8BusID take : 1- RCC_AHB
 * 					  2- RCC_APB1
 * 					  3- RCC_APB2
 *
 * RCC_u8PeripheralId : - AHB :
 * 								RCC_AHB_SDIO_EN
 *                              RCC_AHB_FSMC_EN
 *                              RCC_AHB_CRC_EN
 *                              RCC_AHB_FLITF_EN
 *                              RCC_AHB_SRAM_EN
 *                              RCC_AHB_DMA2_EN
 *                              RCC_AHB_DMA1_EN
 *
 * 					    - APB1:
 * 					    		RCC_APB1_DAC_EN
 * 					    		RCC_APB1_PWR_EN
 * 					    		RCC_APB1_BKP_EN
 * 					    		RCC_APB1_CAN_EN
 * 					    		RCC_APB1_USB_EN
 * 					    		RCC_APB1_I2C1_EN
 * 					    		RCC_APB1_I2C2_EN
 * 					    		RCC_APB1_UART5_EN
 * 					    		RCC_APB1_UART4_EN
 * 					    		RCC_APB1_USART3_EN
 * 					    		RCC_APB1_USART2_EN
 * 					    		RCC_APB1_SPI3_EN
 * 					    		RCC_APB1_SPI2_EN
 * 					    		RCC_APB1_WWDG_EN
 * 					    		RCC_APB1_TIM14_EN
 * 					    		RCC_APB1_TIM13_EN
 * 					            RCC_APB1_TIM12_EN
 * 					            RCC_APB1_TIM7_EN
 * 					            RCC_APB1_TIM6_EN
 * 					            RCC_APB1_TIM5_EN
 * 					            RCC_APB1_TIM4_EN
 * 					            RCC_APB1_TIM3_EN
 * 					            RCC_APB1_TIM2_EN

 * 					    - APB2:
 * 					    		RCC_APB2_TIM11_EN
 * 					    		RCC_APB2_TIM10_EN
 * 					    		RCC_APB2_TIM9_EN
 * 					    		RCC_APB2_ADC3_EN
 * 					    		RCC_APB2_USART1_EN
 * 					    		RCC_APB2_TIM8_EN
 * 					    		RCC_APB2_SPI1_EN
 * 					    		RCC_APB2_TIM1_EN
 * 					    		RCC_APB2_ADC2_EN
 * 					    		RCC_APB2_ADC1_EN
 * 					    		RCC_APB2_IOPG_EN
 * 					    		RCC_APB2_IOPF_EN
 * 					    		RCC_APB2_IOPE_EN
 * 					    		RCC_APB2_IOPD_EN
 * 					    		RCC_APB2_IOPC_EN
 * 					            RCC_APB2_IOPB_EN
 * 					            RCC_APB2_IOPA_EN
 * 					            RCC_APB2_AFIO_EN


 */

typedef struct
{
	u8 RCC_u8BusID ;
	u8 RCC_u8PeripheralId ;


}RCC_t;

void RCC_voidInit (void);

u8 RCC_u8EnableClock (struct Peripheral *Copy_Peripheral);

u8 RCC_u8DisableClock (struct Peripheral *Copy_Peripheral);

u8 RCC_u8ChangeModeBuses (u8 Copy_u8Bus , u8 Copy_u8StateBus);

void RCC_voidEnableClock(u8 Copy_u8BusId, u8 Copy_u8PerId);

#endif
