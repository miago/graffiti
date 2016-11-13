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
 * @file servos_app.c
 * @author Mirco E. Gysin
 * @date 31 Oct 2016
 * @brief This file provides the functions for the configuration
				 and the control of the two servos
 */

#include "servos_hal.h"
#include "servos_app.h"
#include "math.h"

float servos_tilt_angle;
float servos_pan_angle;
float servos_distance_to_wall;
uint16_t servos_timer_period;

void servos_init(void) {
	servos_pan_angle = SERVOS_INITIAL_PAN_ANGLE;
	servos_tilt_angle = SERVOS_INITIAL_TILT_ANGLE;
	servos_distance_to_wall = SERVOS_DISTANCE_TO_WALL;

	servos_timer_period = servos_get_timer_period_hal(); 
	
    servos_init_hal();
}

float servos_get_pan_angle(void){
	return servos_pan_angle;
}

float servos_get_tilt_angle(void){
	return servos_tilt_angle;
}

void servos_set_pan_angle(float new_pan_angle){
    uint16_t tim_value = 0;
	servos_pan_angle = new_pan_angle;
    tim_value = servos_pan_angle_to_timervalue(new_pan_angle);
    servos_set_pan_angle_hal(tim_value);
}

void servos_set_tilt_angle(float new_tilt_angle){
    uint16_t tim_value = 0;
	servos_tilt_angle = new_tilt_angle;
    tim_value = servos_tilt_angle_to_timervalue(new_tilt_angle);
    servos_set_tilt_angle_hal(tim_value);
}


void servos_set_position(float x, float y){
    Angles ang;
    Point p;
    p.x = x;
    p.y = y;
    ang = servos_point_to_angles(&p);
    
    servos_set_tilt_angle(ang.tilt);
    servos_set_pan_angle(ang.pan);
}
/*	
	from -1 to +1 in x
	from -0.5 to +0.5 in y
*/

Angles servos_point_to_angles(Point* p) {
	Angles ang;
	
	ang.tilt = atan2(p->y + 0.5, 1);
	
	
	ang.pan = atan2(p->x, 1);
	
	return ang;
}

uint16_t servos_pan_angle_to_timervalue(float angle){
	/* angle is between 0 and pi, we have to
		bring it between 1 ms and 2ms
		Fullscale 1ms
	*/

	float value_1ms;
	float timer_value_float;
	uint16_t timer_value_uint16_t;

	value_1ms = ((float)servos_timer_period) / 20.0;
	timer_value_float = value_1ms * angle / (3.141592653589793);
	timer_value_float += value_1ms;
	timer_value_uint16_t = (uint16_t)timer_value_float;
	
	return timer_value_float;
}

uint16_t servos_tilt_angle_to_timervalue(float angle){
	/* angle is between 0 and pi/4, we have to
		bring it between 1 ms and 2ms
		Fullscale 1ms
		at zero angle, the servo must be at one extremity,
		-> 2ms
	*/

	float value_1ms;
	float timer_value_float;
	uint16_t timer_value_uint16_t;

	value_1ms = ((float)servos_timer_period) / 20.0;
	angle = 3.141592653589793 - angle;
	timer_value_float = timer_value_float = value_1ms * angle / (3.141592653589793);
	timer_value_float += value_1ms;
	timer_value_uint16_t = (uint16_t)timer_value_float;
	
	return timer_value_float;
}
