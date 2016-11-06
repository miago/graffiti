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

void servos_init(void) {
	servos_pan_angle = SERVOS_INITIAL_PAN_ANGLE;
	servos_tilt_angle = SERVOS_INITIAL_TILT_ANGLE;
	servos_distance_to_wall = SERVOS_DISTANCE_TO_WALL;
}

float servos_get_pan_angle(void){
	return servos_pan_angle;
}

float servos_get_tilt_angle(void){
	return servos_tilt_angle;
}

void servos_set_pan_angle(float new_pan_angle){
	servos_pan_angle = new_pan_angle;
}

void servos_set_tilt_angle(float new_tilt_angle){
	servos_tilt_angle = new_tilt_angle;
}

/*	
	
*/

Angles servos_point_to_angles(Point* p) {
	Angles ang;
	
	ang.tilt = atan2(p->y, servos_distance_to_wall);
	ang.pan = atan2(p->x, servos_distance_to_wall);
	
	return ang;
}
