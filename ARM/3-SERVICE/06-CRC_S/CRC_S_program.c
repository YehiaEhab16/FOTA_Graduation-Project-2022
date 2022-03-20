/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :SERVICE                ***********************/
/***********************   SWC (DRIVER):CRC 			 ***********************/
/***********************   DATE : 15-3-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "STD_TYPES.h"

#include "RCC_interface"
#include "CRC_interface"

#include "CRC_S_interface.h"
#include "CRC_S_private.h"
#include "CRC_S_config.h"

RCC_t Global_RCC_tCRC  = {RCC_AHB,RCC_AHB_CRC_EN};

void CRC_S_voidInit(void)
{
	RCC_u8EnableClock(&Global_RCC_tCRC);
}

void CRC_S_voidDisable(void)
{
	RCC_u8EnableClock(&Global_RCC_tCRC);
}
