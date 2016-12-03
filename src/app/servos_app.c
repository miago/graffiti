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
/**
* @brief Stores the current tilt angle
 */
float servos_tilt_angle;
/**
* @brief Stores the current pan angle
 */
float servos_pan_angle;

/**
* @brief Stores the distance to the wall
*/
float servos_distance_to_wall;

/** 
* @brief This flag is 1 when the module is initialized
*/
uint8_t servos_initialized;

/**
* Initializes the servos unit
*/

void servos_init(void) {
	servos_pan_angle = SERVOS_INITIAL_PAN_ANGLE;
	servos_tilt_angle = SERVOS_INITIAL_TILT_ANGLE;
	servos_distance_to_wall = SERVOS_DISTANCE_TO_WALL;
	
    servos_init_hal();

    servos_initialized = 1;
}

/**
* Function to get the get the pan angle at the application level
* @retval provides the current pan angle
*/

float servos_get_pan_angle(void){
	return servos_pan_angle;
}

/**
* Function to get the get the tilt angle at the application level
* @retval provides the current tilt angle
*/

float servos_get_tilt_angle(void){
	return servos_tilt_angle;
}

/**
* Function to set the tilt angle at the application level
* @param new_tilt_angle desired angle
*/

void servos_set_pan_angle(float new_pan_angle){
    uint16_t tim_value = 0;
	servos_pan_angle = new_pan_angle;
    tim_value = servos_pan_angle_to_timervalue(new_pan_angle);
    servos_set_pan_angle_hal(tim_value);
}

/**
* Function to set the tilt angle at the application level
* @param new_tilt_angle desired angle
*/

void servos_set_tilt_angle(float new_tilt_angle){
    uint16_t tim_value = 0;
	servos_tilt_angle = new_tilt_angle;
    tim_value = servos_tilt_angle_to_timervalue(new_tilt_angle);
    servos_set_tilt_angle_hal(tim_value);
}

/**
* Set the servos such that the laser points to the desired point
* @param x x position of the beam
* @param y y posotion of the beam
*/
void servos_set_position(float x, float y){
    Angles ang;
    Point p;
    p.x = x;
    p.y = y;
    ang = servos_point_to_angles(&p);
    
    servos_set_tilt_angle(ang.tilt);
    servos_set_pan_angle(ang.pan);
}

/**	
* Translates a point on the wall, which go from -1 to +1 in x
* and from -0.5 to +0.5 in y, to the angles of the servos
* @param p point on the wall
* @retval angles angles of the servos
*/

Angles servos_point_to_angles(Point* p) {
	Angles ang;
	
	ang.tilt = atan2(p->y + 0.5, 1);
	
	
	ang.pan = atan2(p->x, 1);
	
	return ang;
}

/**
* This function calculates the needed t_on of the timer/PWM to set the 
* servo to the desired pan angle
* @param angle desired angle
* @retval value value for the output compare
*/

uint16_t servos_pan_angle_to_timervalue(float angle){
	/* 
		y = mx + q
		m = Dy / Dx = (value2 - value1) / (angle2 - angle1)
		q = y - mx = value2 - m*angle2
	*/
	float m, q;
	
	m = (SERVOS_PAN_SECOND_POINT_TIM_VALUE - SERVOS_PAN_FIRST_POINT_TIM_VALUE) / (SERVOS_PAN_SECOND_POINT_ANGLE - SERVOS_PAN_FIRST_POINT_ANGLE);
	
	q = SERVOS_PAN_SECOND_POINT_TIM_VALUE - m * SERVOS_PAN_SECOND_POINT_ANGLE;
	return (uint16_t)(m*angle + q);
}

/**
* This function calculates the needed t_on of the timer/PWM to set the 
* servo to the desired tilt angle
* @param angle desired angle
* @retval value value for the output compare
*/

uint16_t servos_tilt_angle_to_timervalue(float angle){
	/* 
		y = mx + q
		m = Dy / Dx = (value2 - value1) / (angle2 - angle1)
		q = y - mx = value2 - m*angle2
	*/
	float m, q;
	
	m = (SERVOS_TILT_SECOND_POINT_TIM_VALUE - SERVOS_TILT_FIRST_POINT_TIM_VALUE) / (SERVOS_TILT_SECOND_POINT_ANGLE - SERVOS_TILT_FIRST_POINT_ANGLE);
	
	q = SERVOS_TILT_SECOND_POINT_TIM_VALUE - m * SERVOS_TILT_SECOND_POINT_ANGLE;
	return (uint16_t)(m*angle + q);
}

servosMailFormat_t* servos_process_message(servosMailFormat_t* servos_mail)
{
	if( (servos_initialized == 0) && (servos_mail->message_type!=SERVOS_INIT)){
		servos_mail->message_type = SERVOS_ERROR;
		return servos_mail;
	}
    switch(servos_mail->message_type){
        case SERVOS_INIT:
            servos_init();
            servos_mail->message_type = SERVOS_OK;
            return servos_mail;
 
        case SERVOS_GOTO_POSITION:
            servos_set_position(servos_mail->x_position, servos_mail->y_position);
            servos_mail->message_type = SERVOS_OK;
            return servos_mail;

        default:
            servos_mail->message_type = SERVOS_ERROR;
            return servos_mail;
    }
}
