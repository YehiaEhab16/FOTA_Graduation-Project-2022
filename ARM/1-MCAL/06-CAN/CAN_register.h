/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):CAN 			 ***********************/
/***********************   DATA : 10-04-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/
#ifndef CAN_REGISTER_H
#define CAN_REGISTER_H

//CAN Base Address
#define 	CAN_BASE                 (*((volatile CAN_t*)0x40006400))

//CAN Registers
typedef struct
{
  volatile u32 TIR;
  volatile u32 TDTR;
  volatile u32 TDLR;
  volatile u32 TDHR;
}CAN_TxMailBox_t;

typedef struct
{
  volatile u32 RIR;
  volatile u32 RDTR;
  volatile u32 RDLR;
  volatile u32 RDHR;
}CAN_FIFOMailBox_t;

typedef struct
{
  volatile u32 FR1;
  volatile u32 FR2;
}CAN_FilterRegister_t;



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
  CAN_FilterRegister_t sFilterRegister[28];
}CAN_t;


#endif
