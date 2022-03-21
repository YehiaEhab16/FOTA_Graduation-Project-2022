/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):RCC 			 ***********************/
/***********************   DATA : 15-11-2021 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "RCC_register.h"
#include "RCC_private.h"
#include "RCC_config.h"



void RCC_voidAjustmentClockSys ()
{
	u32 Local_u8RealValue ; // the value of HSICAL
	u8 Local_u8ChangeValue ;
	u8 Local_u8EditionValue ; // the value of the HSITRIM
	Local_u8RealValue = 255|(RCC_CR>>8);
	if (Local_u8RealValue != RCC_HSI_SPEED)
	{
		Local_u8ChangeValue = Local_u8RealValue - RCC_HSI_SPEED ;
		Local_u8ChangeValue /= 40 ;
		Local_u8EditionValue= (31 | (RCC_CR>>3)) + 40 ;
		RCC_CR |=(Local_u8EditionValue <<3);
	}

}

u8 RCC_u8ChangeModeBuses (u8 Copy_u8SysClock , u8 Copy_u8StateBus)
{

	u8 Local_u8StateError = 0 ;
	if (Copy_u8StateBus == RCC_ENABLE)
	{
		switch (Copy_u8SysClock)
		{
		case RCC_HSI :  SET_BIT(RCC_CR,Copy_u8SysClock);while (GET_BIT(RCC_CR,RCC_HSI_READY)==0);  break;
		case RCC_HSE :  SET_BIT(RCC_CR,Copy_u8SysClock);while (GET_BIT(RCC_CR,RCC_HSE_READY)==0) ; break;
		case RCC_PLL :  SET_BIT(RCC_CR,Copy_u8SysClock);while (GET_BIT(RCC_CR,RCC_PLL_READY)==0) ; break;
		default : Local_u8StateError = 1 ;                                                     break;

		}

	}
	else if (Copy_u8StateBus == RCC_DISABLE)
	{
		switch (Copy_u8SysClock)
		{
		case RCC_HSI :  CLR_BIT(RCC_CR,Copy_u8SysClock);while (GET_BIT(RCC_CR,RCC_HSI_READY)!=0);  break;
		case RCC_HSE :  CLR_BIT(RCC_CR,Copy_u8SysClock);while (GET_BIT(RCC_CR,RCC_HSE_READY)!=0) ; break;
		case RCC_PLL :  CLR_BIT(RCC_CR,Copy_u8SysClock);while (GET_BIT(RCC_CR,RCC_PLL_READY)!=0) ; break;
		default : Local_u8StateError = 1 ;                                                     break;

		}

	}
	else
	{
		Local_u8StateError = 1 ;

	}

	return Local_u8StateError ;
}


void RCC_voidInit (void)
{
	RCC_u8ChangeModeBuses (RCC_HSI , RCC_ENABLE) ;
	RCC_u8ChangeModeBuses (RCC_HSE , RCC_ENABLE) ;
	RCC_u8ChangeModeBuses (RCC_PLL , RCC_ENABLE) ;

	/*
	 *Selection  Section
	 *
	 **/

# if RCC_CLOCK_SYS	==  RCC_HSI_SELECTION
	RCC_CFGR&=~(3<<0);
	RCC_CFGR|=RCC_HSI_SELECTION ;

#elif RCC_CLOCK_SYS	==  RCC_HSE_SELECTION
	RCC_CFGR&=~(3<<0);
	RCC_CFGR|=RCC_HSE_SELECTION;

#elif RCC_CLOCK_SYS	==  RCC_PLL_SELECTION
	RCC_CFGR&=~(3<<0);
	RCC_CFGR|=RCC_PLL_SELECTION;
#if RCC_PLL_ENTRY  == RCC_PLL_HSI
	CLR_BIT (RCC_CFGR,16);
