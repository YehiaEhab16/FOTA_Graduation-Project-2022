/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):CAN 			 ***********************/
/***********************   DATA : 10-04-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef CAN_INTERFACE_H
#define CAN_INTERFACE_H

#define CAN             		   CAN_BASE

#define CAN_ID_STD  		            0    // Standard Id */
#define CAN_ID_EXT  		            1    // Extended Id */
#define DATA_FRAME       	            0
#define REMOTE_FRAME     	            1


/* Mailboxes definitions */
#define CAN_TXMAILBOX_0   			((u8)0x00)										//Mailbox1
#define CAN_TXMAILBOX_1   			((u8)0x01)										//Mailbox2
#define CAN_TXMAILBOX_2   			((u8)0x02)										//Mailbox3

#define CAN_TxStatus_Failed         ((u8)0x00) 										// Transmission failed
#define CAN_TxStatus_Ok             ((u8)0x01) 										// Transmission succeeded
#define CAN_TxStatus_Pending        ((u8)0x02) 										// Transmission pending
#define CAN_TXSTATUS_NOMAILBOX      ((u8)0x04) 										// No empty mailbox

/*INITIAL TYPE DEFINITIONS*/
/*MODE OPTIONS*/
#define CAN_MODE_NORMAL            ((u8)0x00) //0                                                // Normal mode
#define CAN_MODE_LOOPBACK          ((u8)0x01) //CAN_BTR_LBKM	                                         // Loopback mode
#define CAN_MODE_SILENT            ((u8)0x02) //CAN_BTR_SILM                                         // Silent mode
#define CAN_MODE_SILENT_LOOPBACK   ((u8)0x03) //CAN_BTR_SILM | CAN_BTR_LBKM                              // Loopback combined with silent mode

/*SJW OPTIONS*/
typedef enum {
	CAN_SJW_1TQ=0,     // 1 time quantum
	CAN_SJW_2TQ,       // 2 time quanta
	CAN_SJW_3TQ,       // 3 time quanta
	CAN_SJW_4TQ        // 4 time quanta
}ResynchJumpWidth;

/*BS1 OPTIONS*/
typedef enum {
	CAN_BS1_1TQ=0,     // 1 time quantum
	CAN_BS1_2TQ,       // 2 time quanta
	CAN_BS1_3TQ,       // 3 time quanta
	CAN_BS1_4TQ,       // 4 time quanta
	CAN_BS1_5TQ,       // 5 time quanta
	CAN_BS1_6TQ,       // 6 time quanta
	CAN_BS1_7TQ,       // 7 time quanta
	CAN_BS1_8TQ,       // 8 time quanta
	CAN_BS1_9TQ,       // 9 time quanta
	CAN_BS1_10TQ,      // 10 time quanta
	CAN_BS1_11TQ,      // 11 time quanta
	CAN_BS1_12TQ,      // 12 time quanta
	CAN_BS1_13TQ,      // 13 time quanta
	CAN_BS1_14TQ,      // 14 time quanta
	CAN_BS1_15TQ,      // 15 time quanta
	CAN_BS1_16TQ       // 16 time quanta
} TimeSegmentOne;


/*BS2 OPTIONS*/
typedef enum {
	CAN_BS2_1TQ=0,      // 1 time quantum
	CAN_BS2_2TQ,        // 2 time quanta
	CAN_BS2_3TQ,        // 3 time quanta
	CAN_BS2_4TQ,        // 4 time quanta
	CAN_BS2_5TQ,        // 5 time quanta
	CAN_BS2_6TQ,        // 6 time quanta
	CAN_BS2_7TQ,        // 7 time quanta
	CAN_BS2_8TQ         // 8 time quanta
} TimeSegmentTwo;

/*TTCM , ABOM , AWUM , NART , RFLM , TXFP OPTIONS*/
typedef enum {CAN_DISABLE = 0, CAN_ENABLE = 1} FunctionalState;

/***************************************************************************/
							/*CAN_Error_Code */
#define CAN_ERROR_NONE              ((u32)0x00)                             // No error
#define CAN_ERROR_EWG               ((u32)0x01)                             // EWG error
#define CAN_ERROR_EPV               ((u32)0x02)                             // EPV error
#define CAN_ERROR_BOF               ((u32)0x04)                             // BOF error
#define CAN_ERROR_STF               ((u32)0x08)                             // Stuff error
#define CAN_ERROR_FOR               ((u32)0x10)                             // Form error
#define CAN_ERROR_ACK               ((u32)0x20)                             // Acknowledgment error
#define CAN_ERROR_BR                ((u32)0x40)                             // Bit recessive
#define CAN_ERROR_BD                ((u32)0x80)                             // LEC dominant
#define CAN_ERROR_CRC               ((u32)0x100)                            // LEC transfer error


