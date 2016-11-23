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
 * @file laser_task.c
 * @author Mirco E. Gysin
 * @date 21 Nov 2016
 * @brief This file contains the layer for the thread
 */


#include <cmsis_os.h>
#include "laser_app.h"
#include "laser_task.h"


/*----------------------------------------------------------------------------
 *      Thread 'Laser': Thread to control the laser beam
 *---------------------------------------------------------------------------*/

osMailQDef(laser_mail_box, 3, laserMailFormat_t);
osMailQId laser_mail_box;

osThreadId tid_Laser;		// thread id
osThreadDef(Laser_Thread, osPriorityNormal, 1, 0);	// thread object

/**
* Initialized the Laser Thread
* @param laserDataBlock
*/

int Laser_Thread_Init(laserDataBlock_t * laserDataBlock)
{
	laser_mail_box = osMailCreate(osMailQ(laser_mail_box), NULL);
	tid_Laser = osThreadCreate(osThread(Laser_Thread), laserDataBlock);
	laserDataBlock->tid_Laser = tid_Laser;
	if (!tid_Laser)
		return (-1);

	return (0);
}

void Laser_Thread(void const *argument)
{
    osEvent evt;	
	//threadData_t *value = (threadData_t *) argument;

	while (1) {
		evt = osMailGet(laser_mail_box, osWaitForever);
		if(evt.status == osEventMail){
			
		}
		osThreadYield();	// suspend thread
	}
}