#elif RCC_PLL_ENTRY  == RCC_PLL_HSE_ENTRY
#if RCC_PLL_HSE_ENTRY ==RCC_PLL_HSE_12
	SET_BIT (RCC_CFGR,17);
#elif RCC_PLL_HSE_ENTRY == RCC_PLL_HSE_1
	CLR_BIT (RCC_CFGR,17);
#else
#error "NOT VALID"
#endif
	SET_BIT (RCC_CFGR,16);

#else
#error "invalid Choose"
#endif

#else
#error "THE SELECTION OF SYSTEM CLOCK IS NOT VALID "
#endif

	/*
	 *Select the Secuity of RCC if the external clock is drop  the security mode convert to  the
	 *internal  clock
	 **/
#if RCC_SECURITY == RCC_ENABLE
	SET_BIT (RCC_CR ,RCC_ENABLE );
#elif RCC_SECURITY == RCC_DISABLE
	CLR_BIT (RCC_CR ,RCC_ENABLE );
#else
#error "THE SELECTION OF RCC SECURITY "
#endif

	/*clear the prescaler bits of  APB1 */
	RCC_CFGR&=~(7<<8);
	RCC_CFGR|=(RCC_APB1_PRESCALER<<8);

	/*clear the prescaler bits of  APB2 */
	RCC_CFGR&=~(7<<11);
	RCC_CFGR|=(RCC_APB2_PRESCALER<<11);

	/*clear the prescaler bits of  AHB */
	RCC_CFGR&=~(15<<4);
	RCC_CFGR|=(RCC_APB1_PRESCALER<<4);

	/*
	 * Select the multiplication of PLL
	 * */
	RCC_CFGR&=~(4<<18);
	RCC_CFGR|=(RCC_PLL_MULL<<18);


	RCC_voidAjustmentClockSys ();



#if RCC_AHB_SDIO_STATE		    ==    ENABLE
	SET_BIT(RCC_AHBENR,RCC_AHB_SDIO_EN-RCC_AHB_OFFSET);

#elif RCC_AHB_SDIO_STATE		==    DISABLE
	CLR_BIT(RCC_AHBENR,RCC_AHB_SDIO_EN-RCC_AHB_OFFSET);

#endif

#if RCC_AHB_FSMC_STATE		    ==    ENABLE
	SET_BIT(RCC_AHBENR,RCC_AHB_FSMC_EN-RCC_AHB_OFFSET);

#elif RCC_AHB_FSMC_STATE		==    DISABLE
	CLR_BIT(RCC_AHBENR,RCC_AHB_FSMC_EN-RCC_AHB_OFFSET);

#endif
#if RCC_AHB_CRC_STATE		    ==    ENABLE
	S_BIT(RCC_AHBENR,RCC_AHB_CRC_EN-RCC_AHB_OFFSET);

#elif RCC_AHB_CRC_STATE		    ==    DISABLE
	CLR_BIT(RCC_AHBENR,RCC_AHB_CRC_EN-RCC_AHB_OFFSET);

#endif
#if RCC_AHB_FLITF_STATE		    ==    ENABLE
	SET_BIT(RCC_AHBENR,RCC_AHB_FLITF_EN-RCC_AHB_OFFSET);

#elif RCC_AHB_FLITF_STATE       ==    DISABLE
	CLR_BIT(RCC_AHBENR,RCC_AHB_FLITF_EN-RCC_AHB_OFFSET);

#endif
#if RCC_AHB_SRAM_STATE		    ==    ENABLE
	SET_BIT(RCC_AHBENR,RCC_AHB_SRAM_EN-RCC_AHB_OFFSET);

#elif RCC_AHB_SRAM_STATE	    ==    DISABLE
	CLR_BIT(RCC_AHBENR,RCC_AHB_SRAM_EN-RCC_AHB_OFFSET);


#endif
#if RCC_AHB_DMA2_STATE		    ==    ENABLE
	SET_BIT(RCC_AHBENR,RCC_AHB_DMA2_EN-RCC_AHB_OFFSET);

