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
 * @file servos_task.c
 * @author Mirco E. Gysin
 * @date 21 Nov 2016
 * @brief This file contains the layer for the servo thread
 */


#include <cmsis_os.h>
#include "servos_app.h"
#include "servos_task.h"


/*----------------------------------------------------------------------------
 *      Thread 'Servos': Thread to control the servos
 *---------------------------------------------------------------------------*/

osMessageQId servos_mq;																		//define the message queue
osMessageQDef (servos_mq, 0x16, servosMailFormat_t);

osPoolDef(servos_mail_pool, 16, servosMailFormat_t);																		//define memory pool
osPoolId servos_mail_pool;

osThreadId tid_Servos;		// thread id
osThreadDef(Servos_Thread, osPriorityNormal, 1, 0);	// thread object

/**
* Initialize the Servos Thread
* @param servosDataBlock
*/

int Servos_Thread_Init(servosDataBlock_t * servosDataBlock)
{
    servos_mq = osMessageCreate(osMessageQ(servos_mq),NULL);
	tid_Servos = osThreadCreate(osThread(Servos_Thread), servosDataBlock);
	servosDataBlock->tid_Servos = tid_Servos;
    servos_mail_pool = osPoolCreate(osPool(servos_mail_pool));
    
	if (!tid_Servos)
		return (-1);

	return (0);
}

void Servos_Thread(void const *argument)
{
    osEvent evt;	
    servosMailFormat_t* servos_mail;
	//threadData_t *value = (threadData_t *) argument;

	while (1) {
        evt = osMessageGet(servos_mq, osWaitForever);
		if(evt.status == osEventMessage){
            servos_mail = (servosMailFormat_t*)evt.value.p;	
            servos_process_message(servos_mail);
            osPoolFree(servos_mail_pool, servos_mail);
		}
		osThreadYield();	// suspend thread
	}
}
