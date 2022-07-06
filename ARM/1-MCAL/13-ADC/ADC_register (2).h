/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer : MCAL                  ***********************/
/***********************   SWC (DRIVER):ADC				 ***********************/
/***********************   DATA : 1-4-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef ADC_REGISTER_H_
#define ADC_REGISTER_H_

//ADC Registers
typedef struct
{				
  volatile u32 SR;   
  volatile u32 CR1;  
  volatile u32 CR2;  
  volatile u32 SMPR1;
  volatile u32 SMPR2;
  volatile u32 JOFR1;
  volatile u32 JOFR2;
  volatile u32 JOFR3;
  volatile u32 JOFR4;
  volatile u32 HTR;   
  volatile u32 LTR;  
  volatile u32 SQR1;  
  volatile u32 SQR2;
  volatile u32 SQR3;
  volatile u32 JSQR;
  volatile u32 JDR1;
  volatile u32 JDR2;
  volatile u32 JDR3;      
  volatile u32 JDR4;
  volatile u32 DR;
}ADC_t;


//ADC Base Addresses
#define ADC1						((volatile ADC_t *)0x40012400)
#define ADC2						((volatile ADC_t *)0x40012800)
#define ADC3						((volatile ADC_t *)0x40013C00)


#endif
