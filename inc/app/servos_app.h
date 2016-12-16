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
	SERVOS_INIT = 0,
    SERVOS_GOTO_POSITION = 1, /* kindly asks the module to move the servo 
    to the specified position */
    SERVOS_DRAW_SQUARE = 2,
    SERVOS_DRAW_STAR = 3,

	/* commands from the servos module to other modules */
    SERVOS_OK = 10,
    SERVOS_ERROR = 11, /* when joystick has not been initialized */
} servosMessageType_t;

typedef struct {
    servosMessageType_t message_type;
    float x_position;
    float y_position;
} servosMessageFormat_t;


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
servosMessageFormat_t* servos_process_message(servosMessageFormat_t* servos_mail);
void servos_draw_square(void);
void servos_draw_star(void);
Point servos_get_point_of_spiral(float x, float y, float pixel_size, uint16_t windings, uint16_t point_number);
uint16_t servos_get_number_of_points_in_spiral(uint16_t number_of_windings);
float servos_get_interspiral_space(float pixel_size, uint16_t number_of_windings);

#endif
