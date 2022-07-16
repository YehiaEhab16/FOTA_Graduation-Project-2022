/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer : MCAL                  ***********************/
/***********************   SWC (DRIVER):ADC				 ***********************/
/***********************   DATA : 1-4-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../../6-Library/STD_TYPES.h"
#include "../../6-Library/BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_config.h"
#include "ADC_private.h"
#include "ADC_register.h"

//Initializing ADC
void ADC_voidInit(void)
{
//NOTE:we need to enable rcc&gpio(no pull up no pull down)
	/*Set External trigger */
	SET_BIT((ADC1 -> CR2 ),ADC_CR2_EXTTRIG);

	/* Enable ADC ,in this case single conversion mode is set*/
	SET_BIT(ADC1 -> CR2 , ADC_CR2_ADON);

	//calibration
	SET_BIT(ADC1 -> CR2 , ADC_CR2_CAL);

	for (int i = 0; i < 10000; i++);

    /*CONVERSION MODE */
	#if ADC_CONV_MODE	        ==     Single
	CLR_BIT(ADC1 -> CR2 ,ADC_CR2_CONT);

	#elif ADC_CONV_MODE	        ==     CONT
	SET_BIT(ADC1 -> CR2 ,ADC_CR2_CONT);


	#else
	//set defaut as DISCON
	SET_BIT(ADC1 -> CR1 ,ADC_CR1_DISCEN);
	#endif


	/* Alignment of the Data
	   CLR: Right Alignment
	   SET: Left Alignment
	*/
	#if ADC_ALIG_STATE	        ==     Right
	CLR_BIT(ADC1 -> CR2 , ADC_CR2_ALIGN);
	
	#elif ADC_ALIG_STATE	        ==     Left
	SET_BIT(ADC1 -> CR2 , ADC_CR2_ALIGN);
	#else  //set right as default
	CLR_BIT(ADC1 -> CR2 , ADC_CR2_ALIGN);
	#endif

    /* Enable interrupt for regular channels  */
	SET_BIT(ADC1 -> CR1 , ADC_CR1_EOCIE);

    /* Start conversion of regular channels */
	SET_BIT(ADC1 -> CR2 ,ADC_CR2_SWSTART);
}

/**
Channel Options
CHANNEL0 -> CHANNEL17
*/
void ADC_voidSamplingTime(ADC_Channels Copy_u8Channel, ADCSampleTime_t Copy_u8SamplingTime)
{
	   if(Copy_u8Channel <= 6)
	   {
	      ADC1->SMPR2 |= (Copy_u8SamplingTime) << (Copy_u8Channel * 3);
	   }
	   else if(Copy_u8Channel <= 17)
	   {
		   /*to start the register from 0 as counting of SMP starts from 10*/
	      Copy_u8Channel -= 10;
	      ADC1->SMPR1 |= (Copy_u8SamplingTime) << (Copy_u8Channel * 3);
	   }
}
void ADC_VidStartConv(u16 *Copy_u32DATA,u8 Copy_u8Channel)
{
	CLR_BIT(ADC1 -> CR2 , ADC_CR2_ADON);

	ADC1->SQR3  = Copy_u8Channel ;

	SET_BIT(ADC1 -> CR2 , ADC_CR2_ADON);
	
	for (int i = 0; i < 10000; i++);

	SET_BIT(ADC1 -> CR2 , ADC_CR2_ADON);

	while (GET_BIT(ADC1->SR, ADC_SR_EOC)  == 0);

	*Copy_u32DATA = (u16)(ADC1->DR);

	CLR_BIT(ADC1 -> SR , ADC_SR_EOC);
	CLR_BIT(ADC1 -> SR , ADC_SR_STRT);

}

