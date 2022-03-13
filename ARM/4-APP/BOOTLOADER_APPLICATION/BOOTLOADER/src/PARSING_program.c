/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :SERV                   ***********************/
/***********************   SWC (DRIVER):Parsing 			 ***********************/
/***********************   DATA : 7-3-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "FPEC_interface.h"

#include "PARSING_interface.h"
#include "PARSING_config.h"
#include "PARSING_private.h"

u16 Data[100];


u8 PARSING_u8AsciToHex (u8 Copy_u8Asci)
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

void PARSING_voidWriteData (u8* Copy_u8Data)
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
	u8 Local_u8MainAddress ;

	/******************        Local Variable to Extract Data          **********************/
	u8 Local_u8Data0 ;
	u8 Local_u8Data1 ;
	u8 Local_u8Data2 ;
	u8 Local_u8Data3 ;

	if (Copy_u8Data[8]=='0')
	{
		Local_u8MsbByte = PARSING_u8AsciToHex(Copy_u8Data[1]);
		Local_u8LsbByte =PARSING_u8AsciToHex(Copy_u8Data[2]);
		/*Number of Byte of Data*/
		Local_u8NumByte =(Local_u8MsbByte<<4)|(Local_u8LsbByte);


		Local_u8Address0 = PARSING_u8AsciToHex(Copy_u8Data[3]);
		Local_u8Address1 = PARSING_u8AsciToHex(Copy_u8Data[4]);
		Local_u8Address2 = PARSING_u8AsciToHex(Copy_u8Data[5]);
		Local_u8Address3 = PARSING_u8AsciToHex(Copy_u8Data[6]);


		Local_u8MainAddress = PARSING_BASE_ADDRESS | (Local_u8Address3)|(Local_u8Address2<<4)|(Local_u8Address1<<8)|(Local_u8Address0<<12);


		for (u8 Local_u8Counter =0 ; Local_u8Counter<Local_u8NumByte/2;Local_u8Counter++)
		{
			Local_u8Data0 = PARSING_u8AsciToHex(Copy_u8Data[4*Local_u8Counter+9]);
			Local_u8Data1 = PARSING_u8AsciToHex(Copy_u8Data[4*Local_u8Counter+10]);
			Local_u8Data2 = PARSING_u8AsciToHex(Copy_u8Data[4*Local_u8Counter+11]);
			Local_u8Data3 = PARSING_u8AsciToHex(Copy_u8Data[4*Local_u8Counter+12]);

			Data[Local_u8Counter] = (Local_u8Data0<<4)|(Local_u8Data1)|(Local_u8Data2<<12)|(Local_u8Data3<<8);

		}
		FPEC_voidFlashWrite(Local_u8MainAddress,Data,Local_u8NumByte/2);
	}
	else
	{
		//nothing
	}
}

u16 Data[100] = {0};
u32 Address= 0x08000000;

u8 AsciToHex(u8 Copy_u8Asci)
{
	u8 Result;
	if ( (Copy_u8Asci >= 48) && (Copy_u8Asci <= 57) )
	{
		Result = Copy_u8Asci - 48;
	}

	else
	{
		Result = Copy_u8Asci - 55;
	}

	return Result;
}


void ParseData(u8* Copy_u8BufData)
{
	u8 DigitLow,DigitHigh,CC,i;
	u8 DataDigit0,DataDigit1,DataDigit2,DataDigit3;
	u8 DataCounter = 0;

	/* Get Character Count */
	DigitHigh = AsciToHex (Copy_u8BufData[1]);
	DigitLow  = AsciToHex (Copy_u8BufData[2]);
	CC        = (DigitHigh<<4) | DigitLow ;

	/* Get Address */
	DataDigit0 = AsciToHex (Copy_u8BufData[3]);
	DataDigit1 = AsciToHex (Copy_u8BufData[4]);
	DataDigit2 = AsciToHex (Copy_u8BufData[5]);
	DataDigit3 = AsciToHex (Copy_u8BufData[6]);

	/* Clear Low Part of Address */
	Address = Address & 0xFFFF0000;
	Address = Address | (DataDigit3) | (DataDigit2 << 4) | (DataDigit1 << 8) | (DataDigit0<<12);

	for (i=0;i<CC/2; i++)
	{
		DataDigit0 = AsciToHex (Copy_u8BufData[4*i+9 ]);
		DataDigit1 = AsciToHex (Copy_u8BufData[4*i+10]);
		DataDigit2 = AsciToHex (Copy_u8BufData[4*i+11]);
		DataDigit3 = AsciToHex (Copy_u8BufData[4*i+12])	;

		Data[DataCounter] = (DataDigit3 << 8) | (DataDigit2 << 12) | (DataDigit1) | (DataDigit0<<4);
		DataCounter++;
	}

	FPEC_voidFlashWrite(Address,Data,CC/2);
}


