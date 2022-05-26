/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :HAL                    ***********************/
/***********************   SWC (DRIVER):DC motor 		 ***********************/
/***********************   DATA : 24-5-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

/* Preprocessor file guard 
   Macros and prototypes   */
#ifndef DCMOTOR_INTERFACE_H_
#define DCMOTOR_INTERFACE_H_

#define  PWMPORT 		GPIO_PORTA  //for example
#define  DR1_PIN        GPIO_PIN_0
#define  DR2_PIN        GPIO_PIN_1
#define  ENC_PIN 		GPIO_PIN_3 
#define  HIGH               1
#define  LOW                0


/**

 */
void setMotor(u8 dir);
/**

 */
void DCMOTOR_vidReadEncoder();
/**

 */
void DCMOTOR_vidIRQHandler(void);
/**

 */
u8 DCMOTOR_u8CallBackFunc(void(*pv_CallBack)(void));



#endif