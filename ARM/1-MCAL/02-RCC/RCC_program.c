/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):RCC 			 ***********************/
/***********************   DATA : 21-3-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/
#include "../../6-Library/STD_TYPES.h"
#include "../../6-Library/BIT_MATH.h"

#include "RCC_interface.h"
#include "RCC_register.h"
#include "RCC_private.h"
#include "RCC_config.h"


//Initializing All Peripherals
void RCC_voidInit (void)
{
	RCC_u8ChangeModeBuses (RCC_CR_HSI , RCC_ENABLE) ;
	RCC_u8ChangeModeBuses (RCC_CR_HSE , RCC_ENABLE) ;
	RCC_u8ChangeModeBuses (RCC_CR_PLL , RCC_ENABLE) ;

	//Selection Section
	#if RCC_CLOCK_SYS	==  RCC_HSI_SELECTION
	RCC->CFGR&=~(3<<0);/***************EDIT***********/
	RCC->CFGR|=RCC_HSI_SELECTION ;

	#elif RCC_CLOCK_SYS	==  RCC_HSE_SELECTION
	RCC->CFGR&=~(3<<0);/***************EDIT***********/
	RCC->CFGR|=RCC_HSE_SELECTION;

	#elif RCC_CLOCK_SYS	==  RCC_PLL_SELECTION
	RCC->CFGR&=~(3<<0);/***************EDIT***********/
	RCC->CFGR|=RCC_PLL_SELECTION;
	#if RCC_PLL_ENTRY  == RCC_PLL_HSI
	CLR_BIT (RCC->CFGR,16);/***************EDIT***********/
	#elif RCC_PLL_ENTRY  == RCC_PLL_HSE_ENTRY
	#if RCC_PLL_HSE_ENTRY ==RCC_PLL_HSE_12
	SET_BIT (RCC->CFGR,17);/***************EDIT***********/
	#elif RCC_PLL_HSE_ENTRY == RCC_PLL_HSE_1
	CLR_BIT (RCC->CFGR,17);/***************EDIT***********/
	#else
	#error "NOT VALID"
	#endif
	SET_BIT (RCC->CFGR,16);/***************EDIT***********/

	#else
	#error "invalid Choose"
	#endif

	#else
	#error "THE SELECTION OF SYSTEM CLOCK IS NOT VALID "
	#endif

	//Select the Secuity of RCC if the external clock is drop  the security mode convert to  the internal  clock
	#if RCC_SECURITY == RCC_ENABLE
	SET_BIT (RCC->CR ,RCC_ENABLE );
	#elif RCC_SECURITY == RCC_DISABLE
	CLR_BIT (RCC->CR ,RCC_ENABLE );
	#else
	#error "THE SELECTION OF RCC SECURITY "
	#endif

	//Clear the prescaler bits of  APB1
	RCC->CFGR&=~(7<<8);	/***************EDIT***********/
	RCC->CFGR|=(RCC_APB1_PRESCALER<<8);/***************EDIT***********/

	//Clear the prescaler bits of  APB2
	RCC->CFGR&=~(7<<11);/***************EDIT***********/
	RCC->CFGR|=(RCC_APB2_PRESCALER<<11);/***************EDIT***********/

	//Clear the prescaler bits of  AHB
	RCC->CFGR&=~(15<<4);/***************EDIT***********/
	RCC->CFGR|=(RCC_APB1_PRESCALER<<4);/***************EDIT***********/

	//Select the multiplication of PLL
	RCC->CFGR&=~(4<<18);/***************EDIT***********/
	RCC->CFGR|=(RCC_PLL_MULL<<18);/***************EDIT***********/

	//Adjust System Clock
	RCC_voidAjustmentClockSys();

	//Enabling Peripherals
	#if RCC_SDIO_STATE		    ==    RCC_ENABLE
	SET_BIT(RCC->AHBENR,RCC_SDIO-RCC_AHB_OFFSET);
	#endif

	#if RCC_FSMC_STATE		    ==    RCC_ENABLE
	SET_BIT(RCC->AHBENR,RCC_FSMC-RCC_AHB_OFFSET);
	#endif
	
	#if RCC_CRC_STATE		    ==    RCC_ENABLE
	SET_BIT(RCC->AHBENR,RCC_CRC-RCC_AHB_OFFSET);
	#endif
	
	#if RCC_FLITF_STATE		    ==    RCC_ENABLE
	SET_BIT(RCC->AHBENR,RCC_FLITF-RCC_AHB_OFFSET);
	#endif
	
	#if RCC_SRAM_STATE		    ==    RCC_ENABLE
	SET_BIT(RCC->AHBENR,RCC_SRAM-RCC_AHB_OFFSET);
	#endif
	
	#if RCC_DMA2_STATE		    ==    RCC_ENABLE
	SET_BIT(RCC->AHBENR,RCC_DMA2-RCC_AHB_OFFSET);
	#endif
	
	#if RCC_DMA1_STATE		    ==    RCC_ENABLE
	SET_BIT(RCC->AHBENR,RCC_DMA1-RCC_AHB_OFFSET);
	#endif
	
	#if RCC_TIM11_STATE	    ==     RCC_ENABLE
	SET_BIT(RCC->APB2ENR,RCC_TIM11-RCC_APB2_OFFSET);
	#endif
	
	#if RCC_TIM10_STATE	    ==     RCC_ENABLE
	SET_BIT(RCC->APB2ENR,RCC_TIM10-RCC_APB2_OFFSET);
	#endif
	
	#if RCC_TIM9_STATE	        ==     RCC_ENABLE
	SET_BIT(RCC->APB2ENR,RCC_TIM9-RCC_APB2_OFFSET);
	#endif
	
	#if RCC_ADC3_STATE	        ==     RCC_ENABLE
	SET_BIT(RCC->APB2ENR,RCC_ADC3-RCC_APB2_OFFSET);	
	#endif
	
	#if RCC_USART1_STATE	    ==     RCC_ENABLE
	SET_BIT(RCC->APB2ENR,RCC_USART1-RCC_APB2_OFFSET);
	#endif
	
	#if RCC_TIM8_STATE	        ==     RCC_ENABLE
	SET_BIT(RCC->APB2ENR,RCC_TIM8-RCC_APB2_OFFSET);
	#endif
	
	#if RCC_SPI1_STATE	        ==     RCC_ENABLE
	SET_BIT(RCC->APB2ENR,RCC_SPI1-RCC_APB2_OFFSET);
	#endif
	
	#if RCC_TIM1_STATE	        ==     RCC_ENABLE
	SET_BIT(RCC->APB2ENR,RCC_TIM1-RCC_APB2_OFFSET);
	#endif
	
	#if RCC_ADC2_STATE	        ==     RCC_ENABLE
	SET_BIT(RCC->APB2ENR,RCC_ADC2-RCC_APB2_OFFSET);
	#endif
	
	#if RCC_ADC1_STATE	        ==     RCC_ENABLE
	SET_BIT(RCC->APB2ENR,RCC_ADC1-RCC_APB2_OFFSET);
	#endif
	
	#if RCC_IOPG_STATE	        ==     RCC_ENABLE
	SET_BIT(RCC->APB2ENR,RCC_IOPG-RCC_APB2_OFFSET);
	#endif
	
	#if RCC_IOPF_STATE	        ==     RCC_ENABLE
	SET_BIT(RCC->APB2ENR,RCC_IOPF-RCC_APB2_OFFSET);
	#endif
	
	#if RCC_IOPE_STATE	        ==     RCC_ENABLE
	SET_BIT(RCC->APB2ENR,RCC_IOPE-RCC_APB2_OFFSET);
	#endif
	
	#if RCC_IOPD_STATE	        ==     RCC_ENABLE
	SET_BIT(RCC->APB2ENR,RCC_IOPD-RCC_APB2_OFFSET);
	#endif
	
	#if RCC_IOPC_STATE	        ==     RCC_ENABLE
	SET_BIT(RCC->APB2ENR,RCC_IOPC-RCC_APB2_OFFSET);
	#endif
	
	#if RCC_IOPB_STATE	        ==     RCC_ENABLE
	SET_BIT(RCC->APB2ENR,RCC_IOPB-RCC_APB2_OFFSET);
	#endif
	
	#if RCC_IOPA_STATE	        ==     RCC_ENABLE
	SET_BIT(RCC->APB2ENR,RCC_IOPA-RCC_APB2_OFFSET);
	#endif
	
	#if   RCC_AFIO_STATE	        ==     RCC_ENABLE
	SET_BIT(RCC->APB2ENR,RCC_AFIO-RCC_APB2_OFFSET);
	#endif
	
	#if   RCC_DAC_STATE			==    RCC_ENABLE
	SET_BIT(RCC->APB1ENR,RCC_DAC	-RCC_APB1_OFFSET);
	#endif
	
	#if   RCC_PWR_STATE	        ==    RCC_ENABLE
	SET_BIT(RCC->APB1ENR,RCC_PWR	-RCC_APB1_OFFSET);
	#endif
	
	#if   RCC_BKP_STATE	        ==    RCC_ENABLE
	SET_BIT(RCC->APB1ENR,RCC_BKP	-RCC_APB1_OFFSET);
	#endif
	
	#if   RCC_CAN_STATE	        ==    RCC_ENABLE
	SET_BIT(RCC->APB1ENR,RCC_CAN	-RCC_APB1_OFFSET);
	#endif
	
	#if   RCC_USB_STATE	        ==    RCC_ENABLE
	SET_BIT(RCC->APB1ENR,RCC_USB	-RCC_APB1_OFFSET);
	#endif
	
	#if   RCC_I2C1_STATE	        ==    RCC_ENABLE
	SET_BIT(RCC->APB1ENR,RCC_I2C1-RCC_APB1_OFFSET);
	#endif
	
	#if   RCC_I2C2_STATE	        ==    RCC_ENABLE
	SET_BIT(RCC->APB1ENR,RCC_I2C2-RCC_APB1_OFFSET);
	#endif
	
	#if   RCC_UART5_STATE	    ==    RCC_ENABLE
	SET_BIT(RCC->APB1ENR,RCC_UART5-RCC_APB1_OFFSET);
	#endif
	
	#if   RCC_UART4_STATE	    ==    RCC_ENABLE
	SET_BIT(RCC->APB1ENR,RCC_UART4-RCC_APB1_OFFSET);
	#endif
	
	#if   RCC_USART3_STATE	    ==    RCC_ENABLE
	SET_BIT(RCC->APB1ENR,RCC_USART3-RCC_APB1_OFFSET);
	#endif
	#if   RCC_USART2_STATE	    ==    RCC_ENABLE
	SET_BIT(RCC->APB1ENR,RCC_USART2-RCC_APB1_OFFSET);
	#endif
	
	#if   RCC_SPI3_STATE	        ==    RCC_ENABLE
	SET_BIT(RCC->APB1ENR,RCC_SPI3-RCC_APB1_OFFSET);
	#endif
	
	#if   RCC_SPI2_STATE	        ==    RCC_ENABLE
	SET_BIT(RCC->APB1ENR,RCC_SPI2-RCC_APB1_OFFSET);
	#endif
	
	#if   RCC_WWDG_STATE	        ==    RCC_ENABLE
	SET_BIT(RCC->APB1ENR,RCC_WWDG-RCC_APB1_OFFSET);
	#endif
	
	#if   RCC_TIM14_STATE	    ==    RCC_ENABLE
	SET_BIT(RCC->APB1ENR,RCC_TIM14-RCC_APB1_OFFSET);
	#endif
	
	#if   RCC_TIM13_STATE	    ==    RCC_ENABLE
	SET_BIT(RCC->APB1ENR,RCC_TIM13-RCC_APB1_OFFSET);
	#endif
	
	#if   RCC_TIM12_STATE	    ==    RCC_ENABLE
	SET_BIT(RCC->APB1ENR,RCC_TIM12-RCC_APB1_OFFSET);
	#endif
	
	#if   RCC_TIM7_STATE	        ==    RCC_ENABLE
	SET_BIT(RCC->APB1ENR,RCC_TIM7-RCC_APB1_OFFSET);
	#endif
	
	#if   RCC_TIM6_STATE	        ==    RCC_ENABLE
	SET_BIT(RCC->APB1ENR,RCC_TIM6-RCC_APB1_OFFSET);
	#endif
	
	#if   RCC_TIM5_STATE	        ==    RCC_ENABLE
	SET_BIT(RCC->APB1ENR,RCC_TIM5-RCC_APB1_OFFSET);
	#endif
	
	#if   RCC_TIM4_STATE	        ==    RCC_ENABLE
	SET_BIT(RCC->APB1ENR,RCC_TIM4-RCC_APB1_OFFSET);
	#endif
	
	#if   RCC_TIM3_STATE	        ==    RCC_ENABLE
	SET_BIT(RCC->APB1ENR,RCC_TIM3-RCC_APB1_OFFSET);
	#endif
	
	#if   RCC_TIM2_STATE	        ==    RCC_ENABLE
	SET_BIT(RCC->APB1ENR,RCC_TIM2-RCC_APB1_OFFSET);
	#endif
}

