/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :SERVICE                ***********************/
/***********************   SWC (DRIVER):COM 			 ***********************/
/***********************   DATE : 8-7-2022	 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef COM_CONFIG_H_
#define COM_CONFIG_H_


#define COM_PORT		GPIO_PORTA

#define COM_DIAG_OUT	GPIO_PIN_7	//Output (Initial 1)
#define COM_UPDATE_OUT	GPIO_PIN_3	//Output (Initial 1)

#define COM_DIAG_IN		GPIO_PIN_1	//Input
#define COM_UPDATE_IN	GPIO_PIN_0 	//Input

#define COM_DIAG_DATA0	GPIO_PIN_4	//Output (Initial 1)
#define COM_DIAG_DATA1	GPIO_PIN_5	//Output (Initial 1)
#define COM_DIAG_DATA2	GPIO_PIN_6	//Output (Initial 1)

#define COM_RES_FLAG	GPIO_PIN_2	//Input

#define CMO_DELAY_TIME	250

#endif
