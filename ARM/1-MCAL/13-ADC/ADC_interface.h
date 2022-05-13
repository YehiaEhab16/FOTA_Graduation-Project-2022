/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer : MCAL                  ***********************/
/***********************   SWC (DRIVER):ADC				 ***********************/
/***********************   DATA : 1-4-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_



#define ADC_ENABLE			1
#define ADC_DISABLE 	   	0

/*conversion mode*/

#define Single              0
#define CONT                1
#define DISCON              2
/*Alignment state*/
#define Right				1
#define  Left               0


/*channel selected for conversion*/
#define NOCHANNEL		((u32)0x00000000)
#define CHANNEL0		((u32)0x00000000)
#define CHANNEL1		((u32)0x00000001)
#define CHANNEL2		((u32)0x00000002)
#define CHANNEL3		((u32)0x00000003)
#define CHANNEL4		((u32)0x00000004)
#define CHANNEL5		((u32)0x00000005)
#define CHANNEL6		((u32)0x00000006)
#define CHANNEL7		((u32)0x00000007)
#define CHANNEL8		((u32)0x00000008)
#define CHANNEL9		((u32)0x00000009)
#define CHANNEL10		((u32)0x0000000A)
#define CHANNEL11		((u32)0x0000000B)
#define CHANNEL12		((u32)0x0000000C)
#define CHANNEL13		((u32)0x0000000D)
#define CHANNEL14		((u32)0x0000000E)
#define CHANNEL15		((u32)0x0000000F)
#define CHANNEL16		((u32)0x00000010)
#define CHANNEL17		((u32)0x00000011)





/**
 * @def function to initialize ADC
 */
void ADC_voidInit(void);
void ADC_VidStartConv(u32 Copy_u32DATA,u32 Copy_u32JDATA);
#endif
