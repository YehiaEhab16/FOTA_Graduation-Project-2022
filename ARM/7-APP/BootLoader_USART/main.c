/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :Bootloader		    ***********************/
/***********************   DATA : 7-3-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/


/********************************LIBRARY LAYER**********************************/
#include "../../6-Library/STD_TYPES.h"
#include "../../6-Library/BIT_MATH.h"
/*******************************************************************************/
/*******************************************************************************/

/********************************MCAL LAYER*************************************/
#include "../../1-MCAL/01-GPIO/GPIO_interface.h"
#include "../../1-MCAL/02-RCC/RCC_interface.h"
#include "../../1-MCAL/05-USART/USART_interface.h"
#include "../../1-MCAL/08-FPEC/FPEC_interface.h"
#include "../../1-MCAL/11-WWDG/WWDG_interface.h"
/*******************************************************************************/
/*******************************************************************************/
/********************************HAL LAYER*************************************/
#include "../../1-MCAL/01-LED/LED_interface.h"

/********************************SERV LAYER*************************************/
#include "../../3-SERVICE/01-PARSING/PARSING_interface.h"


/*******************************************************************************/
/*******************************************************************************/
/****************************************************************************************************/
/*************BOOTLOADER DESIGN*************/

/********************************PreLoad Block***********************************/
#define BOOT_u8REQUESTFLAG					0x080028C0
#define READ_REQUEST_FLAG					(*((volatile u16*)0x080028C0))
#define SCB_VTOR   							(*((volatile u32*)0xE000ED08))

void APP1(void) ;
void APP2(void) ;

typedef void (*Application)(void) ;

Application AddrAPP1 ;
Application AddrAPP2 ;

//LEDs
LED_t Global_LED_tApp1 = {LED_PORTB,LED_PIN0,LED_ACTIVE_HIGH};
LED_t Global_LED_tApp2 = {LED_PORTC,LED_PIN15,LED_ACTIVE_HIGH};

void main (void)
{
	/*Initialize RCC*/
	RCC_voidInit();

	/*Initialize USART*/
	GPIO_voidDirectionInit();

	/*Initialize USART*/
	USART_voidInit(USART1);

	/*Initialize FPEC*/
	FPEC_voidInit();
	
	#if BOOT_TARGET == BOOT_APP1
	LED_voidLedOn(&Global_LED_tApp1);
	#elif BOOT_TARGET == BOOT_APP2
	LED_voidLedOn(&Global_LED_tApp2);
	#endif
	
	u16 Update = 0;
	u16 No_update =1 ;
	u16 Corruption =2 ;

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

	/*******************************************************************************************/
	/*******************************************************************************************/
	/********************************BOOTLOADER**************************************************/

	if (READ_REQUEST_FLAG==0 )
	{

		while (BOOT_u8FinRecFlag == 0)
		{

			BOOT_u8RecData[BOOT_u32RecCounter]=USART_u8ReceiveChar(USART1);

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
					//WWDG_voidReset(1,10);
					//IWDG_voidReset(100);

				}
				/**************************************************************************************/
				/*********************************Write Operation *************************************/
				PARSING_voidWriteData(BOOT_u8RecData);
				USART_voidTransmitSync(USART1,(u8*)"ok");
				BOOT_u32RecCounter =0 ;

				if (BOOT_u8RecData[8]=='1')
				{
					FPEC_voidFlashPageErase(10);
					FPEC_voidFlashWrite(BOOT_u8REQUESTFLAG, &No_update, 1);
					IWDG_voidReset(100);
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

	/********************************APPLICATION2************************************************/
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

	SCB_VTOR =0x08003000;
	AddrAPP1 =*(Application*)(0x08003004);
	AddrAPP1();

}
void APP2(void)
{
	SCB_VTOR = 0x0800E800 ;

	AddrAPP2 =*((Application*)0x0800E804);
	AddrAPP2();
}
