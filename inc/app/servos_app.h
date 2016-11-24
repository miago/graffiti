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
 * @file servos_app.h
 * @author Mirco E. Gysin
 * @date 21 Nov 2016
 * @brief Header file of servos_app.c
 */

#ifndef SERVOS_APP_H
#define SERVOS_APP_H

#include "servos_hal.h"

#define SERVOS_INITIAL_PAN_ANGLE 0
#define SERVOS_INITIAL_TILT_ANGLE 3.141592
#define SERVOS_DISTANCE_TO_WALL 1.3

typedef enum
{
	/* commands to the joystick module */
	SERVOS_INIT,
    SERVOS_GOTO_POSITION, /* kindly asks the module to move the servo 
    to the specified position */

	/* commands from the servos module to other modules */
    SERVOS_NO_REPLY,
    SERVOS_ERROR, /* when joystick has not been initialized */
} servoskMessageType_t;

typedef struct {
    servoskMessageType_t message_type;
    float x_position;
    float y_position;
} servosMailFormat_t;


void servos_init(void);
void servos_set_angles(float tilt_angle, float pan_angle);
void servos_set_position(float x, float y);
float servos_get_pan_angle(void);
float servos_get_tilt_angle(void);
void servos_set_pan_angle(float new_pan_angle);
void servos_set_tilt_angle(float new_tilt_angle);
Angles servos_point_to_angles(Point* p) ;
uint16_t servos_pan_angle_to_timervalue(float angle);
uint16_t servos_tilt_angle_to_timervalue(float angle);
void servos_process_message(servosMailFormat_t* servos_mail);

#endif
