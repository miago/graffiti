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

osMessageQId laser_mq;															
osMessageQDef (laser_mq, 0x16, laserMailFormat_t);

osPoolDef(laser_mail_pool, 16, laserMailFormat_t);
osPoolId laser_mail_pool;

osThreadId tid_Laser;		
osThreadDef(Laser_Thread, osPriorityNormal, 1, 0);

/**
* Initialized the Laser Thread
* @param laserDataBlock
*/

int Laser_Thread_Init(laserDataBlock_t * laserDataBlock)
{
    laser_mq = osMessageCreate(osMessageQ(laser_mq),NULL);
	tid_Laser = osThreadCreate(osThread(Laser_Thread), laserDataBlock);
	laserDataBlock->tid_Laser = tid_Laser;
    laser_mail_pool = osPoolCreate(osPool(laser_mail_pool));
    
	if (!tid_Laser)
		return (-1);

	return (0);
}

void Laser_Thread(void const *argument)
{
    osEvent evt;	
    laserMailFormat_t* laser_mail;

	while (1) {
        evt = osMessageGet(laser_mq, osWaitForever);
		if(evt.status == osEventMessage){
            laser_mail = (laserMailFormat_t*)evt.value.p;	
            laser_process_message(laser_mail);
            osPoolFree(laser_mail_pool, laser_mail);
		}
		osThreadYield();
	}
}

