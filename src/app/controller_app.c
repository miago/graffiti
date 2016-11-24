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
 * @file controller_app.c
 * @author Mirco E. Gysin
 * @date 23 Nov 2016
 * @brief This file contains the logic of the controller
 */

#include "controller_app.h"
#include "joystick_app.h"
#include "laser_app.h"
#include "servos_app.h"
#include <cmsis_os.h>

#define INCREMENT_STEP 0.02

controllerState_t controller_state;
drawingMode_t controller_drawing_mode;

extern osMessageQId laser_mq;
extern osPoolId laser_mail_pool;

extern osMessageQId servos_mq;
extern osPoolId servos_mail_pool;

float laser_position_x;
float laser_position_y;

void controller_init(void)
{
	controller_state = INITIALIZED;
	controller_drawing_mode = FREE_DRAWING;
    
    laser_position_x = 0;
    laser_position_y = 0;
}

void controller_process_laser(laserMailFormat_t * laser_mail) 
{

}

void controller_process_joystick(joystickMailFormat_t * joystick_mail) 
{
    laserMailFormat_t * laser_mail;
    servosMailFormat_t * servos_mail;
    
	if(controller_drawing_mode == FREE_DRAWING) {
		if(joystick_mail->message_type == JOYSTICK_UPDATED_VALUES) {
            if(joystick_mail->joystick_event->center == JOYSTICK_EVT_PRESSED) {
                laser_mail = (laserMailFormat_t*) osPoolAlloc(laser_mail_pool);
                if(laser_mail){
                    laser_mail->message_type = LASER_TOGGLE;
                    osMessagePut(laser_mq, (uint32_t)laser_mail, osWaitForever);
                }
            }
            if(joystick_mail->joystick_event->up == JOYSTICK_EVT_PRESSED){
                controller_increment_y_position();
                servos_mail = (servosMailFormat_t*) osPoolAlloc(servos_mail_pool);
                if(servos_mail){
                    servos_mail->message_type = SERVOS_GOTO_POSITION;
                    servos_mail->x_position = laser_position_x;
                    servos_mail->y_position = laser_position_y;
                    osMessagePut(servos_mq, (uint32_t)servos_mail, osWaitForever);
                }
            }
            
            if(joystick_mail->joystick_event->down == JOYSTICK_EVT_PRESSED){
                controller_decrement_y_position();
                servos_mail = (servosMailFormat_t*) osPoolAlloc(servos_mail_pool);
                if(servos_mail){
                    servos_mail->message_type = SERVOS_GOTO_POSITION;
                    servos_mail->x_position = laser_position_x;
                    servos_mail->y_position = laser_position_y;
                    osMessagePut(servos_mq, (uint32_t)servos_mail, osWaitForever);
                }
            }
            
            if(joystick_mail->joystick_event->right == JOYSTICK_EVT_PRESSED){
                controller_decrement_x_position();
                servos_mail = (servosMailFormat_t*) osPoolAlloc(servos_mail_pool);
                if(servos_mail){
                    servos_mail->message_type = SERVOS_GOTO_POSITION;
                    servos_mail->x_position = laser_position_x;
                    servos_mail->y_position = laser_position_y;
                    osMessagePut(servos_mq, (uint32_t)servos_mail, osWaitForever);
                }
            }
            
            if(joystick_mail->joystick_event->left == JOYSTICK_EVT_PRESSED){
                controller_increment_x_position();
                servos_mail = (servosMailFormat_t*) osPoolAlloc(servos_mail_pool);
                if(servos_mail){
                    servos_mail->message_type = SERVOS_GOTO_POSITION;
                    servos_mail->x_position = laser_position_x;
                    servos_mail->y_position = laser_position_y;
                    osMessagePut(servos_mq, (uint32_t)servos_mail, osWaitForever);
                }
            }
        }   
	}
}

void controller_increment_x_position(void){
    laser_position_x += INCREMENT_STEP;
    if(laser_position_x > 1)
    {
        laser_position_x = 1;
    }
}

void controller_decrement_x_position(void){
    laser_position_x -= INCREMENT_STEP;
    if(laser_position_x < -1)
    {
        laser_position_x = -1;
    }
}

void controller_increment_y_position(void){
    laser_position_y += INCREMENT_STEP;
    if(laser_position_y > 0.5)
    {
        laser_position_y = 0.5;
    }
}

void controller_decrement_y_position(void){
    laser_position_y -= INCREMENT_STEP;
    if(laser_position_y < -0.5)
    {
        laser_position_y = -0.5;
    }
}