#define CAN_FILTERSCALE_16BIT           0 	// Two 16-bit filters
#define CAN_FILTERSCALE_32BIT           1 	// One 32-bit filter

#define CAN_FILTERMODE_IDMASK           0
#define CAN_FILTERMODE_IDLIST           1

#define CAN_FIFO_0         		  0
#define CAN_FIFO_1         		  1




#define CAN_RTR_DATA                ((u32)0x00000000)  // Data frame
#define CAN_RTR_REMOTE              ((u32)0x00000002)  // Remote frame


/* Error Interrupts */
#define CAN_IT_EWG                  ((u32)CAN_IER_EWGIE) // Error warning interrupt   */
#define CAN_IT_EPV                  ((u32)CAN_IER_EPVIE) // Error passive interrupt   */
#define CAN_IT_BOF                  ((u32)CAN_IER_BOFIE) // Bus-off interrupt         */
#define CAN_IT_LEC                  ((u32)CAN_IER_LECIE) // Last error code interrupt */
#define CAN_IT_ERR                  ((u32)CAN_IER_ERRIE) // Error Interrupt           */


#define CAN_TI0R_STID_BIT_POSITION    ((u32)21)  /* Position of LSB bits STID in register CAN_TI0R */
#define CAN_TI0R_EXID_BIT_POSITION    ((u32) 3)  /* Position of LSB bits EXID in register CAN_TI0R */
#define CAN_TDL0R_DATA0_BIT_POSITION  ((u32) 0)  /* Position of LSB bits DATA0 in register CAN_TDL0R */
#define CAN_TDL0R_DATA1_BIT_POSITION  ((u32) 8)  /* Position of LSB bits DATA1 in register CAN_TDL0R */
#define CAN_TDL0R_DATA2_BIT_POSITION  ((u32)16)  /* Position of LSB bits DATA2 in register CAN_TDL0R */
#define CAN_TDL0R_DATA3_BIT_POSITION  ((u32)24)  /* Position of LSB bits DATA3 in register CAN_TDL0R */


typedef struct  {
  u32 id;                 // message identifier
  u8  data[8];               // Data field
  u8  len;                // Length of data field in bytes
  u8  format;             // 0 - STANDARD, 1- EXTENDED IDENTIFIER
  u8  type;               // 0 - DATA FRAME, 1 - REMOTE FRAME
} CAN_msg;


/*
Description: CAN Init structure configuration
*/
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

  u8 CAN_FilterMode;        // specify the mode of filter "ID OR MASK"

  u8 CAN_FilterBankNumber;  //contain the filter bank number to specify

  u8 CAN_FilterBankScale;   // Specify the bank scale type " 16 or 32"

  u8 CAN_FilterFIFONumber; //contain the FIFO number to add bank to it

  FunctionalState CAN_FilterActivation; // specify the state of the filter "ENABLE OR DISABLE"

} CAN_FilterInit_t;


typedef struct
{
  u32 StdId;       /* Specifies the standard identifier.*/

  u32 ExtId;       /* Specifies the extended identifier.*/

  u32 IDE;         /* Specifies the type of identifier for the message that will be received.*/

  u32 RTR;         /* Specifies the type of frame for the received message.*/

  u32 DLC;         /* Specifies the length of the frame that will be received.*/

  u8 Data[8];      /* Contains the data to be received. */

  u32 FMI;         /* Specifies the index of the filter the message stored in the mailbox passes through.*/

  u32 FIFONumber;  /* Specifies the receive FIFO number. */


}CanRxMsgTypeDef;

/**
 * @def function to initialize CAN
 * @param hcan struct contains info about CAN
 */
void CAN_voidInit(CAN_Init_t* hcan);

/**
 * @def function for transmission
 * @param CAN message struct contains info about message
 * @return Error Flag
 */
u8 CAN_u8Transmit(CAN_msg* pTxMsg);

/**
 * @def function for receiving
 * @param msg struct contains info about message
 * @param Copy_u8FIFOIndex FIFo index
 */
void CAN_voidReceive(CAN_msg *msg, u8 Copy_u8FIFOIndex);

/**
 * @def function to set filter
 * @param CAN_FilterInitStruct struct contains info about filter
 */
void CAN_VoidFilterSet(CAN_FilterInit_t* CAN_FilterInitStruct);

void CAN_VoidEnableFifo1Int (void);
void CAN_VoidDisableFifo1Int(void);
void CAN_VoidEnableFifo0Int (void);
void CAN_VoidDisableFifo0Int(void);

/**
 * @def function to set callback function
 */
void CAN_voidCallBackFunc(u8 Copy_u8FifoNumber, void(*pv_CallBack)(void));

#endif
