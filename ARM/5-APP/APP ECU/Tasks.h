/*******************************************************************************/
/*******************************************************************************/
/***********************   GRADUATION PROJECT : (FOTA)  ***********************/
/***********************   Layer :App ECU Application   ***********************/
/***********************   DATA : 10/5/2022 			***********************/
/*******************************************************************************/
/*******************************************************************************/

#ifndef TASKS_H_
#define TASKS_H_


/**
 * @def Activate buzzer and LED for collision avoidance
 */
void Task_voidAlert(void);

/**
 * @def read direction from 2 switches to indicate forward or backward motion
 * @return Direction (FORWARD, BACKWARD)
 */ 
u8 Task_u8ReadDirection(void);

/**
 * @def read temperature from sensor
 * @return temperature value
 */ 
u8 Task_u8ReadTemperature(void);

/**
 * @def read distance from Ultrasonic sensor
 * @return distance value
 */
u8 Task_u8ReadDistance(void);

/**
 * @def check for malfunctions in system
 * @return error state (error in vehicle)
 */ 
u8 Task_u8SystemCheck(void);

/**
 * @def move vehicle forward or backward
 * @param Copy_u8Direction Direction of motion
 * @return temperature value
 */ 
u8 Task_u8MoveVehicle(u8 Copy_u8Direction);

/**
 * @def recieve update or diagnostics request
 * @return recieved message
 */ 
u8 Task_u8RecieveRequest(void);

/**
 * @def send diagnostics data to Main ECU
 * @param Copy_u8Message message to be sent
 */ 
void Task_voidSendDiagnostics(u8 Copy_u8Message);


#endif

