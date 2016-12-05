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
 * @file controller_app.h
 * @author Mirco E. Gysin
 * @date 23 Nov 2016
 * @brief This file contains the definitions for controller_app.c
 */

#ifndef CONTROLLER_APP_H
#define CONTROLLER_APP_H

#include "laser_app.h"
#include "joystick_app.h"

typedef enum {
	UNINIT,
	INITIALIZED, /* here we can select our program */
	DRAWING
} controllerState_t;

typedef enum {
	CIRCLE,
	FREE_DRAWING,
	FROM_TEXT
} drawingMode_t;

void controller_init(void);
void controller_process_laser(laserMailFormat_t * laser_mail);
void controller_process_joystick(joystickMailFormat_t * joystick_mail);

void controller_increment_x_position(void);
void controller_decrement_x_position(void);
void controller_increment_y_position(void);
void controller_decrement_y_position(void);

#endif
