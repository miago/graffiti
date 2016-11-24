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


/*----------------------------------------------------------------------------
 *      Thread 'Controller': Manages the whole system
 *---------------------------------------------------------------------------*/

osThreadId tid_controller;		// thread id
osThreadDef(Controller_Thread, osPriorityNormal, 1, 0);	// thread object

extern osMailQId joystick_mail_box;

/**
* Initialized the Joystick Thread
* @param joystickDataBlock
*/

int Controller_Thread_Init(controllerDataBlock_t * controllerDataBlock)
{
	tid_controller = osThreadCreate(osThread(Controller_Thread), controllerDataBlock);
	controllerDataBlock->tid_Controller = tid_controller;
	if (!tid_controller)
		return (-1);

	return (0);
}

void Controller_Thread(void const *argument)
{
    osEvent evt;
    
	controllerDataBlock_t *value = (controllerDataBlock_t *) argument;

	while (1) {
		evt = osMailGet(joystick_mail_box, osWaitForever);
		if(evt.status == osEventMail){
			
		}
		osThreadYield();	// suspend thread
	}
}

