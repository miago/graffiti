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
 * @file joystick_task.c
 * @author Mirco E. Gysin
 * @date 22 Nov 2016
 * @brief This file contains the joystick for the thread
 */


#include <cmsis_os.h>
#include "joystick_app.h"
#include "joystick_task.h"


/*----------------------------------------------------------------------------
 *      Thread 'Joystick': Thread to control the joystick
 *---------------------------------------------------------------------------*/

osThreadId tid_joystick;		// thread id
osThreadDef(Joystick_Thread, osPriorityNormal, 1, 0);	// thread object

osMailQDef(joystick_mail_box, 3, joystickMailFormat_t);
osMailQId joystick_mail_box;

/**
* Initialized the Joystick Thread
* @param joystickDataBlock
*/

int Joystick_Thread_Init(joystickDataBlock_t * joystickDataBlock)
{
	joystick_mail_box = osMailCreate(osMailQ(joystick_mail_box), NULL);
	tid_joystick = osThreadCreate(osThread(Joystick_Thread), joystickDataBlock);
	joystickDataBlock->tid_Joystick = tid_joystick;
	if (!tid_joystick)
		return (-1);

	return (0);
}

void Joystick_Thread(void const *argument)
{

    osEvent evt;
	joystickDataBlock_t *value = (joystickDataBlock_t *) argument;

	while (1) {
		evt = osMailGet(joystick_mail_box, osWaitForever);
		if(evt.status == osEventMail){
			
		}
		osThreadYield();	// suspend thread
	}
}