#elif RCC_AHB_DMA2_STATE	    ==    DISABLE
	CLR_BIT(RCC_AHBENR,RCC_AHB_DMA2_EN-RCC_AHB_OFFSET);

#endif
#if RCC_AHB_DMA1_STATE		    ==    ENABLE
	SET_BIT(RCC_AHBENR,RCC_AHB_DMA1_EN-RCC_AHB_OFFSET);

#elif RCC_AHB_DMA1_STATE		==    DISABLE
	CLR_BIT(RCC_AHBENR,RCC_AHB_DMA1_EN-RCC_AHB_OFFSET);

#endif




#if RCC_APB2_TIM11_STATE	    ==     ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB2_TIM11_EN-RCC_APB2_OFFSET);
#elif RCC_APB2_TIM11_STATE	    ==     DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB2_TIM11_EN-RCC_APB2_OFFSET);

#endif
#if RCC_APB2_TIM10_STATE	    ==     ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB2_TIM10_EN-RCC_APB2_OFFSET);

#elif RCC_APB2_TIM10_STATE	    ==     DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB2_TIM10_EN-RCC_APB2_OFFSET);

#endif
#if RCC_APB2_TIM9_STATE	        ==     ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB2_TIM9_EN-RCC_APB2_OFFSET);

#elif RCC_APB2_TIM9_STATE	    ==     DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB2_TIM9_EN-RCC_APB2_OFFSET);

#endif
#if RCC_APB2_ADC3_STATE	        ==     ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB2_ADC3_EN-RCC_APB2_OFFSET);
#elif RCC_APB2_ADC3_STATE	    ==     DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB2_ADC3_EN-RCC_APB2_OFFSET);

#endif
#if RCC_APB2_USART1_STATE	    ==     ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB2_USART1_EN-RCC_APB2_OFFSET);

#elif RCC_APB2_USART1_STATE	    ==     DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB2_USART1_EN-RCC_APB2_OFFSET);

#endif
#if RCC_APB2_TIM8_STATE	        ==     ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB2_TIM8_EN-RCC_APB2_OFFSET);

#elif RCC_APB2_TIM8_STATE	    ==     DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB2_TIM8_EN-RCC_APB2_OFFSET);

#endif
#if RCC_APB2_SPI1_STATE	        ==     ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB2_SPI1_EN-RCC_APB2_OFFSET);

#elif RCC_APB2_SPI1_STATE	    ==     DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB2_SPI1_EN-RCC_APB2_OFFSET);

#endif
#if RCC_APB2_TIM1_STATE	        ==     ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB2_TIM1_EN-RCC_APB2_OFFSET);

#elif RCC_APB2_TIM1_STATE	    ==     DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB2_TIM1_EN-RCC_APB2_OFFSET);

#endif
#if RCC_APB2_ADC2_STATE	        ==     ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB2_ADC2_EN-RCC_APB2_OFFSET);
#elif RCC_APB2_ADC2_STATE	    ==     DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB2_ADC2_EN-RCC_APB2_OFFSET);

#endif
#if RCC_APB2_ADC1_STATE	        ==     ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB2_ADC1_EN-RCC_APB2_OFFSET);

#elif RCC_APB2_ADC1_STATE	    ==     DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB2_ADC1_EN-RCC_APB2_OFFSET);

#endif
#if RCC_APB2_IOPG_STATE	        ==     ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB2_IOPG_EN-RCC_APB2_OFFSET);

#elif RCC_APB2_IOPG_STATE       ==     DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB2_IOPG_EN-RCC_APB2_OFFSET);

#endif
#if RCC_APB2_IOPF_STATE	        ==     ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB2_IOPF_EN-RCC_APB2_OFFSET);

#elif RCC_APB2_IOPF_STATE	    ==     DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB2_IOPF_EN-RCC_APB2_OFFSET);

