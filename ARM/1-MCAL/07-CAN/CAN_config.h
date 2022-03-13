#ifndef CAN_CONFIG_H
#define CAN_CONFIG_H

/***********************************************************************************/
                      /*** HW Macros***/
/***********************************************************************************/

#define MAX_CONTROLLERS_NUMBER    (2U)
#define USED_CONTROLLERS_NUMBER   (1U)
#define USED_FILTERS_NUMBERS      (2U)



/*
Description: CAN Init structure configuration
*/

typedef struct{
  u16 CAN_Prescaler;  //describe time quantum length

  u8 CAN_MODE;     // describe the operation mode of can driver

  u8 CAN_SJW;  // describe max number of time quantum

  u8 CAN_BS1;   // describe time quantum in segment 1

  u8 CAN_BS2;   // describe time quantum in seqment 2



} CAN_InitTypeDef;

/*
Description: CAN filter init structure definition
*/
typedef struct
{
  u32 CAN_FilterId;         // contain ID of filter bank

  u32 CAN_FilterMaskId;     //contain Mask of filter bank

  u8 CAN_FilterMode;        // specifiy the mode of filter "ID OR MASK"

  u8 CAN_FilterBankNumber;  //contain the filter bank numer to specifiy

  u8 CAN_FilterBankScale;   // Specify the bank scale type " 16 or 32"

  u8 CAN_FilterFIFONumber; //contain the FIFO number to add bank to it

  FunctionalState CAN_FilterActivation; // specify the state of the filter "ENABLE OR DISABLE"

} CAN_FilterInitTypeDef;


#endif

















