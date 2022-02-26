
#ifndef CAN_PRIVATE_H
#define CAN_PRIVATE_H

#define CAN1_BASE                       ((u32)0x40006400)
#define CAN2_BASE                       ((u32)0x40006800)

typedef struct
{
  volatile u32 TIR;
  volatile u32 TDTR;
  volatile u32 TDLR;
  volatile u32 TDHR;
} CAN_TxMailBox_t;

typedef struct
{
  volatile u32 RIR;
  volatile u32 RDTR;
  volatile u32 RDLR;
  volatile u32 RDHR;
} CAN_FIFOMailBox_t;

typedef struct
{
  volatile u32 FR1;
  volatile u32 FR2;
} CAN_FilterRegister_TypeDef;

typedef struct
{
  volatile u32 MCR;
  volatile u32 MSR;
  volatile u32 TSR;
  volatile u32 RF0R;
  volatile u32 RF1R;
  volatile u32 IER;
  volatile u32 ESR;
  volatile u32 BTR;
       	   u32 RESERVED0[88];
  CAN_TxMailBox_t      sTxMailBox[3];
  CAN_FIFOMailBox_t    sFIFOMailBox[2];
       	   u32 RESERVED1[12];
  volatile u32 FMR;
  volatile u32 FM1R;
  volatile u32 RESERVED2;
  volatile u32 FS1R;
  volatile u32 RESERVED3;
  volatile u32 FFA1R;
  volatile u32 RESERVED4;
  volatile u32 FA1R;
       	   u32 RESERVED5[8];
  CAN_FilterRegister_TypeDef sFilterRegister[28];
} CAN_t;

#define RELEASE                   (1<<5)

/*----------------- MCR bits -------------------*/
#define CAN_MCR_INRQ		((u16)0x0001)
#define CAN_MCR_SLEEP		((u16)0x0002)
#define CAN_MCR_TXFP        ((u16)0x0004)
#define CAN_MCR_RFLM        ((u16)0x0008)
#define CAN_MCR_NART		((u16)0x0010)
#define CAN_MCR_ABOM		((u16)0x0040)

/*----------------- TSR bits -------------------*/
#define  CAN_TSR_TME0       ((u32)0x04000000)
#define  CAN_TSR_TME1       ((u32)0x08000000)
#define  CAN_TSR_TME2       ((u32)0x10000000)

/*----------------- BTR bits -------------------*/
#define  CAN_BTR_LBKM       ((u32)0x40000000)
#define  CAN_BTR_SILM       ((u32)0x80000000)

#endif