#endif
#if RCC_APB2_IOPE_STATE	        ==     ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB2_IOPE_EN-RCC_APB2_OFFSET);

#elif RCC_APB2_IOPE_STATE	    ==     DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB2_IOPE_EN-RCC_APB2_OFFSET);

#endif
#if RCC_APB2_IOPD_STATE	        ==     ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB2_IOPD_EN-RCC_APB2_OFFSET);

#elif RCC_APB2_IOPD_STATE       ==     DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB2_IOPD_EN-RCC_APB2_OFFSET);

#endif
#if RCC_APB2_IOPC_STATE	        ==     ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB2_IOPC_EN-RCC_APB2_OFFSET);

#elif RCC_APB2_IOPC_STATE       ==     DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB2_IOPC_EN-RCC_APB2_OFFSET);

#endif
#if RCC_APB2_IOPB_STATE	        ==     ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB2_IOPB_EN-RCC_APB2_OFFSET);

#elif RCC_APB2_IOPB_STATE       ==     DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB2_IOPB_EN-RCC_APB2_OFFSET);

#endif
#if RCC_APB2_IOPA_STATE	        ==     ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB2_IOPA_EN-RCC_APB2_OFFSET);

#elif RCC_APB2_IOPA_STATE	    ==     DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB2_IOPA_EN-RCC_APB2_OFFSET);

#endif
#if   RCC_APB2_AFIO_STATE	        ==     ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB2_AFIO_EN-RCC_APB2_OFFSET);

#elif RCC_APB2_AFIO_STATE	    ==     DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB2_AFIO_EN-RCC_APB2_OFFSET);

#endif


#if   RCC_APB1_DAC_STATE			==    ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB1_DAC_EN	-RCC_APB1_OFFSET);
#elif RCC_APB1_DAC_STATE		==    DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB1_DAC_EN	-RCC_APB1_OFFSET);
#endif
#if   RCC_APB1_PWR_STATE	        ==    ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB1_PWR_EN	-RCC_APB1_OFFSET);

#elif RCC_APB1_PWR_STATE	    ==    DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB1_PWR_EN	-RCC_APB1_OFFSET);

#endif
#if   RCC_APB1_BKP_STATE	        ==    ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB1_BKP_EN	-RCC_APB1_OFFSET);

#elif RCC_APB1_BKP_STATE	    ==    DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB1_BKP_EN	-RCC_APB1_OFFSET);

#endif
#if   RCC_APB1_CAN_STATE	        ==    ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB1_CAN_EN	-RCC_APB1_OFFSET);

#elif RCC_APB1_CAN_STATE	    ==    DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB1_CAN_EN	-RCC_APB1_OFFSET);

#endif
#if   RCC_APB1_USB_STATE	        ==    ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB1_USB_EN	-RCC_APB1_OFFSET);

#elif RCC_APB1_USB_STATE	    ==    DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB1_USB_EN	-RCC_APB1_OFFSET);

#endif
#if   RCC_APB1_I2C1_STATE	        ==    ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB1_I2C1_EN-RCC_APB1_OFFSET);

#elif RCC_APB1_I2C1_STATE	    ==    DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB1_I2C1_EN-RCC_APB1_OFFSET);

#endif
#if   RCC_APB1_I2C2_STATE	        ==    ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB1_I2C2_EN-RCC_APB1_OFFSET);

#elif RCC_APB1_I2C2_STATE	    ==    DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB1_I2C2_EN-RCC_APB1_OFFSET);
#endif
#if   RCC_APB1_UART5_STATE	    ==    ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB1_UART5_EN-RCC_APB1_OFFSET);

#elif RCC_APB1_UART5_STATE	    ==    DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB1_UART5_EN-RCC_APB1_OFFSET);

#endif
#if   RCC_APB1_UART4_STATE	    ==    ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB1_UART4_EN-RCC_APB1_OFFSET);

#elif RCC_APB1_UART4_STATE	    ==    DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB1_UART4_EN-RCC_APB1_OFFSET);

