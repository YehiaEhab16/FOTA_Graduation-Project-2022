/**********************************************************/
/* GRADUATION PROJECT : (FOTA)							  */
/* Version   : V01                                        */
/**********************************************************/
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

#define CAN_INITSTATUS_FAILED       ((uint32_t)0x00000000)  /* CAN initialization failed */
#define CAN_INITSTATUS_SUCCESS      ((uint32_t)0x00000001)  /* CAN initialization OK */

typedef struct  {
  u32 id;                 // message identifier
  u8  data[8];            // Data field
  u8  len;                // Length of data field in bytes
  u8  format;             // 0 - STANDARD, 1- EXTENDED IDENTIFIER
  u8  type;               // 0 - DATA FRAME, 1 - REMOTE FRAME
} CAN_msg;

typedef struct
{
  u8		                 Instance;  		 /* CAN peripheral  (0 or 1)       */

  CAN_InitTypeDef             Init;      		 /* CAN required parameters        */

  CanTxMsgTypeDef*            pTxMsg;    		 /* Pointer to transmit structure  */

  CAN_msg*            pRxMsg;    		 /* Pointer to reception structure */

}CAN_HandleTypeDef;


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

