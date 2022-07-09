/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)   ***********************/
/***********************   Layer : APP (Receive)         ***********************/
/***********************   DATE : 26-4-2022  			 ***********************/
/*******************************************************************************/
/*******************************************************************************/
#ifndef INTERFACE_H
#define INTERFACE_H


/********************* ESP *********************/
//Send
#define DOWNLOAD_FILE			        '1'
#define UPDATE_CHECK			        'U'
#define RECORD_ACK				        'a'

//Receive
#define UPDATE_NOTIFICATION		        'P'
#define UpdateAvailable			        'A'
#define NoUpdateAvailable		        'N'

/********************* USER *********************/
//Send
#define UpdateCheck_ID			     (u8)0x73
#define MOTOR_ISSUES			     	'M'
#define TEMP_SENSOR_ISSUE		     	'T'
#define CollisionSysIssue		     	'C'


//Receive
#define Request_ID				     (u8)0x64
#define UPDATE_REQUEST			     'R'
#define DIAGNOSTICS_REQUEST		     'S'
#define ACCEPT_UPDATE			     (u8)30
#define DECLINE_UPDATE			     (u8)35

/********************* App *********************/
//Send

//Receive
#define APP_RxCollisionSysIssue		(u8)0b00000001
#define APP_RxTempSensorIssue		(u8)0b00000010
#define APP_RxMotorIssue			(u8)0b00000100


/****************** Filter IDs *****************/
#define  APP_ACKNOWLEDGE		       (u8)0x30
#define  USER_REQUEST_ID		       (u8)0x36
#define  USER_RESPONSE_ID		       (u8)0x32
#define  APP_DIAG_M1			       (u8)0x38
#define  APP_DIAG_M2			       (u8)0x31


#define BUFFER_SIZE 					100


typedef enum
{
  IDLE   ,
  USER_RESPONSE ,
  USER_REQUEST ,
  DIAGNOSTICS   ,
  START_UPDATE,
  RECEIVE_RECORD
}STATE_t;


void CAN_FIFO0_callback(void);
void UART_callback(void);
void CAN_AppAckCallback(void);
void GetUpdate(void);
void MainInit();



#endif
