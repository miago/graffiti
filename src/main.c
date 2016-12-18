/**
* CMSIS-RTOS Starter application: Creates three identical threads for a LED
* @file     main.c
* @date     21.11.2016
* @version  1.0
* @author   bfh-ti/dnd1
* 
* @warning
* THE PRESENT SOFTWARE CODE IS FOR EDUCATIONAL PURPOSES ONLY, VOID OF ANY
* WARRANTY WHATSOEVER
*
* <h2><center>smile from time to time</center></h2>
*
*
* uVision MDK-ARM 5.21a or later
*/

/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#define osObjectsPublic		// define objects in main module
#include "osObjects.h"		

#include "stm32f10x.h"
#include "myAppData.h"
#include "laser_task.h"
#include "joystick_task.h"
#include "controller_task.h"
#include "servos_task.h"
#include "display_task.h"
#include "controller_app.h"
#include <stdio.h>
#include "alia.h"

extern void Init_Timers(void);

extern int Init_ThreadA(threadData_t *);

/**
* @brief data of the LED thread
**/
threadData_t threadData[3];

/**
* @brief data of the Controller
**/
controllerDataBlock_t controllerData;

/**
* @brief data of the Laser Task
**/
laserDataBlock_t laserData;
extern osPoolId laser_message_pool;
/**
* @brief pointer to a message for the laser task
**/
laserMessageFormat_t* laser_mail;
extern osMessageQId laser_mq;

/**
* @brief data of the Joystick Task
**/
joystickDataBlock_t joystickData;
extern osPoolId joystick_message_pool;
/**
* @brief pointer to a message for the joystick task
**/
joystickMessageFormat_t* joystick_mail;
extern osMessageQId joystick_mq;

/**
* @brief data of the Servos Task
**/
servosDataBlock_t servosData;
extern osPoolId servos_message_pool;
/**
* @brief pointer to a message for the servos task
**/
servosMessageFormat_t* servos_mail;
extern osMessageQId servos_mq;

/**
* @brief data of the Display Task
**/
displayDataBlock_t displayData;
extern osPoolId display_message_pool;
/**
* @brief pointer to a message for the display task
**/
displayMessageFormat_t* display_message;
extern osMessageQId display_mq;

/**
* @brief pointer to a controller message
**/ 
controllerMessageFormat_t* controller_message;
extern osMessageQId controller_mq;
extern osPoolId controller_message_pool;

/**
* @brief Text of the welcome message on the display
**/
char welcome_message[10] = "Welcome\n";

/*
 * main: initialize and start the system
 */

int main(void)
{
	initialisation();

	osKernelInitialize();	// initialize CMSIS-RTOS, stop scheduler

	// initialize peripherals here

	// create 'thread' functions that start executing,
	// example: tid_name = osThreadCreate (osThread(name), NULL);

	threadData[0].delay = 1000;
	threadData[0].pinId = GPIO_Pin_9;
	threadData[0].portId = GPIOA;
	threadData[0].beepFreq = 1;
	threadData[0].beepTime = 1;
	Init_ThreadA(&threadData[0]);
    
    // init controller
    
    Controller_Thread_Init(&controllerData);
    
    controller_message = (controllerMessageFormat_t *)osPoolAlloc(controller_message_pool);
    controller_message->message_type = CONTROLLER_INIT;
    osMessagePut(controller_mq, (uint32_t)controller_message, osWaitForever);
    
    // init joystick
    
    Joystick_Thread_Init(&joystickData);
    joystick_mail = (joystickMessageFormat_t *)osPoolAlloc(joystick_message_pool);
    joystick_mail->message_type = JOYSTICK_INIT;
    osMessagePut(joystick_mq, (uint32_t)joystick_mail, osWaitForever);
   
    // init laser
    
    Laser_Thread_Init(&laserData);
    
    laser_mail = (laserMessageFormat_t *)osPoolAlloc(laser_message_pool);
    laser_mail->message_type = LASER_INIT;
    laser_mail->laser_state = 0;
    osMessagePut(laser_mq, (uint32_t)laser_mail, osWaitForever);
    
    /*laser_mail = (laserMessageFormat_t *)osPoolAlloc(laser_mail_pool);
    laser_mail->message_type = LASER_SET_STATUS;
    laser_mail->laser_state = 0;
    osMessagePut(laser_mq, (uint32_t)laser_mail, osWaitForever); */
    
    
    // init display
    
    Display_Thread_Init(&displayData);
    
    display_message = (displayMessageFormat_t *)osPoolAlloc(display_message_pool);
    display_message->message_type = DISPLAY_INIT;
    osMessagePut(display_mq, (uint32_t)display_message, osWaitForever);
    
    display_message = (displayMessageFormat_t *)osPoolAlloc(display_message_pool);
    display_message->message_type = DISPLAY_WRITE;
    display_message->row_number = 1;
    display_message->text = welcome_message;
    osMessagePut(display_mq, (uint32_t)display_message, osWaitForever);

    
    // init servos
    
    Servos_Thread_Init(&servosData);
    
    servos_mail = (servosMessageFormat_t *)osPoolAlloc(servos_message_pool);
    servos_mail->message_type = SERVOS_INIT;
    osMessagePut(servos_mq, (uint32_t)servos_mail, osWaitForever);
    
    servos_mail = (servosMessageFormat_t *)osPoolAlloc(servos_message_pool);
    servos_mail->message_type = SERVOS_GOTO_POSITION;
    servos_mail->x_position = +0.0;
    servos_mail->y_position = +0.0;
    osMessagePut(servos_mq, (uint32_t)servos_mail, osWaitForever);
      

    // send command to controller to begin writing the test
    
    osDelay(500); /* should be sufficient! */
    
    controller_message = (controllerMessageFormat_t *)osPoolAlloc(controller_message_pool);
    controller_message->message_type = CONTROLLER_DRAW_TEXT;
    osMessagePut(controller_mq, (uint32_t)controller_message, osWaitForever);

	Init_Timers();

	osKernelStart();	// start thread execution 
}
