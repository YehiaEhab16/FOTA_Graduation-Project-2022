/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer : APP (Receive)         ***********************/
/***********************   DATE : 26-4-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/
#ifndef INTERFACE_H
#define INTERFACE_H


/************** ESP ***************/
//Send
#define DOWNLOAD_FILE			'1'
#define UPDATE_CHECK			'U'
#define RECORD_ACK				'a'

//Receive
#define UPDATE_NOTIFICATION		'P'
#define UpdateAvailable			'A'
#define NoUpdateAvailable		'N'

/************** USER ***************/
//Send
#define UpdateCheck_ID			(u8)0x73
#define DiagResult_ID			(u8)0x75
#define NO_ISSUES				'G'
#define FIRMWARE_ISSUE			'F'
#define HARDWARE_ISSUE			'H'

//Receive
#define Request_ID				(u8)0x64
#define UPDATE_REQUEST			'R'
#define DIAGNOSTICS_REQUEST		'S'
#define USER_RESPONSE_ID		(u8)0x46
#define ACCEPT_UPDATE			(u8)0x00
#define DECLINE_UPDATE			(u8)0x01

/************** App ***************/
//Send

//Receive

#define TEMP_SENSOR				0
#define MOTORS					1
#define COLLISION_SYSTEM		2

/************ Filter IDs *************/
#define	 APP_DIAGNOSTICS		(u8)0x31
#define  TEMP_SENSOR_ID         (u8)0x32
#define  MOTORS_ID		        (u8)0x33
#define  COLLISION_SYSTEM_ID    (u8)0x34
#define  APP_ACKNOWLEDGE		(u8)0x37


#define BUFFER_SIZE 			200


typedef enum
{
  IDLE   ,
  USER_RESPONSE ,
  USER_REQUEST ,
  DIAGNOSTICS   ,
  ESP_MSG    ,
  RECEIVE_UPDATE
}STATE_t;


void CAN_FIFO0_callback(void);
void UART_callback(void);
void CAN_DiagCallback(void);
void GetUpdate(void);
void MainInit();



#endif
