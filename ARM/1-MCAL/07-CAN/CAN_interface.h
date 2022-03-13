
#ifndef CAN_H
#define CAN_H

#include "STD_TYPES.h"
#include "CAN_private.h"
#include "CAN_config.h"


#define CAN_ID_STD  		            0
#define CAN_ID_EXT  		            1
#define DATA_FRAME       	            0
#define REMOTE_FRAME     	            1

#define CAN_MODE_LOOPBACK               CAN_BTR_LBKM
#define CAN_MODE_SILENT                 CAN_BTR_SILM
#define CAN_MODE_NORMAL                 CAN_BTR_LBKM & CAN_BTR_SILM


#define CAN_TXMAILBOX_0		            0
#define CAN_TXMAILBOX_1		            1
#define CAN_TXMAILBOX_2		            2

#define CAN_FILTERSCALE_16BIT           0 	// Two 16-bit filters
#define CAN_FILTERSCALE_32BIT           1 	// One 32-bit filter

#define CAN_FILTERMODE_IDMASK           0
#define CAN_FILTERMODE_IDLIST           1

#define CAN_FIFO_0         		  0
#define CAN_FIFO_1         		  1


typedef struct  {
  u32 id;                 // message identifier
  u8  data[8];            // Data field
  u8  len;                // Length of data field in bytes
  u8  format;             // 0 - STANDARD, 1- EXTENDED IDENTIFIER
  u8  type;               // 0 - DATA FRAME, 1 - REMOTE FRAME
} CAN_msg;

void CAN_voidInit(u8 Copy_u8CAN, u32 Copy_u32Mode);
void CAN_voidTransmit(u8 Copy_u8CAN, u32 Copy_u32ID, u8 Copy_u8IDType, u8 Copy_u8FrameType, u8 *m, u8 mailIndex);
void CAN_voidFiltersInit(u8 Copy_u8CAN, u32 Copy_u32ID);
void CAN_voidReceive(u8 Copy_u8CAN, CAN_msg *msg, u8 Copy_u8FIFOIndex);
void CAN_VoidFilterSet(u8 Copy_u8CAN,CAN_FilterInitTypeDef* CAN_FilterInitStruct);

#endif
