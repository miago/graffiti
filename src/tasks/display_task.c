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
 * @file display_task.c
 * @author Mirco E. Gysin
 * @date 04 Dec 2016
 */


#include <cmsis_os.h>
#include "display_app.h"
#include "display_task.h"


/*----------------------------------------------------------------------------
 *      Thread 'Display': Thread to control the display
 *---------------------------------------------------------------------------*/


osThreadId tid_display;		// thread id
osThreadDef(Display_Thread, osPriorityNormal, 1, 0);	// thread object

osMessageQId display_mq;																		//define the message queue
osMessageQDef (display_mq, 0x16, displayMessageFormat_t);
extern osMessageQId display_mq_in;

osPoolDef(display_message_pool, 16, displayMessageFormat_t);																		//define memory pool
osPoolId display_message_pool;

/**
* Initialized the Display Thread
* @param displayDataBlock
*/

int Display_Thread_Init(displayDataBlock_t * displayDataBlock)
{
	display_mq = osMessageCreate(osMessageQ(display_mq),NULL);
	tid_display = osThreadCreate(osThread(Display_Thread), displayDataBlock);
	displayDataBlock->tid_Display = tid_display;
    display_message_pool = osPoolCreate(osPool(display_message_pool));
    
	if (!tid_display)
		return (-1);

	return (0);
}

void Display_Thread(void const *argument)
{
    osEvent evt;	
    displayMessageFormat_t* display_message;
	//threadData_t *value = (threadData_t *) argument;

	while (1) {
        evt = osMessageGet(display_mq, osWaitForever);
		if(evt.status == osEventMessage){
            display_message = (displayMessageFormat_t*)evt.value.p;	
            display_process_message(display_message);
            osPoolFree(display_message_pool, display_message);
		}
        
		osThreadYield();	// suspend thread
	}
}