//Disabling Clock on certain peripheral
u8 RCC_u8DisableClock(u8 Copy_u8PeripheralID)
{
	u8 Local_u8ErrorState = OK ;
	//AHB Bus
	if(Copy_u8PeripheralID <=AHB_END  && Copy_u8PeripheralID >=AHB_START)
		CLR_BIT(RCC->AHBENR,(Copy_u8PeripheralID-RCC_AHB_OFFSET));
	//APB1 Bus
	else if(Copy_u8PeripheralID <=APB1_END  && Copy_u8PeripheralID >=APB1_START)
		CLR_BIT(RCC->APB1ENR,(Copy_u8PeripheralID-RCC_APB1_OFFSET));
	//APB2 Bus
	else if (Copy_u8PeripheralID <=APB2_END  && Copy_u8PeripheralID >=APB2_START)
		CLR_BIT(RCC->APB2ENR,(Copy_u8PeripheralID-RCC_APB2_OFFSET));
	//Wrong Input
	else
		Local_u8ErrorState = NOK ;

	return Local_u8ErrorState;
}

//Changing Bus Mode
u8 RCC_u8ChangeModeBuses(u8 Copy_u8SysClock , u8 Copy_u8StateBus)
{
	u8 Local_u8StateError = OK;
	if(Copy_u8StateBus == RCC_ENABLE)
		switch (Copy_u8SysClock)
		{
			case RCC_CR_HSI:  SET_BIT(RCC->CR,Copy_u8SysClock);while (GET_BIT(RCC->CR,RCC_HSI_READY)==0);break;
			case RCC_CR_HSE:  SET_BIT(RCC->CR,Copy_u8SysClock);while (GET_BIT(RCC->CR,RCC_HSE_READY)==0);break;
			case RCC_CR_PLL:  SET_BIT(RCC->CR,Copy_u8SysClock);while (GET_BIT(RCC->CR,RCC_PLL_READY)==0);break;
			default: Local_u8StateError = NOK; break;	//Wrong Input
		}

	else if (Copy_u8StateBus == RCC_DISABLE)
		switch (Copy_u8SysClock)
		{
			case RCC_CR_HSI:  CLR_BIT(RCC->CR,Copy_u8SysClock);while (GET_BIT(RCC->CR,RCC_HSI_READY)!=0);break;
			case RCC_CR_HSE:  CLR_BIT(RCC->CR,Copy_u8SysClock);while (GET_BIT(RCC->CR,RCC_HSE_READY)!=0);break;
			case RCC_CR_PLL:  CLR_BIT(RCC->CR,Copy_u8SysClock);while (GET_BIT(RCC->CR,RCC_PLL_READY)!=0);break;
			default: Local_u8StateError = NOK;	break;	//Wrong Input
		}
	//Wrong Input
	else
		Local_u8StateError = NOK;

	return Local_u8StateError ;
}

//Adjusting System clock and calibrating error
void RCC_voidAjustmentClockSys ()
{
	u32 Local_u8RealValue ; // the value of HSICAL
	u8 Local_u8ChangeValue ;
	u8 Local_u8EditionValue ; // the value of the HSITRIM
	Local_u8RealValue = 255|(RCC->CR>>8); /***************EDIT***********/
	if (Local_u8RealValue != RCC_HSI_SPEED)
	{
		Local_u8ChangeValue = Local_u8RealValue - RCC_HSI_SPEED ;
		Local_u8ChangeValue /= 40 ;/***************EDIT***********/
		Local_u8EditionValue= (31 | (RCC->CR>>3)) + 40 ;/***************EDIT***********/
		RCC->CR |=(Local_u8EditionValue <<3);/***************EDIT***********/
	}
}
