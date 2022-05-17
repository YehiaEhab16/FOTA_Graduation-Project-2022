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


#include "GPIO_interface.h"

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
	CLR    (ADC1 -> CR2 ,ADC_CR2_CONT);
	
	#elif ADC_CONV_MODE	        ==     CONT
	SET_BIT(ADC1 -> CR2 ,ADC_CR2_CONT);

	
	#else
	//set defaut as DISCON
	SET_BIT(ADC1 -> CR1 ,ADC_CR1_DISCEN);
	#endif
	
	
	/* Alignment of the Data
	   CLR: Right Alignment
	   SET: Left Alignmen
	*/
	#if ADC_ALIG_STATE	        ==     Right
	CLR_BIT(ADC1 -> CR2 , ADC_CR2_ALIGN);
	
	#elif ADC_ALIG_STATE	        ==     Left
	SET_BIT(ADC1 -> CR2 , ADC_CR2_ALIGN);
	#else  //set right as default
	CLR_BIT(ADC1 -> CR2 , ADC_CR2_ALIGN);
	#endif
	
//	/* Enable interrupt for injected channels */
//	SET_BIT(ADC1 -> CR1 , ADC_CR1_JEOCIE);

    /* Enable interrupt for regular channels  */
	SET_BIT(ADC1 -> CR1 , ADC_CR1_EOCIE);
	
    /* Start conversion of regular channels */
	SET_BIT(ADC1 -> CR2 ,ADC_CR2_SWSTART);
  

}
/*CHOOSE THE CHANNEL
//CHANNEL_0,
//CHANNEL_1,
//CHANNEL_2,
//CHANNEL_3,
//CHANNEL_4,
//CHANNEL_5,
//CHANNEL_6,
//CHANNEL_7,
//CHANNEL_8,
//CHANNEL_9,
//CHANNEL_10,
//CHANNEL_11,
//CHANNEL_12,
//CHANNEL_13,
//CHANNEL_14,
//CHANNEL_15,
//CHANNEL_16,
//CHANNEL_17*/
void ADC_voidSamplingTime(ADC_Channels Copy_u8Channel, ADCSampleTime_t Copy_u8SamplingTime){
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
	   else
	   {
	   }
}
void ADC_VidStartConv(u32 *Copy_u32DATA,u32 *Copy_u32JDATA){

	 ADC1->SQR1  |= ( (ADC_SQ13)|(ADC_SQ14<<5)|(ADC_SQ15<<10)|(ADC_SQ16<<15)|(SQ_L<<20));
	 ADC1->SQR2  |= ( (ADC_SQ7) |(ADC_SQ8<<5) |(ADC_SQ9<<10) |(ADC_SQ10<<15)|(ADC_SQ11<<20)|(ADC_SQ12<<25));
	 ADC1->SQR3  |= ( (ADC_SQ1) |(ADC_SQ2<<5) |(ADC_SQ3<<10) |(ADC_SQ4<<15) |(ADC_SQ5<<20)|(ADC_SQ6<<25)  );


	SET_BIT(ADC1 -> CR2 , ADC_CR2_ADON);
	SET_BIT(ADC1 -> CR2 ,ADC_CR2_SWSTART);


		while (GET_BIT(ADC1->SR, ADC_SR_STRT) == 0);
		GPIO_u8SetPinValue (GPIO_PORTA, GPIO_PIN_7,GPIO_PIN_HIGH);
		for(int i=0;i<500000;i++)
		while (GET_BIT(ADC1->SR, ADC_SR_EOC)  == 0);

		*Copy_u32DATA = (ADC1->DR)&(0x0FFF);

		CLR_BIT(ADC1 -> SR , ADC_SR_EOC);
		CLR_BIT(ADC1 -> SR , ADC_SR_STRT);
//		if(Copy_u32DATA !=0){
//			GPIO_u8SetPinValue (GPIO_PORTA, GPIO_PIN_7,GPIO_PIN_LOW);
//			for(int i=0;i<500000;i++);
//		}
//		if(((ADC1->SR) << ADC_SR_JEOC) == 1){
//		SET_BIT(ADC1 -> CR2 ,ADC_CR2_SWSTART);
//		while (GET_BIT(ADC1->SR, ADC_SR_JSTRT) == 0);
//		while (GET_BIT(ADC1->SR, ADC_SR_JEOC)  == 0);
//
//		Copy_u32JDATA  = (ADC1 -> JDR1 & 0x0000FFFF);
//		CLR_BIT(ADC1 -> CR2 , ADC_SR_JEOC);
//		CLR_BIT(ADC1 -> SR , ADC_SR_JSTRT);
//	}

}
