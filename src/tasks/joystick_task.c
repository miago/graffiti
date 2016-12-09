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

osMessageQId joystick_mq;																		//define the message queue
osMessageQDef (joystick_mq, 0x16, joystickMessageFormat_t);
extern osMessageQId joystick_mq_in;

osPoolDef(joystick_message_pool, 16, joystickMessageFormat_t);																		//define memory pool
osPoolId joystick_message_pool;

/**
* Initialized the Joystick Thread
* @param joystickDataBlock
*/

int Joystick_Thread_Init(joystickDataBlock_t * joystickDataBlock)
{
	joystick_mq = osMessageCreate(osMessageQ(joystick_mq),NULL);
	tid_joystick = osThreadCreate(osThread(Joystick_Thread), joystickDataBlock);
	joystickDataBlock->tid_Joystick = tid_joystick;
    joystick_message_pool = osPoolCreate(osPool(joystick_message_pool));
    
	if (!tid_joystick)
		return (-1);

	return (0);
}

void Joystick_Thread(void const *argument)
{
    osEvent evt;	
    joystickMessageFormat_t* joystick_mail;
	//threadData_t *value = (threadData_t *) argument;

	while (1) {
        evt = osMessageGet(joystick_mq, 1);
		if(evt.status == osEventMessage){
            joystick_mail = (joystickMessageFormat_t*)evt.value.p;	
            joystick_process_message(joystick_mail);
            osPoolFree(joystick_message_pool, joystick_mail);
		}
        
        osDelay(50);
        joystick_mail = (joystickMessageFormat_t*) osPoolAlloc(joystick_message_pool);
        if(joystick_mail) {
            joystick_mail->message_type = JOYSTICK_UPDATE_REQ;
            joystick_mail = joystick_process_message(joystick_mail);
            osMessagePut(joystick_mq_in, (uint32_t)joystick_mail, osWaitForever);
        } else
        {
            joystick_mail = (joystickMessageFormat_t*) 1337;
        }
       
		osThreadYield();	// suspend thread
	}
}

