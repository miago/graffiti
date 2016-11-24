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
#include <stdio.h>

extern void Init_Timers(void);

extern int Init_ThreadA(threadData_t *);

extern osMailQId laser_mail_box;

threadData_t threadData[3];
laserDataBlock_t laserData;

laserMailFormat_t* laser_mail;

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
    
    // init laser
    
    Laser_Thread_Init(&laserData);
    
    laser_mail = (laserMailFormat_t*)osMailAlloc(laser_mail_box, osWaitForever);	
    
    laser_mail->message_type = INIT;
    laser_mail->laser_state = 0;
    osMailPut(laser_mail_box, &laser_mail);	
    
    laser_mail = (laserMailFormat_t*)osMailAlloc(laser_mail_box, osWaitForever);
    laser_mail->message_type = SET_STATUS;
    laser_mail->laser_state = 1;
    
    osMailPut(laser_mail_box, &laser_mail);
    

	Init_Timers();

	osKernelStart();	// start thread execution 
}
