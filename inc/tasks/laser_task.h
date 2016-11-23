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
 * @file laser_task.h
 * @author Mirco E. Gysin
 * @date 23 Nov 2016
 * @brief Header file of laser_task.c
 */

#ifndef LASER_TASK_H
#define LASER_TASK_H

#include <stdint.h>
#include <cmsis_os.h>
#include "laser_app.h"
#include "laser_hal.h"

typedef enum
{
	/* Messages which can be sent to the laser */
	INIT, /* Reuqest initialisation of laser */
	GET_STATUS, /* Request status of the laser */
	SET_STATUS, /* Request that laser is set to 
	the provided value */
	TOGGLE, /* Request that the laser status 
	is toggled */


	/* Responses which the laser can give */
	OK, /* This is the default response when the message
	has been executed correctly */
	ERROR, /* This is the response given when an error occured */
	STATUS /* With this messsage the status of the led
	is provided */
} laserMessageType_t;

typedef struct 
{
    osThreadId tid_Laser;           //!< Handle to the current thread
} laserDataBlock_t;                 //!< Thread Data block defined

typedef struct
{
	laserMessageType_t message_type;
    uint8_t laser_state;
    uint8_t toggle;
} laserMailFormat_t;

/* function prototypes */ 
void Laser_Thread(void const *argument);
int Laser_Thread_Init(laserDataBlock_t * laserDataBlock);

#endif
