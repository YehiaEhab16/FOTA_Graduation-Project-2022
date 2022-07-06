/****************************************************************/
/****************************************************************/
/***********************   YEHIA SHAHIN   ***********************/
/***********************   Layer :HAL    ************************/
/***********************   SWC (DRIVER):CLCD ********************/
/***********************   DATA : 5-1-2022 **********************/
/***********************   VERSION : 1.00   *********************/
/****************************************************************/
/****************************************************************/

//library
#include "STD_TYPES.h"
#include "BIT_MATH.h"

//mcal layer
#include "GPIO_interface.h"
#include "STK_interface.h" 

#include "CLCD_interface.h"
#include "CLCD_config.h"
#include "CLCD_private.h"



void CLCD_voidSendCommand (u8 Copy_u8Command)
{
	//set the register select to zero to active command mode
	GPIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,GPIO_PIN_LOW);
	//set RW to zero to active the effect command on the lcd
	GPIO_u8SetPinValue (CLCD_CTRL_PORT,CLCD_RW_PIN,GPIO_PIN_LOW);

#if CLCD_MODE==MODE_8_BIT
	GPIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Command);
	//read the command by enable pin
	GPIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,GPIO_PIN_HIGH);
	STK_voidDelay(2);
	GPIO_u8SetPinValue (CLCD_CTRL_PORT,CLCD_E_PIN,GPIO_PIN_LOW);
#elif CLCD_MODE==MODE_4_BIT
	GPIO_u8SetPinValue(CLCD_DATA_PORT,GPIO_PIN_7,GET_BIT(Copy_u8Command,7));
	GPIO_u8SetPinValue(CLCD_DATA_PORT,GPIO_PIN_6,GET_BIT(Copy_u8Command,6));
	GPIO_u8SetPinValue(CLCD_DATA_PORT,GPIO_PIN_5,GET_BIT(Copy_u8Command,5));
	GPIO_u8SetPinValue(CLCD_DATA_PORT,GPIO_PIN_4,GET_BIT(Copy_u8Command,4));

	GPIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,GPIO_PIN_HIGH);
	STK_voidDelay (2);
	GPIO_u8SetPinValue (CLCD_CTRL_PORT,CLCD_E_PIN,GPIO_PIN_LOW);

	GPIO_u8SetPinValue(CLCD_DATA_PORT,GPIO_PIN_7,GET_BIT(Copy_u8Command,3));
	GPIO_u8SetPinValue(CLCD_DATA_PORT,GPIO_PIN_6,GET_BIT(Copy_u8Command,2));
	GPIO_u8SetPinValue(CLCD_DATA_PORT,GPIO_PIN_5,GET_BIT(Copy_u8Command,1));
	GPIO_u8SetPinValue(CLCD_DATA_PORT,GPIO_PIN_4,GET_BIT(Copy_u8Command,0));

	GPIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,GPIO_PIN_HIGH);
	STK_voidDelay (2);
	GPIO_u8SetPinValue (CLCD_CTRL_PORT,CLCD_E_PIN,GPIO_PIN_LOW);


#else
#error "WRONG IN SEND COMMAND"
#endif
}
void CLCD_voidSendData (u8 Copy_u8Data)
{
	//set the register select to one to active command mode
	GPIO_u8SetPinValue (CLCD_CTRL_PORT,CLCD_RS_PIN,GPIO_PIN_HIGH);
	//set RW to zero to active the effect command on the lcd
	GPIO_u8SetPinValue (CLCD_CTRL_PORT,CLCD_RW_PIN,GPIO_PIN_LOW);


#if CLCD_MODE==MODE_8_BIT
	//put data on the data port
	GPIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Data);
	//read the data by enable pin
	GPIO_u8SetPinValue (CLCD_CTRL_PORT,CLCD_E_PIN,GPIO_PIN_HIGH);
	STK_voidDelay (2);
	GPIO_u8SetPinValue (CLCD_CTRL_PORT,CLCD_E_PIN,GPIO_PIN_LOW);
