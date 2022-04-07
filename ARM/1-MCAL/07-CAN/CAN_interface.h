/**********************************************************/
/* GRADUATION PROJECT : (FOTA)							  */
/* Version   : V01                                        */
/**********************************************************/
#ifndef CAN_INTERFACE_H
#define CAN_INTERFACE_H

#include "STD_TYPES.h"
#include "CAN_private.h"
#include "CAN_config.h"

#define CAN1                ((CAN_t *)CAN_BASE)

#define CAN_ID_STD  		            u32(0x00000000)    // Standard Id */
#define CAN_ID_EXT  		            u32(0x00000004)    // Extended Id */
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
#define CAN_SJW_1TQ                0     					                         // 1 time quantum
#define CAN_SJW_2TQ                BTR_SJW_0 				                         // 2 time quantum
#define CAN_SJW_3TQ                BTR_SJW_1 				                         // 3 time quantum
#define CAN_SJW_4TQ                BTR_SJW    				                         // 4 time quantum

/*BS1 OPTIONS*/
#define CAN_BS1_1TQ                0                                                // 1 time quantum
#define CAN_BS1_2TQ                BTR_TS1_0                                        // 2 time quantum
#define CAN_BS1_3TQ                BTR_TS1_1                                        // 3 time quantum
#define CAN_BS1_4TQ                BTR_TS1_1 | BTR_TS1_0                            // 4 time quantum
#define CAN_BS1_5TQ                BTR_TS1_2                                        // 5 time quantum
#define CAN_BS1_6TQ                BTR_TS1_2 | BTR_TS1_0                            // 6 time quantum
#define CAN_BS1_7TQ                BTR_TS1_2 | BTR_TS1_1                            // 7 time quantum
#define CAN_BS1_8TQ                BTR_TS1_2 | BTR_TS1_1 | CAN_BTR_TS1_0            // 8 time quantum
#define CAN_BS1_9TQ                BTR_TS1_3                                        // 9 time quantum
#define CAN_BS1_10TQ               BTR_TS1_3 | BTR_TS1_0                            // 10 time quantum
#define CAN_BS1_11TQ               BTR_TS1_3 | BTR_TS1_1                            // 11 time quantum
#define CAN_BS1_12TQ               BTR_TS1_3 | BTR_TS1_1 | CAN_BTR_TS1_0            // 12 time quantum
#define CAN_BS1_13TQ               BTR_TS1_3 | BTR_TS1_2                            // 13 time quantum
#define CAN_BS1_14TQ               BTR_TS1_3 | BTR_TS1_2 | CAN_BTR_TS1_0            // 14 time quantum
#define CAN_BS1_15TQ               BTR_TS1_3 | BTR_TS1_2 | CAN_BTR_TS1_1            // 15 time quantum
#define CAN_BS1_16TQ               BTR_TS1									        // 16 time quantum

/*BS2 OPTIONS*/
#define CAN_BS2_1TQ                0                                                 // 1 time quantum
#define CAN_BS2_2TQ                BTR_TS2_0                                         // 2 time quantum
#define CAN_BS2_3TQ                BTR_TS2_1                                         // 3 time quantum
#define CAN_BS2_4TQ                BTR_TS2_1 | BTR_TS2_0                             // 4 time quantum
#define CAN_BS2_5TQ                BTR_TS2_2                                         // 5 time quantum
#define CAN_BS2_6TQ                BTR_TS2_2 | BTR_TS2_0                             // 6 time quantum
#define CAN_BS2_7TQ                BTR_TS2_2 | BTR_TS2_1                             // 7 time quantum
#define CAN_BS2_8TQ                BTR_TS2                                           // 8 time quantum


/*TTCM , ABOM , AWUM , NART , RFLM , TXFP OPTIONS*/
#define ENABLE                1
#define DISABLE               0

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
  u8  data[8];            // Data field
  u8  len;                // Length of data field in bytes
  u8  format;             // 0 - STANDARD, 1- EXTENDED IDENTIFIER
  u8  type;               // 0 - DATA FRAME, 1 - REMOTE FRAME
} CAN_msg;

typedef struct
{
  CAN_t*		         Instance;  		 /* CAN peripheral  (0 or 1)       */

  CAN_Init_t             Init;      		 /* CAN required parameters        */

  CAN_msg*            pTxMsg;    		 /* Pointer to transmit structure  */

  CAN_msg*            pRxMsg;    		 /* Pointer to reception structure */

}CAN_HandleTypeDef;

extern CAN_msg CAN_TXmsg;
extern CAN_msg CAN_RXmsg;
extern u8 CAN_msgReceived;


void CAN_VoidInit(CAN_HandleTypeDef* hcan);
u8 CAN_u8Transmit(CAN_HandleTypeDef* hcan);
//void CAN_voidTransmit_IT(CAN_HandleTypeDef* hcan);
void CAN_voidReceive( CAN_msg *msg, u8 Copy_u8FIFOIndex);
void CAN_VoidFilterSet(CAN_FilterInit_t* CAN_FilterInitStruct);
u8 CAN_VoidTransmit(CAN_HandleTypeDef* hcan);


#endif
