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
#define DOWNLOAD_FILE			        'k'
#define UPDATE_CHECK			        'U'
#define RECORD_ACK				        'a'

//Receive
#define UPDATE_NOTIFICATION		        'P'
#define APP1_DOWNLOADED					'2'
#define APP2_DOWNLOADED					'd'

/********************* USER *********************/
//Send
#define UpdateCheck_ID			     (u8)0x73
#define U_Notification				 (u8)45
#define UpdateComplete				 (u8)55
#define UpdateFailed				 (u8)60
#define MOTOR_ISSUES			     	'M'
#define TEMP_SENSOR_ISSUE		     	'T'
#define CollisionSysIssue		     	'C'


//Receive
#define Request_ID				     (u8)0x36
#define UPDATE_REQUEST			     65
#define DIAGNOSTICS_REQUEST		     40
#define ACCEPT_UPDATE			     (u8)30
#define DECLINE_UPDATE			     (u8)35

/********************* App *********************/
//Send

//Receive
#define StartTransmission			'A'
#define APP_RxCollisionSysIssue		(u8)0b00000001
#define APP_RxTempSensorIssue		(u8)0b00000010
#define APP_RxMotorIssue			(u8)0b00000100


/****************** Filter IDs *****************/
#define  APP_ACKNOWLEDGE		       0x30
#define  USER_REQUEST_ID		       (u8)0x36
#define  USER_RESPONSE_ID		       (u8)0x46
#define  APP1_DIAG_ID			       (u8)0x38
#define  APP2_DIAG_ID			       (u8)0x31


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

typedef enum
{
  NO_ERROR 		,
  DIST_DIR_M1	,
  DIST_M1		,
  DIR_M1		,
  DIST_DIR_M2	,
  DIST_M2		,
  DIR_M2
}Error_t;

void CAN_FIFO1_callback(void);
void UART_callback(void);
void CAN_AppAckCallback(void);
void GetUpdate(void);
void MainInit();



#endif
