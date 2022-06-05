/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):FPEC 			 ***********************/
/***********************   DATA : 7-3-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/
/********************************LIBRARY LAYER**********************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
/*******************************************************************************/
/*******************************************************************************/
/********************************MCAL LAYER*************************************/
#include "GPIO_interface.h"
#include "RCC_interface.h"
#include "CAN_interface.h"
#include "FPEC_interface.h"
#include "WWDG_interface.h"
/*******************************************************************************/
/*******************************************************************************/
/********************************SERV LAYER*************************************/
#include "PARSING_interface.h"
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*****************************BOOTLOADER DESIGN*********************************/
/********************************PreLoad Block**********************************/
#define BOOT_u8REQUESTFLAG					0x080028C0
#define READ_REQUEST_FLAG					(*((volatile u16*)0x080028C0))
#define SCB_VTOR   							(*((volatile u32*)0xE000ED08))

/**
 *********************************************************************************
Initialize the CAN Protocol 
 *********************************************************************************
 **/
extern CAN_Init_t CAN_InitStruct;
extern CAN_FilterInit_t CAN_FilterUserResponse;
CAN_msg CAN_RXmsg;
CAN_msg CAN_TXmsg;
/*********************************************************************************/
/*********************************************************************************/
/*****************************Application ***************************************/
/*********************************************************************************/
/*********************************************************************************/

void APP1(void) ;
void APP2(void) ;

/*Pointer point to the Application Location */
typedef void (*Application)(void) ;

Application AddrAPP1 ;  //Application 1
Application AddrAPP2 ;  //Application 2



void main (void)
{

	RCC_voidInit();
	GPIO_voidDirectionInit();

	CAN_voidInit(&CAN_InitStruct);
	CAN_VoidFilterSet(&CAN_FilterUserResponse);

	FPEC_voidInit();

	CAN_TXmsg.len = 1;
	CAN_TXmsg.id = 0x30;
	CAN_TXmsg.format = CAN_ID_STD;
	CAN_TXmsg.type = CAN_RTR_DATA;
	CAN_TXmsg.data[0] = 'O';
	CAN_TXmsg.data[1] = 'k';





	/*Initialize USART*/

	/**************************Init the FPEC Driver ******************/
	u16 Update = 0;
	u16 No_update =1 ;
	u16 Corruption =2 ;

	//Simulation of Update 
	//FPEC_voidFlashWrite(BOOT_u8REQUESTFLAG, &Update, 1);

	// Array of Data
	u8 BOOT_u8RecData[100];

	// Flag to Write
	u8 BOOT_u8FinRecFlag = 0 ;

	//index of Data
	u32 BOOT_u32RecCounter =0 ;
	//index of Erase pages
	u32 BOOT_u32EraseCounter =0 ;

	//Check Sum
	u8 Check_s32Sum = 0 ;
	u32 Check_s32Counter = 1;
	u8 BOOT_u8Digit0 ;
	u8 BOOT_u8Digit1 ;
	u8 BOOT_u8Data ;
	u8 Check_sum_Validation ;

	// flage to start and end Erase operation
	u32 BOOT_u32EraseFlag =1 ;

	//counter for CAN
	u8 Counter_CAN = 0 ;



	/*******************************************************************************************/
	/*******************************************************************************************/
	/********************************BOOTLOADER**************************************************/

	if (READ_REQUEST_FLAG==0 )
	{

		while (BOOT_u8FinRecFlag == 0)
		{

			CAN_voidReceive(&CAN_RXmsg, 0);

			while (Counter_CAN == 4 )
			{
				BOOT_u8RecData[BOOT_u32RecCounter] = CAN_RXmsg.data[Counter_CAN]; 

				BOOT_u32RecCounter++;
				Counter_CAN++;

			}
			Counter_CAN = 0 ;

			/**************************************************************************************/
			if (BOOT_u8RecData[BOOT_u32RecCounter]=='\n')
			{
				/****************************Erase APPLICATION 1 **************************************/
				if (BOOT_u32EraseFlag==1)
				{

					for (BOOT_u32EraseCounter=12 ;BOOT_u32EraseCounter<60 ;BOOT_u32EraseCounter++)
					{
						FPEC_voidFlashPageErase(BOOT_u32EraseCounter);
					}
					BOOT_u32EraseFlag = 0 ;
				}

				Check_s32Sum =0 ;
				Check_s32Counter = 1 ;

				while(Check_s32Counter<BOOT_u32RecCounter-2)
				{
					BOOT_u8Digit0=PARSING_u8AsciToHex(BOOT_u8RecData[Check_s32Counter]);

					BOOT_u8Digit1 =PARSING_u8AsciToHex(BOOT_u8RecData[Check_s32Counter+1]);

					BOOT_u8Data = (BOOT_u8Digit0<<4)|(BOOT_u8Digit1);

					Check_s32Sum =Check_s32Sum + BOOT_u8Data ;

					Check_s32Counter = Check_s32Counter+2 ;

				}
				Check_s32Sum =~(Check_s32Sum -1) ;

				// Validation
				BOOT_u8Digit0=PARSING_u8AsciToHex(BOOT_u8RecData[BOOT_u32RecCounter-2]);

				BOOT_u8Digit1 =PARSING_u8AsciToHex(BOOT_u8RecData[BOOT_u32RecCounter-1]);

				Check_sum_Validation = (BOOT_u8Digit0<<4)|(BOOT_u8Digit1);


				if (Check_s32Sum !=Check_sum_Validation)
				{
					//Data Corruption
					GPIO_u8SetPinValue(GPIO_PORTA,GPIO_PIN_4, GPIO_PIN_HIGH);
					FPEC_voidFlashPageErase(10);
					FPEC_voidFlashWrite(BOOT_u8REQUESTFLAG, &Corruption, 1);
					WWDG_voidReset(100);

				}
				/**************************************************************************************/
				/*********************************Write Operation *************************************/
				PARSING_voidWriteData(BOOT_u8RecData);
				CAN_u8Transmit(&CAN_TXmsg);
				BOOT_u32RecCounter =0 ;

				if (BOOT_u8RecData[8]=='1')
				{
					FPEC_voidFlashPageErase(10);
					FPEC_voidFlashWrite(BOOT_u8REQUESTFLAG, &No_update, 1);
					WWDG_voidReset(10);
				}


			}
			else
			{
				BOOT_u32RecCounter++;
			}
		}
	}


	/*******************************************************************************************/
	/*******************************************************************************************/
	/********************************APPLICATION1************************************************/
	else if (READ_REQUEST_FLAG==1 )
	{
		APP1();
	}
	/*****************************************************************************************/
	/*****************************************************************************************/
	/********************************APPLICATION2*********************************************/
	else
	{

		APP2();
	}



}
/*****************************************************************************************/
/*****************************************************************************************/
/********************************Application Layer ***************************************/

void APP1(void)
{

	SCB_VTOR =0x08003000; // Edit
	AddrAPP1 =*(Application*)(0x08003004); //Edit
	AddrAPP1();

}
void APP2(void)
{
	SCB_VTOR = 0x0800E800 ; // Edit

	AddrAPP2 =*((Application*)0x0800E804); //Edit
	AddrAPP2();
}
