/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer : MCAL                  ***********************/
/***********************   SWC (DRIVER):ADC				 ***********************/
/***********************   DATA : 1-4-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_


/*CR1 Register**/
#define     ADC_CR1_AWDEN            23
#define     ADC_CR1_DISCEN           11
#define     ADC_CR1_SCAN             8
#define     ADC_CR1_JAWDEN           22
#define     ADC_CR1_EOCIE			 5
#define     ADC_CR1_JEOCIE			 7

/*CR2 Register*/
#define     ADC_CR2_ADON              0
#define     ADC_CR2_CONT              1
#define     ADC_CR2_CAL       	      2
#define     ADC_CR2_SWSTART           22
#define     ADC_CR2_DMA			      8

#define     ADC_CR2_ALIGN             11
#define     ADC_CR2_JEXTSEL_0         12
#define     ADC_CR2_JEXTSEL_1         13
#define     ADC_CR2_JEXTSEL_2         14
#define     ADC_CR2_JEXTTRIG          15

#define     ADC_CR2_EXTTRIG			  20



/*SR  Register*/


#define     ADC_SR_STRT               4
#define     ADC_SR_JSTRT              3
#define     ADC_SR_JEOC               2
#define     ADC_SR_EOC                1
#define     ADC_SR_AWD				  0








#endif
