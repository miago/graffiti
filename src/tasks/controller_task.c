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
#include "servos_app.h"
#include "joystick_app.h"
#include "laser_app.h"

/*----------------------------------------------------------------------------
 *      Thread 'Controller': Manages the whole system
 *---------------------------------------------------------------------------*/

osThreadId tid_controller;		// thread id
osThreadDef(Controller_Thread, osPriorityNormal, 1, 0);	// thread object

/* new a message queue for every component: JOYSTICK */
osMessageQId joystick_mq_in;																		//define the message queue
osMessageQDef (joystick_mq_in, 0x16, joystickMessageFormat_t);
extern osMessageQId joystick_mq;
extern osPoolId joystick_message_pool;

/* new a message queue for every component: SERVOS */
osMessageQId servos_mq_in;																		//define the message queue
osMessageQDef (servos_mq_in, 0x16, servosMessageFormat_t);
extern osMessageQId servos_mq;
extern osPoolId servos_message_pool;

/* new a message queue for every component: LASER*/
osMessageQId laser_mq_in;																		//define the message queue
osMessageQDef (laser_mq_in, 0x16, laserMessageFormat_t);
extern osMessageQId laser_mq;
extern osPoolId laser_message_pool;

osMessageQId controller_mq;
osMessageQDef (controller_mq, 0x10, controllerMessageFormat_t);
osPoolDef(controller_message_pool, 16, controllerMessageFormat_t);
osPoolId controller_message_pool;

/**
* Initialized the Joystick Thread
* @param controllerDataBlock
*/
int Controller_Thread_Init(controllerDataBlock_t * controllerDataBlock)
{
    servos_mq_in = osMessageCreate(osMessageQ(servos_mq_in), NULL);
    //servos_mail_pool = osPoolCreate(osPool(servos_mail_pool));
    laser_mq_in = osMessageCreate(osMessageQ(laser_mq_in), NULL); 
    controller_mq = osMessageCreate(osMessageQ(controller_mq),NULL);
    controller_message_pool = osPoolCreate(osPool(controller_message_pool));
    
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
    
    joystickMessageFormat_t* joystick_mail;
    controllerMessageFormat_t* controller_message;

	while (1) {
        
        /* get message from my own message queue */
        evt = osMessageGet(controller_mq, 1);
        if(evt.status == osEventMessage){
            controller_message = (controllerMessageFormat_t*)evt.value.p;
            controller_process_message(controller_message);
            //osPoolFree(controller_message_pool, controller_message);
        }
        
        evt = osMessageGet(joystick_mq_in, 1);
		if(evt.status == osEventMessage){ 
            joystick_mail = (joystickMessageFormat_t*)evt.value.p;	
            controller_process_joystick(joystick_mail); 
            osPoolFree(joystick_message_pool, joystick_mail);
		} 

		osThreadYield();	// suspend thread
	}
}

