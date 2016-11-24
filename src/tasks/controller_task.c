/* 
 * This file is part of the Graffiti distribution 
 * (https://github.com/miago/graffiti).
 * Copyright (c) 2016 Mirco Gysin.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file controller_task.c
 * @author Mirco E. Gysin
 * @date 23 Nov 2016
 * @brief This file contains the interface for the controller logic
 */


#include <cmsis_os.h>
#include "controller_app.h"
#include "controller_task.h"
#include "joystick_app.h"
#include "laser_app.h"

/*----------------------------------------------------------------------------
 *      Thread 'Controller': Manages the whole system
 *---------------------------------------------------------------------------*/

osThreadId tid_controller;		// thread id
osThreadDef(Controller_Thread, osPriorityNormal, 1, 0);	// thread object

/* new a message queue for every component: JOYSTICK */
osMessageQId joystick_mq_in;																		//define the message queue
osMessageQDef (joystick_mq_in, 0x16, joystickMailFormat_t);
extern osMessageQId joystick_mq;
extern osPoolId joystick_mail_pool;

/* new a message queue for every component: LASER*/
osMessageQId laser_mq_in;																		//define the message queue
osMessageQDef (laser_mq_in, 0x16, laserMailFormat_t);
extern osMessageQId laser_mq;
extern osPoolId laser_mail_pool;
/**
* Initialized the Joystick Thread
* @param joystickDataBlock
*/

int Controller_Thread_Init(controllerDataBlock_t * controllerDataBlock)
{
    joystick_mq_in = osMessageCreate(osMessageQ(joystick_mq_in),NULL);
	tid_controller = osThreadCreate(osThread(Controller_Thread), controllerDataBlock);
	controllerDataBlock->tid_Controller = tid_controller;
	if (!tid_controller)
		return (-1);

	return (0);
}

void Controller_Thread(void const *argument)
{
    osEvent evt;
    
    joystickMailFormat_t* joystick_mail;

	while (1) {
        evt = osMessageGet(joystick_mq_in, 1);
		if(evt.status == osEventMessage){ 
            joystick_mail = (joystickMailFormat_t*)evt.value.p;	
            controller_process_joystick(joystick_mail);
            
            osPoolFree(joystick_mail_pool, joystick_mail);
		} 

		osThreadYield();	// suspend thread
	}
}

