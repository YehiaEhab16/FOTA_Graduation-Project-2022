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


/*channel selected for convers	ion*/
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



typedef enum
{
   CHANNEL_0,
   CHANNEL_1,
   CHANNEL_2,
   CHANNEL_3,
   CHANNEL_4,
   CHANNEL_5,
   CHANNEL_6,
   CHANNEL_7,
   CHANNEL_8,
   CHANNEL_9,
   CHANNEL_10,
   CHANNEL_11,
   CHANNEL_12,
   CHANNEL_13,
   CHANNEL_14,
   CHANNEL_15,
   CHANNEL_16,
   CHANNEL_17
}ADC_Channels;


typedef enum
{
	_1_AND_HALF_CYCLE = 0,
   _7_AND_HALF_CYCLE,
   _13_AND_HALF_CYCLE,
   _28_AND_HALF_CYCLE,
   _41_AND_HALF_CYCLE,
   _55_AND_HALF_CYCLE,
   _71_AND_HALF_CYCLE,
   _239_AND_HALF_CYCLE
}ADCSampleTime_t;


/**
 * @def function to initialize ADC
 */
void ADC_voidInit(void);
void ADC_voidStartConv(u16 *Copy_u32DATA,u8 Copy_u8Channel);
void ADC_voidSamplingTime(ADC_Channels Copy_u8Channel, ADCSampleTime_t Copy_u8SamplingTime);
#endif
