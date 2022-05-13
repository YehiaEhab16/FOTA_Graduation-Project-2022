/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer : MCAL                  ***********************/
/***********************   SWC (DRIVER):ADC				 ***********************/
/***********************   DATA : 1-4-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

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
	
    /*CONVERSION MODE */
	#if ADC_CONV_MODE	        ==     Single
	CLR    (ADC1 -> CR2 ,ADC_CR2_CONT);
	#endif
	
	#if ADC_CONV_MODE	        ==     CONT
	SET_BIT(ADC1 -> CR2 ,ADC_CR2_CONT);
	#endif
	
	#if ADC_CONV_MODE	        ==     DISCON
	SET_BIT(ADC1 -> CR1 ,ADC_CR1_DISCEN);
	#endif
	
	
	/* Alignment of the Data
	   CLR: Right Alignment
	   SET: Left Alignmen
	*/
	#if ADC_ALIG_STATE	        ==     Right
	CLR_BIT(ADC1 -> CR2 , ADC_CR2_ALIGN);
	#endif
	
	#if ADC_ALIG_STATE	        ==     Left
	SET_BIT(ADC1 -> CR2 , ADC_CR2_ALIGN);
	#endif
	
	/* Enable interrupt for injected channels */
	SET_BIT(ADC1 -> CR1 , ADC_CR1_JEOCIE);

    /* Enable interrupt for regular channels  */
	SET_BIT(ADC1 -> CR1 , ADC_CR1_EOCIE);
	
    /* Start conversion of regular channels */
	SET_BIT(ADC1 -> CR2 ,ADC_CR2_SWSTART);
  

}
void ADC_VidStartConv(u32 Copy_u32DATA,u32 Copy_u32JDATA){
	if(((ADC1->SR) << ADC_SR_EOC) == 1){
		SET_BIT(ADC1 -> CR2 ,ADC_CR2_SWSTART);
		while (GET_BIT(ADC1->SR, ADC_SR_STRT) == 0);
		while (GET_BIT(ADC1->SR, ADC_SR_EOC)  == 0);
		CLR_BIT(ADC1 -> CR2 , ADC_SR_EOC);
		while (GET_BIT(ADC1->SR, ADC_SR_EOC) == 0);
		Copy_u32DATA = (ADC1->DR&0x0000FFFF);
	}
		if(((ADC1->SR) << ADC_SR_JEOC) == 1){
		SET_BIT(ADC1 -> CR2 ,ADC_CR2_SWSTART);
		while (GET_BIT(ADC1->SR, ADC_SR_JSTRT) == 0);
		while (GET_BIT(ADC1->SR, ADC_SR_JEOC)  == 0);
		CLR_BIT(ADC1 -> CR2 , ADC_SR_JEOC);
		while (GET_BIT(ADC1->SR, ADC_SR_JEOC) == 0);
		Copy_u32JDATA  = (ADC1 -> JDR1 & 0x0000FFFF);
	}

}