#endif
#if   RCC_APB1_USART3_STATE	    ==    ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB1_USART3_EN-RCC_APB1_OFFSET);

#elif RCC_APB1_USART3_STATE	    ==	  DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB1_USART3_EN-RCC_APB1_OFFSET);

#endif
#if   RCC_APB1_USART2_STATE	    ==    ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB1_USART2_EN-RCC_APB1_OFFSET);

#elif RCC_APB1_USART2_STATE	    ==    DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB1_USART2_EN-RCC_APB1_OFFSET);

#endif
#if   RCC_APB1_SPI3_STATE	        ==    ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB1_SPI3_EN-RCC_APB1_OFFSET);

#elif RCC_APB1_SPI3_STATE	    ==    DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB1_SPI3_EN-RCC_APB1_OFFSET);

#endif
#if   RCC_APB1_SPI2_STATE	        ==    ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB1_SPI2_EN-RCC_APB1_OFFSET);

#elif RCC_APB1_SPI2_STATE	    ==    DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB1_SPI2_EN-RCC_APB1_OFFSET);
#endif
#if   RCC_APB1_WWDG_STATE	        ==    ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB1_WWDG_EN-RCC_APB1_OFFSET);

#elif RCC_APB1_WWDG_STATE	    ==    DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB1_WWDG_EN-RCC_APB1_OFFSET);

#endif
#if   RCC_APB1_TIM14_STATE	    ==    ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB1_TIM14_EN-RCC_APB1_OFFSET);

#elif RCC_APB1_TIM14_STATE	    ==    DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB1_TIM14_EN-RCC_APB1_OFFSET);

#endif
#if   RCC_APB1_TIM13_STATE	    ==    ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB1_TIM13_EN-RCC_APB1_OFFSET);

#elif RCC_APB1_TIM13_STATE	    ==    DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB1_TIM13_EN-RCC_APB1_OFFSET);


#endif
#if   RCC_APB1_TIM12_STATE	    ==    ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB1_TIM12_EN-RCC_APB1_OFFSET);

#elif RCC_APB1_TIM12_STATE	    ==    DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB1_TIM12_EN-RCC_APB1_OFFSET);

#endif
#if   RCC_APB1_TIM7_STATE	        ==    ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB1_TIM7_EN-RCC_APB1_OFFSET);

#elif RCC_APB1_TIM7_STATE	   		==    DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB1_TIM7_EN-RCC_APB1_OFFSET);

#endif
#if   RCC_APB1_TIM6_STATE	        ==    ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB1_TIM6_EN-RCC_APB1_OFFSET);
#elif RCC_APB1_TIM6_STATE	   		==    DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB1_TIM6_EN-RCC_APB1_OFFSET);

#endif
#if   RCC_APB1_TIM5_STATE	        ==    ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB1_TIM5_EN-RCC_APB1_OFFSET);

#elif RCC_APB1_TIM5_STATE	    	==    DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB1_TIM5_EN-RCC_APB1_OFFSET);

#endif
#if   RCC_APB1_TIM4_STATE	        ==    ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB1_TIM4_EN-RCC_APB1_OFFSET);

#elif RCC_APB1_TIM4_STATE	    	==    DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB1_TIM4_EN-RCC_APB1_OFFSET);

#endif
#if   RCC_APB1_TIM3_STATE	        ==    ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB1_TIM3_EN-RCC_APB1_OFFSET);

#elif RCC_APB1_TIM3_STATE	    	==    DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB1_TIM3_EN-RCC_APB1_OFFSET);

#endif
#if   RCC_APB1_TIM2_STATE	        ==    ENABLE
	SET_BIT(RCC_APB2ENR,RCC_APB1_TIM2_EN-RCC_APB1_OFFSET);

#elif RCC_APB1_TIM2_STATE	   		==    DISABLE
	CLR_BIT(RCC_APB2ENR,RCC_APB1_TIM2_EN-RCC_APB1_OFFSET);
