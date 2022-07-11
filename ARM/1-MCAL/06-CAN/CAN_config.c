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

/******************************** Main ECU Filters *************************************/

CAN_FilterInit_t CAN_FilterUserResponse = {(u32)(0x46<<21), (u32)(0x46<<21), CAN_FILTERMODE_IDLIST, 1, CAN_FILTERSCALE_32BIT, CAN_FIFO_1, CAN_ENABLE};

CAN_FilterInit_t CAN_FilterAppAck = {0x06000000, 0x06000000, CAN_FILTERMODE_IDLIST, 3, CAN_FILTERSCALE_32BIT, CAN_FIFO_0, CAN_ENABLE};

CAN_FilterInit_t CAN_FilterUserRequest = {(u32)(0x36<<21), (u32)(0x36<<21), CAN_FILTERMODE_IDLIST, 4, CAN_FILTERSCALE_32BIT, CAN_FIFO_1, CAN_ENABLE};

CAN_FilterInit_t CAN_FilterAppDiagnostics_MODE1 = {(u32)(0x38<<21), (u32)(0x38<<21), CAN_FILTERMODE_IDLIST, 2, CAN_FILTERSCALE_32BIT, CAN_FIFO_1, CAN_ENABLE};

CAN_FilterInit_t CAN_FilterAppDiagnostics_MODE2 = {(u32)(0x31<<21), (u32)(0x31<<21), CAN_FILTERMODE_IDLIST, 5, CAN_FILTERSCALE_32BIT, CAN_FIFO_1, CAN_ENABLE};

/************************************* User ECU Filters *************************************/

CAN_FilterInit_t CAN_FilterUpdateNotifcation = {(u32)(0x73<<21), (u32)(0x73<<21), CAN_FILTERMODE_IDLIST, 3, CAN_FILTERSCALE_32BIT, CAN_FIFO_0, CAN_ENABLE};

CAN_FilterInit_t CAN_FilterUserDiagnostics = {(u32)(0x33<<21), (u32)(0x33<<21), CAN_FILTERMODE_IDLIST, 4, CAN_FILTERSCALE_32BIT, CAN_FIFO_0, CAN_ENABLE};

/********************************** Application ECUs Filters *************************************/

CAN_FilterInit_t CAN_FilterApp1Update = {(u32)(0x34<<21), (u32)(0x34<<21), CAN_FILTERMODE_IDLIST, 5, CAN_FILTERSCALE_32BIT, CAN_FIFO_0, CAN_ENABLE};

CAN_FilterInit_t CAN_FilterApp2Update = {(u32)(0x50<<21), (u32)(0x50<<21), CAN_FILTERMODE_IDLIST, 6, CAN_FILTERSCALE_32BIT, CAN_FIFO_0, CAN_ENABLE};

CAN_FilterInit_t CAN_FilterAppDiagnostics = {(u32)(0X48<<21), (u32)(0X48<<21), CAN_FILTERMODE_IDLIST, 6, CAN_FILTERSCALE_32BIT, CAN_FIFO_0, CAN_ENABLE};
