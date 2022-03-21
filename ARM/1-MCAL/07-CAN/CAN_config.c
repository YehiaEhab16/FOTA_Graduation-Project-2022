///*******************************************************************************
//**  FILENAME     : Can_cfg.c         			                                        **
//**                                                                            **
//**  VERSION      :                                                       **
//**                                                                            **
//**  DATE         :                                                  **
//**
//**  AUTHOR       : 2022	                                              **
//**                                                                            **                                                                           **                                                                          **
//**  DESCRIPTION  : CAN Driver source configuration file                       **
//**                                                                            **
//*******************************************************************************/
//#include "STD_TYPES.h"
//#include "CAN_private.h"
//#include "CAN_config.h"
//
//#include "CAN_interface.h"
//
//
//
//
///*FOR BIT RATE 500KHZ , PRESCALE = 1, SJW = 0 ,SEG1 = 0X0C , SEG2 = 0X01 , SAMPLE PIONT AT 87.5 , BTR=  0x001C0000 */
//
//                        /* they are not stabdard containers but keep it now until new version become tested and safe :)*/
////CAN_InitTypeDef        CAN_InitStruct         =	{ 1 , CAN_MODE_NORMAL   , 0 , 0X0C , 0X01, 0 , 0 , 0 , 0 , 0 , 0 } ;
//
//
////CAN_FilterInitTypeDef  CAN_FilterInitStruct_1 = { 0x00600000 , 0x00600000 , CAN_FILTERMODE_IDMASK ,  1  , CAN_FILTERSCALE_32BIT , CAN_FIFO_0 , 1}; // ID = 0X03
////
////CAN_FilterInitTypeDef  CAN_FilterInitStruct_2 = { 0x00400000 , 0x00400000 , CAN_FILTERMODE_IDMASK ,  2  , CAN_FILTERSCALE_32BIT , CAN_FIFO_0 , 1}; // ID = 0X02
//
