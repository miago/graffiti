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
* @section sHw Hardware used
*
* Nucleo64STM32F103
*
* @section sIde Development tool used
*
* uVision MDK-ARM 5.21a or later
*/

/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#define osObjectsPublic		// define objects in main module
#include "osObjects.h"		// RTOS object definitions

#include "stm32f10x.h"
#include "myAppData.h"
#include "laser_task.h"
#include "joystick_task.h"
#include "controller_task.h"
#include "servos_task.h"
#include <stdio.h>

extern void Init_Timers(void);

extern int Init_ThreadA(threadData_t *);


threadData_t threadData[3];

controllerDataBlock_t controllerData;

laserDataBlock_t laserData;
extern osPoolId laser_mail_pool;
laserMailFormat_t* laser_mail;
extern osMessageQId laser_mq;

joystickDataBlock_t joystickData;
extern osPoolId joystick_mail_pool;
joystickMailFormat_t* joystick_mail;
extern osMessageQId joystick_mq;

servosDataBlock_t servosData;
extern osPoolId servos_mail_pool;
servosMailFormat_t* servos_mail;
extern osMessageQId servos_mq;


char text[20];

void RCC_Configuration(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Joystick center button input for button reading */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//$TASK LED on Nucleo
	/* 
	   red D5 PB4
	   green D9 PC7
	   blue D8 PA9
	 */
	// Blue LED on PA9, Arduino D8
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// Green LED on PC7, Arduino D9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	// Red LED on PB4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// Blue LED pin PB4 JTAG  JNTRST pin must be Alternate Remap to be a GPIO
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST, ENABLE);

	// Active low elements, so switch them on!
	GPIO_SetBits(GPIOA, GPIO_Pin_9);
	GPIO_SetBits(GPIOC, GPIO_Pin_7);
	GPIO_SetBits(GPIOB, GPIO_Pin_4);

}

/**
* Initialisation code 
*/
void initialisation(void)
{

	SystemCoreClockUpdate();

	RCC_Configuration();
	GPIO_Configuration();
}

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
    
    // init joystick
    
    Joystick_Thread_Init(&joystickData);
    joystick_mail = (joystickMailFormat_t *)osPoolAlloc(joystick_mail_pool);
    joystick_mail->message_type = JOYSTICK_INIT;
    osMessagePut(joystick_mq, (uint32_t)joystick_mail, osWaitForever);
   
    // init laser
    
    Laser_Thread_Init(&laserData);
    
    laser_mail = (laserMailFormat_t *)osPoolAlloc(laser_mail_pool);
    laser_mail->message_type = LASER_INIT;
    laser_mail->laser_state = 0;
    osMessagePut(laser_mq, (uint32_t)laser_mail, osWaitForever);
    
    laser_mail = (laserMailFormat_t *)osPoolAlloc(laser_mail_pool);
    laser_mail->message_type = LASER_SET_STATUS;
    laser_mail->laser_state = 1;
    osMessagePut(laser_mq, (uint32_t)laser_mail, osWaitForever);
    
    // init servos
    
    Servos_Thread_Init(&servosData);
    
    servos_mail = (servosMailFormat_t *)osPoolAlloc(servos_mail_pool);
    servos_mail->message_type = SERVOS_INIT;
    osMessagePut(servos_mq, (uint32_t)servos_mail, osWaitForever);
    

	Init_Timers();

	osKernelStart();	// start thread execution 
}
