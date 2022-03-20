/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :SERVICE                ***********************/
/***********************   SWC (DRIVER):FPEC 			 ***********************/
/***********************   DATA : 15-3-2022 			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "FPEC_interface.h"

#include "FPEC_S_interface.h"
#include "FPEC_S_private.h"
#include "FPEC_S_config.h"

u16 Data[100] = {0};
u32 Address= 0x08000000;

RCC_t Global_RCC_tFPEC  = {RCC_AHB,RCC_AHB_FLITF_EN};

void FPEC_S_voidInit(void)
{
	RCC_u8EnableClock(&Global_RCC_tFPEC);
}

void FPEC_S_voidDisable(void)
{
	RCC_u8DisableClock(&Global_RCC_tFPEC);
}

u8 FPEC_S_u8AsciToHex (u8 Copy_u8Asci)
{
	u8 Local_u8HexNum ;

	if ((Copy_u8Asci>=ASCI_ZERO)&&(Copy_u8Asci<=ASCI_NINE))
	{
		Local_u8HexNum = Copy_u8Asci - ASCI_ZERO ;
	}
	else
	{
		Local_u8HexNum =Copy_u8Asci -ASCI_A_10 ;
	}
	return Local_u8HexNum;


}

void FPEC_S_voidWriteData (u8* Copy_u8Data)
{
	/******************Local Variable to extract the Number of byte of Data**********************/
	u8 Local_u8MsbByte ;
	u8 Local_u8LsbByte ;
	u8 Local_u8NumByte ;
	/******************        Local Variable to Extract address           **********************/
	u8 Local_u8Address0 ;
	u8 Local_u8Address1 ;
	u8 Local_u8Address2 ;
	u8 Local_u8Address3 ;
	u32 Local_u8MainAddress ;

	/******************        Local Variable to Extract Data          **********************/
	u8 Local_u8Data0 ;
	u8 Local_u8Data1 ;
	u8 Local_u8Data2 ;
	u8 Local_u8Data3 ;

	if (Copy_u8Data[8]=='0')
	{
		Local_u8MsbByte = FPEC_S_u8AsciToHex(Copy_u8Data[1]);
		Local_u8LsbByte =FPEC_S_u8AsciToHex(Copy_u8Data[2]);
		/*Number of Byte of Data*/
		Local_u8NumByte =(Local_u8MsbByte<<4)|(Local_u8LsbByte);


		Local_u8Address0 = FPEC_S_u8AsciToHex(Copy_u8Data[3]);
		Local_u8Address1 = FPEC_S_u8AsciToHex(Copy_u8Data[4]);
		Local_u8Address2 = FPEC_S_u8AsciToHex(Copy_u8Data[5]);
		Local_u8Address3 = FPEC_S_u8AsciToHex(Copy_u8Data[6]);

		Address = Address & 0xFFFF0000;
		Local_u8MainAddress = Address | (Local_u8Address3)|(Local_u8Address2<<4)|(Local_u8Address1<<8)|(Local_u8Address0<<12);


		for (u8 Local_u8Counter =0 ; Local_u8Counter<Local_u8NumByte/2;Local_u8Counter++)
		{
			Local_u8Data0 = FPEC_S_u8AsciToHex(Copy_u8Data[4*Local_u8Counter+9]);
			Local_u8Data1 = FPEC_S_u8AsciToHex(Copy_u8Data[4*Local_u8Counter+10]);
			Local_u8Data2 = FPEC_S_u8AsciToHex(Copy_u8Data[4*Local_u8Counter+11]);
			Local_u8Data3 = FPEC_S_u8AsciToHex(Copy_u8Data[4*Local_u8Counter+12]);

			Data[Local_u8Counter] = (Local_u8Data0<<4)|(Local_u8Data1)|(Local_u8Data2<<12)|(Local_u8Data3<<8);

		}
		FPEC_voidFlashWrite(Local_u8MainAddress,Data,Local_u8NumByte/2);
	}
	else
	{
		//nothing
	}
}
