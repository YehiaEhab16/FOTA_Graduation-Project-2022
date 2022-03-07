/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer :MCAL                   ***********************/
/***********************   SWC (DRIVER):FPEC 			 ***********************/
/***********************   DATA : 7-3-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/


#ifndef FPEC_INTERFACE_H_
#define FPEC_INTERFACE_H_

/**
 * @def Initialized FPEC :
 * 		Initialize :
 * 					1-UnLock
 * 					2-FPEC Latency
 */
void FPEC_voidInit(void);
/**
 * @def Erase the specific Area in flash
 * @param Copy_u8StartPage Start Page
 * @param Copy_u8EndPage  End Page
 * @return Error Flag when erase  the Boot Loader code
 */
u8 FPEC_voidEraseFlashArea(u8 Copy_u8StartPage , u8 Copy_u8EndPage );

/**
 * @def Erase all flash memory
 * @return Error Flag when erase the boot loader code
 */

u8 FPEC_voidEraseFlash(void);



/**
 * @def FlashPageErase
 * @param Copy_u8PageNumber Enter the number of page that want to br erased
 * @return ErrorFlag : when the page in the boot loader pages
 */
u8 FPEC_voidFlashPageErase(u8 Copy_u8PageNumber);

/**
 * @def Write half Word
 * @param Copy_u32Address Address Data
 * @param Copy_u16Data half word address
 * @param Copy_u8Length length of data
 */
void FPEC_voidFlashWrite(u32 Copy_u32Address, u16* Copy_u16Data, u8 Copy_u8Length);









#endif

