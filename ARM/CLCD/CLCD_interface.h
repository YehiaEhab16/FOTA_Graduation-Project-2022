/****************************************************************/
/****************************************************************/
/***********************   YEHIA SHAHIN   ***********************/
/***********************   Layer :HAL    ************************/
/***********************   SWC (DRIVER):CLCD ********************/
/***********************   DATA : 5-1-2022 **********************/
/***********************   VERSION : 1.00   *********************/
/****************************************************************/
/****************************************************************/

/*preprocessor file guard */

#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_


// function to send the command to the lcd
void CLCD_voidSendCommand (u8 Copy_u8Command);

//function to send the data to the lcd
void CLCD_voidSendData (u8 Copy_u8Data);

//function to initilaize mode of the lcd

void CLCD_voidInit (void);

void CLCD_voidSendString(const char * Copy_phString );

void CLCD_voidSendNumber (u32 Copy_u32Number);

void CLCD_voidCalcu (void);

void CLCD_voidGotoXY (u8 Copy_u8PosX ,u8 Copy_u8PosY);

void CLCD_voidFullLcd (const char * Copy_pu8String ,u8 Copy_u8PosX ,u8 Copy_u8PosY);

void CLCD_voidWriteSpecialCharacter(const char *Copy_pu8String ,u8 Copy_u8NumberPatttern,u8 Copy_u8PosX, u8 Copy_u8PosY);


void CLCD_sinusoidal (const char* arr ,u8 Copy_u8PosX, u8 Copy_u8PosY,u8 size);


#endif
