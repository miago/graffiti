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
 * @file laser_app.h
 * @author Mirco E. Gysin
 * @date 21 Nov 2016
 * @brief Header file of laser_app.c
 */

#ifndef LASER_APP_H
#define LASER_APP_H

#include "laser_task.h"
#include "laser_hal.h"

#define CANVAS_X_MIN -1
#define CANVAS_X_MAX +1
#define CANVAS_Y_MIN -0.5
#define CANVAS_Y_MAX +0.5

typedef enum
{
	/* Messages which can be sent to the laser */
	LASER_INIT = 2, /* Reuqest initialisation of laser */
	LASER_GET_STATUS = 3, /* Request status of the laser */
	LASER_SET_STATUS = 4, /* Request that laser is set to 
	the provided value */
	LASER_TOGGLE = 5, /* Request that the laser status 
	is toggled */

	/* Responses which the laser can give */
	LASER_OK = 10, /* This is the default response when the message
	has been executed correctly */
	LASER_ERROR = 11, /* This is the response given when an error occured */
	LASER_STATUS = 12 /* With this messsage the status of the laser
	is provided */
} laserMessageType_t;

typedef struct
{
	laserMessageType_t message_type;
    uint8_t laser_state;
} laserMessageFormat_t;

void laser_init(void);
void laser_set_on(void);
void laser_set_off(void);
laserMessageFormat_t* laser_process_message(laserMessageFormat_t* mail);

laser_status_t laser_get_status(void);

#endif 
