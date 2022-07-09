/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):CAN 			 ***********************/
/***********************   DATA : 10-04-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "../../6-Library/STD_TYPES.h"

#include "CAN_interface.h"

CAN_Init_t CAN_InitStruct = {12, CAN_MODE_NORMAL, CAN_SJW_1TQ, CAN_BS1_2TQ, CAN_BS2_3TQ, CAN_DISABLE, CAN_DISABLE, CAN_DISABLE, CAN_ENABLE, CAN_DISABLE, CAN_ENABLE};

/* Main ECU Filters */

CAN_FilterInit_t CAN_FilterUserResponse = {0x06000000, 0x06000000, CAN_FILTERMODE_IDLIST, 1, CAN_FILTERSCALE_32BIT, CAN_FIFO_0, CAN_ENABLE}; // ID = 0X46

/* In case of one app ECU */
CAN_FilterInit_t CAN_FilterAppAck = {0x06a00000, 0x06a00000, CAN_FILTERMODE_IDLIST, 3, CAN_FILTERSCALE_32BIT, CAN_FIFO_1, CAN_ENABLE}; // ID = 0X35

CAN_FilterInit_t CAN_FilterUserRequest = {0x06c00000, 0x06c00000, CAN_FILTERMODE_IDLIST, 4, CAN_FILTERSCALE_32BIT, CAN_FIFO_0, CAN_ENABLE}; // ID = 0X36

CAN_FilterInit_t CAN_FilterAppDiagnostics_MODE1 = {0x07000000, 0x07000000, CAN_FILTERMODE_IDLIST, 2, CAN_FILTERSCALE_32BIT, CAN_FIFO_0, CAN_ENABLE}; // ID = 0X38

CAN_FilterInit_t CAN_FilterAppDiagnostics_MODE2 = {0x06200000, 0x06200000, CAN_FILTERMODE_IDLIST, 2, CAN_FILTERSCALE_32BIT, CAN_FIFO_0, CAN_ENABLE}; // ID = 0X31

/* In case of multiple ECUs */

CAN_FilterInit_t CAN_FilterUpdateNotifcation = {0x06400000, 0x06400000, CAN_FILTERMODE_IDLIST, 3, CAN_FILTERSCALE_32BIT, CAN_FIFO_0, CAN_ENABLE}; // ID = 0X32

CAN_FilterInit_t CAN_FilterUserDiagnostics = {0x06600000, 0x06600000, CAN_FILTERMODE_IDLIST, 4, CAN_FILTERSCALE_32BIT, CAN_FIFO_0, CAN_ENABLE}; // ID = 0X33

CAN_FilterInit_t CAN_FilterApp1Update = {0x06800000, 0x06800000, CAN_FILTERMODE_IDLIST, 5, CAN_FILTERSCALE_32BIT, CAN_FIFO_0, CAN_ENABLE}; // ID = 0X34

CAN_FilterInit_t CAN_FilterApp2Update = {(u32)(0x50<<21), (u32)(0x50<<21), CAN_FILTERMODE_IDLIST, 6, CAN_FILTERSCALE_32BIT, CAN_FIFO_0, CAN_ENABLE}; // ID = 0X50

CAN_FilterInit_t CAN_FilterApp1Diagnostics = {(u32)(0X47<<21), (u32)(0X47<<21), CAN_FILTERMODE_IDLIST, 5, CAN_FILTERSCALE_32BIT, CAN_FIFO_0, CAN_ENABLE}; // ID = 0X47

CAN_FilterInit_t CAN_FilterApp2Diagnostics = {(u32)(0X48<<21), (u32)(0X48<<21), CAN_FILTERMODE_IDLIST, 6, CAN_FILTERSCALE_32BIT, CAN_FIFO_0, CAN_ENABLE}; // ID = 0X48