#elif CLCD_MODE==MODE_4_BIT
	GPIO_u8SetPinValue(CLCD_DATA_PORT,GPIO_PIN_7,GET_BIT(Copy_u8Data,7));
	GPIO_u8SetPinValue(CLCD_DATA_PORT,GPIO_PIN_6,GET_BIT(Copy_u8Data,6));
	GPIO_u8SetPinValue(CLCD_DATA_PORT,GPIO_PIN_5,GET_BIT(Copy_u8Data,5));
	GPIO_u8SetPinValue(CLCD_DATA_PORT,GPIO_PIN_4,GET_BIT(Copy_u8Data,4));

	GPIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,GPIO_PIN_HIGH);
	STK_voidDelay (2);
	GPIO_u8SetPinValue (CLCD_CTRL_PORT,CLCD_E_PIN,GPIO_PIN_LOW);

	GPIO_u8SetPinValue(CLCD_DATA_PORT,GPIO_PIN_7,GET_BIT(Copy_u8Data,3));
	GPIO_u8SetPinValue(CLCD_DATA_PORT,GPIO_PIN_6,GET_BIT(Copy_u8Data,2));
	GPIO_u8SetPinValue(CLCD_DATA_PORT,GPIO_PIN_5,GET_BIT(Copy_u8Data,1));
	GPIO_u8SetPinValue(CLCD_DATA_PORT,GPIO_PIN_4,GET_BIT(Copy_u8Data,0));

	GPIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,GPIO_PIN_HIGH);
	STK_voidDelay (2);
	GPIO_u8SetPinValue (CLCD_CTRL_PORT,CLCD_E_PIN,GPIO_PIN_LOW);

#else
#error "WRONG IN SEND DATA"
#endif

}



void CLCD_voidInit (void)
{

	STK_voidInit();


#if CLCD_MODE==MODE_8_BIT
	STK_voidDelay (40);
#elif CLCD_MODE==MODE_4_BIT
	STK_voidDelay (40);
	//set the register select to zero to active command mode
	GPIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,GPIO_PIN_LOW);
	//set RW to zero to active the effect command on the lcd
	GPIO_u8SetPinValue (CLCD_CTRL_PORT,CLCD_RW_PIN,GPIO_PIN_LOW);
	//put command on the command port

	GPIO_u8SetPinValue(CLCD_DATA_PORT,GPIO_PIN_7,0);
	GPIO_u8SetPinValue(CLCD_DATA_PORT,GPIO_PIN_6,0);
	GPIO_u8SetPinValue(CLCD_DATA_PORT,GPIO_PIN_5,1);
	GPIO_u8SetPinValue(CLCD_DATA_PORT,GPIO_PIN_4,0);

	GPIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,GPIO_PIN_HIGH);
	STK_voidDelay (2);
	GPIO_u8SetPinValue (CLCD_CTRL_PORT,CLCD_E_PIN,GPIO_PIN_LOW);
#else
#error "WRONG IN INITIALIZATION"
#endif

	// wait for more than 30 ms

	//function set Set command 2lines , font =5*7
	CLCD_voidSendCommand(0b00101000);

	CLCD_voidSendCommand(0b00001100);

	CLCD_voidSendCommand(0b00000001);





}



void CLCD_voidSendString(const char * Copy_phString )
{
	u8 Local_LoopCounter;
	for (Local_LoopCounter=0;(*(Copy_phString+Local_LoopCounter))!=0;Local_LoopCounter++)
	{
		CLCD_voidSendData(*(Copy_phString+Local_LoopCounter));

	}
}



