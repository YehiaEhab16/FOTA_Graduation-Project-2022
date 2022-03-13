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

#include "RCC_interface.h"
#include "USART_interface.h"
#include "PORT_interface.h"
#include "CRC_interface.h"
#include "FPEC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"


/*******************************************************************************/
/*******************************************************************************/


/********************************SERV LAYER*************************************/



#include "PARSING_interface.h"


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


void main (void)
{

	RCC_voidInit();

	/*Create Perpherial UART, PORTA , FPEC  */
	struct Peripheral UART1 = {RCC_APB2,RCC_APB2_USART1_EN};
	struct Peripheral UART2 = {RCC_APB1,RCC_APB1_USART2_EN};
	struct Peripheral PORTA = {RCC_APB2,RCC_APB2_IOPA_EN};
	struct Peripheral FPEC1 = {RCC_AHB,RCC_AHB_FLITF_EN};
	struct Peripheral CRC = {RCC_AHB,RCC_AHB_CRC_EN};

	/*Enable Perpherial UART, PORTA , FPEC  */
	RCC_u8EnableClock(&UART1);
	RCC_u8EnableClock(&UART2);
	RCC_u8EnableClock(&PORTA);
	RCC_u8EnableClock(&FPEC1);
	RCC_u8EnableClock(&CRC);
	/*Initialize USART*/
	PORT_voidInit() ;
	/*Initialize USART*/
	USART_voidInit (USART1);


	/**************************Init the FPEC Driver ******************/
	FPEC_voidInit();

	u16 DATA = 0;
	FPEC_voidFlashWrite(BOOT_u8REQUESTFLAG, &DATA, 1);
	if ((*((volatile u16*)0x080028C0)) == 0)
	{
		GPIO_u8SetPinValue(GPIO_PORTA,GPIO_PIN_1, GPIO_PIN_LOW);
	}

	u8 BOOT_u8RecData[100];
	u8 BOOT_u8FinRecFlag = 0 ;
	u32 BOOT_u32RecCounter =0 ;
	u32 BOOT_u32EraseCounter =0 ;
	u32 BOOT_u32CRCCounter =0 ;
	u8 BOOT_u8CRCVal =0 ;
	u8 BOOt_u8CRCTest =0 ;
	u32 BOOT_u32EraseFlag =1 ;
	u32 BOOT_u32NumChar =0 ;
	u8 BOOT_u8AscitoHex =0 ;

	u16 BOOT_u16ConFlag = 0 ;
	u16 APP_u16Flag = 1 ;



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

					for (BOOT_u32EraseCounter=12 ;BOOT_u32EraseCounter<128 ;BOOT_u32EraseCounter++)
					{
						FPEC_voidFlashPageErase(BOOT_u32EraseCounter);
					}
					BOOT_u32EraseFlag = 0 ;
				}
				/**************************************************************************************/
				/**************************************************************************************/


				/****************************Erase APPLICATION 1 **************************************/

				for (BOOT_u32CRCCounter=1 ; BOOT_u32CRCCounter <BOOT_u32RecCounter-2 ;BOOT_u32CRCCounter++)
				{

					BOOT_u8AscitoHex = PARSING_u8AsciToHex(BOOT_u8RecData[BOOT_u32CRCCounter]);
					BOOT_u8CRCVal=CRC_u8CalculationHardware(BOOT_u8AscitoHex) ;

				}

				BOOt_u8CRCTest = (u8)((BOOT_u8RecData[BOOT_u32RecCounter-2]<<4)|(BOOT_u8RecData[BOOT_u32RecCounter-1]));


				if (BOOt_u8CRCTest != (u8)BOOT_u8CRCVal)
				{
					GPIO_u8SetPinValue(GPIO_PORTA,GPIO_PIN_1, GPIO_PIN_HIGH);

					/*Data Corruption (RED) */
					/*Jump to application 2*/
					/*Send message to Main ECU "The data is corrupted"*/
					//USART_voidTransmitSync(USART2,(u8 *)"NOK\r");
					/*SET Request Flag */
					//BOOT_u8REQUESTFLAG = 1 ;

				}

				/**************************************************************************************/
				/*********************************Write Operation *************************************/
				PARSING_voidWriteData(BOOT_u8RecData);
				USART_voidTransmitSync(USART1,(u8*)"ok");

				if (BOOT_u8RecData[8]=='1')
				{
					GPIO_u8SetPinValue(GPIO_PORTA,GPIO_PIN_0, GPIO_PIN_HIGH);
					FPEC_voidFlashWrite(BOOT_u8REQUESTFLAG, &APP_u16Flag, 1);
					APP1();
				}
				/**************************************************************************************/
				/**********************************Init the second record*******************************/
				BOOT_u32RecCounter =0 ;

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

	/********************************APPLICATION1************************************************/
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
	GPIO_u8SetPinValue(GPIO_PORTA,GPIO_PIN_2, GPIO_PIN_HIGH);
	SCB_VTOR =0x08001800;
	AddrAPP1 =*((Application*)0x08001804);

	AddrAPP1();

}
void APP2(void)
{
	SCB_VTOR = 0x0800E800 ;

	AddrAPP2 =*((Application*)0x0800E804);
	AddrAPP2();
}