#endif
}

u8 RCC_u8EnableClock (struct Peripheral *Copy_Peripheral)
{
	u8 Local_u8ErrorState = OK  ;
	if (((Copy_Peripheral ->RCC_u8PeripheralId - RCC_AHB_OFFSET)<RCC_NUM_REGISTER )||((Copy_Peripheral ->RCC_u8PeripheralId - RCC_APB2_OFFSET)<RCC_NUM_REGISTER )||((Copy_Peripheral ->RCC_u8PeripheralId - RCC_APB1_OFFSET)<RCC_NUM_REGISTER ) )
	{
		switch (Copy_Peripheral -> RCC_u8BusID)
		{
		case RCC_AHB  : SET_BIT(RCC_AHBENR,(Copy_Peripheral ->RCC_u8PeripheralId-RCC_AHB_OFFSET));break;
		case RCC_APB1 : SET_BIT(RCC_APB1ENR,(Copy_Peripheral ->RCC_u8PeripheralId-RCC_APB1_OFFSET));break;
		case RCC_APB2 : SET_BIT(RCC_APB2ENR,((Copy_Peripheral ->RCC_u8PeripheralId)-RCC_APB2_OFFSET));break;
		default : Local_u8ErrorState = NOK ; break ;
		}
	}
	else
	{
		Local_u8ErrorState = NOK ;

	}

	return Local_u8ErrorState;
}

u8 RCC_u8DisableClock (struct Peripheral *Copy_Peripheral)
{
	u8 Local_u8ErrorState = OK  ;
	if (((Copy_Peripheral ->RCC_u8PeripheralId - RCC_AHB_OFFSET)<RCC_NUM_REGISTER )||((Copy_Peripheral ->RCC_u8PeripheralId - RCC_APB2_OFFSET)<RCC_NUM_REGISTER )||((Copy_Peripheral ->RCC_u8PeripheralId - RCC_APB1_OFFSET)<RCC_NUM_REGISTER ) )
	{
		switch (Copy_Peripheral -> RCC_u8BusID)
		{
		case RCC_AHB  : CLR_BIT(RCC_AHBENR,(Copy_Peripheral ->RCC_u8PeripheralId-RCC_AHB_OFFSET));break;
		case RCC_APB1 : CLR_BIT(RCC_APB1ENR,(Copy_Peripheral ->RCC_u8PeripheralId-RCC_APB1_OFFSET));break;
		case RCC_APB2 : CLR_BIT(RCC_APB2ENR,(Copy_Peripheral ->RCC_u8PeripheralId-RCC_APB2_OFFSET));break;
		default : Local_u8ErrorState = NOK ; break ;
		}
	}
	else
	{
		Local_u8ErrorState = NOK ;

	}

	return Local_u8ErrorState;


}

u8 RCC_u8DisableClock_2 (u32 Copy_u32PeripheralID)
{
	u8 Local_u8ErrorState = OK  ;
	if(Copy_u32PeripheralID <=AHB_END  && Copy_u32PeripheralID >=AHB_START)
	{
		CLR_BIT(RCC_AHBENR,(Copy_u32PeripheralID-RCC_AHB_OFFSET));

	}

	else if (Copy_u32PeripheralID <=RCC_APB1ENR  && Copy_u32PeripheralID >=APB1_START)
	{
		CLR_BIT(RCC_AHBENR,(Copy_u32PeripheralID-RCC_APB1_OFFSET));

	}
	else if (Copy_u32PeripheralID <=RCC_APB2ENR  && Copy_u32PeripheralID >=APB2_START)
	{
		CLR_BIT(RCC_AHBENR,(Copy_u32PeripheralID-RCC_APB2_OFFSET));


	}
	else
	{
		Local_u8ErrorState = NOK ;

	}

	return Local_u8ErrorState;


}