void CLCD_voidSendNumber (u32 Copy_u32Number)
{
	u8 Local_u8Counter=0;
	u8 Local_u8Counter1=0;
	u8 Local_u8Counter3 ;
	u32 Local_u8Temp =Copy_u32Number;
	u32 Local_u8Temp2 =Copy_u32Number;
	u32 Local_u8result;


	do {
		Local_u8Temp /=10 ;
		Local_u8Counter++;
	}while(Local_u8Temp !=0);

	Local_u8Counter3 =Local_u8Counter;
	for (Local_u8Counter1 =0;Local_u8Counter1<Local_u8Counter;Local_u8Counter1++)
	{
		do
		{
			Local_u8result =Local_u8Temp2 %10;
			Local_u8Temp2 /=10 ;
			Local_u8Counter3--;
		}
		while (Local_u8Counter3>Local_u8Counter1);
		Local_u8Counter3 = Local_u8Counter;
		Local_u8Temp2 =Copy_u32Number;
		CLCD_voidSendData('0'+Local_u8result);

	}

}


void CLCD_voidGotoXY (u8 Copy_u8PosX ,u8 Copy_u8PosY)
{

	u8 Local_u8DDRAMAddress ;

	if (Copy_u8PosY == 0)
	{
		Local_u8DDRAMAddress =Copy_u8PosX;
	}
	else
	{
		Local_u8DDRAMAddress =Copy_u8PosX;
	}

	CLCD_voidSendCommand(Local_u8DDRAMAddress +128);
}


void CLCD_voidFullLcd (const char *Copy_pu8String ,u8 Copy_u8PosX ,u8 Copy_u8PosY)
{
	u8 Local_u8CounterLoop ;
	CLCD_voidGotoXY(Copy_u8PosX,Copy_u8PosY);
	for (Local_u8CounterLoop =0 ; (*(Copy_pu8String+Local_u8CounterLoop))!=0;Local_u8CounterLoop++)
	{
		CLCD_voidSendData(*(Copy_pu8String+Local_u8CounterLoop));
		Copy_u8PosX++;
		if (Copy_u8PosX>15&&Copy_u8PosX<=16)
		{
			CLCD_voidGotoXY(0x40,1);
		}
	}

}

void CLCD_voidWriteSpecialCharacter(const char *Copy_pu8String ,u8 Copy_u8NumberPatttern,u8 Copy_u8PosX, u8 Copy_u8PosY)
{
	u8 Local_u8DDRAMAddress = Copy_u8NumberPatttern *8 ;

	u8 Local_u8LoopCounter ;

	CLCD_voidSendCommand(Local_u8DDRAMAddress +64);

	for (Local_u8LoopCounter=0;Local_u8LoopCounter<8;Local_u8LoopCounter++)
	{
		CLCD_voidSendData(*(Copy_pu8String+Local_u8LoopCounter));
	}

	CLCD_voidGotoXY(Copy_u8PosX,Copy_u8PosY);

	CLCD_voidSendData(Copy_u8NumberPatttern);


}




void CLCD_sinusoidal (const char* arr ,u8 Copy_u8PosX, u8 Copy_u8PosY,u8 size)
{
	u8 Local_u8FirstLocation=0;
	CLCD_voidGotoXY(Copy_u8PosX,Copy_u8PosY);
	CLCD_voidSendString(arr);
	STK_voidDelay(1000);
	Local_u8FirstLocation+=size;
	CLCD_voidSendCommand(1);

	CLCD_voidGotoXY(0x40+Copy_u8PosX+Local_u8FirstLocation,1);
	CLCD_voidSendString(arr);
	STK_voidDelay(1000);
	Local_u8FirstLocation+=size;
	CLCD_voidSendCommand(1);

	CLCD_voidGotoXY(Copy_u8PosX+Local_u8FirstLocation,0);
	CLCD_voidSendString(arr);
	STK_voidDelay(1000);
	Local_u8FirstLocation+=size;
	CLCD_voidSendCommand(1);

	CLCD_voidGotoXY(0x40+Copy_u8PosX+Local_u8FirstLocation,1);
	CLCD_voidSendString(arr);
	STK_voidDelay(1000);
	CLCD_voidSendCommand(1);


}


