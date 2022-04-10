/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):CAN 			 ***********************/
/***********************   DATA : 10-04-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef CAN_CONFIG_H
#define CAN_CONFIG_H


//Description: CAN Init structure configuration
typedef struct
{
  u16 CAN_Prescaler;  /* Specifies the length of a time quantum.
                          This parameter must be a number between Min_Data = 1 and Max_Data = 1024. */

  u8  CAN_MODE;        /* Specifies the CAN operating mode.*/

  u8  CAN_SJW;         /* Specifies the maximum number of time quanta */

  u8  CAN_BS1;         /* Specifies the number of time quanta in Bit Segment 1.*/

  u8  CAN_BS2;         /* Specifies the number of time quanta in Bit Segment 2.*/

  u32 CAN_TTCM;       /* Enable or disable the time triggered communication mode.
                         This parameter can be set to ENABLE or DISABLE. */

  u32 CAN_ABOM;       /* Enable or disable the automatic bus-off management.
                         This parameter can be set to ENABLE or DISABLE. */

  u32 CAN_AWUM;       /* Enable or disable the automatic wake-up mode.
                         This parameter can be set to ENABLE or DISABLE. */

  u32 CAN_NART;       /* Enable or disable the non-automatic retransmission mode.
                         This parameter can be set to ENABLE or DISABLE. */

  u32 CAN_RFLM;       /* Enable or disable the Receive FIFO Locked mode.
                         This parameter can be set to ENABLE or DISABLE. */

  u32 CAN_TXFP;       /* Enable or disable the transmit FIFO priority.
                          This parameter can be set to ENABLE or DISABLE. */
}CAN_Init_t;

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

}CAN_FilterInit_t;


#endif
