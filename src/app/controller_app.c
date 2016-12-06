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
#include "globals.h"
#include "text_generator.h"
#include <cmsis_os.h>


/**
* @brief contains the width of a character (pixel)
**/
uint16_t controller_font_width;

/**
* @brief contains the height of a characters (pixel)
**/
uint16_t controller_font_height;

/** 
* @brief Increment step for manual drawing
*/
#define INCREMENT_STEP 0.02

/**
* @brief Contains the state of the controller
**/
controllerState_t controller_state;

/**
* @brief Contains the drawing status of the controller
**/
drawingMode_t controller_drawing_mode;

extern osMessageQId laser_mq;
extern osPoolId laser_mail_pool;

extern osMessageQId servos_mq;
extern osPoolId servos_mail_pool;

/** 
* @brief Contains the current x position of the laser/servos
**/
float laser_position_x;

/**
* @brief Contains the current y position of the laser/servos
**/
float laser_position_y;

uint8_t current_menu_element_id;

char text_to_display[6] = "Mirco\n";

/**
* @brief this variable points to a \n terminated string containg the text to display
*/
char* output_text;

/**
* @brief Initializes the controller 
**/
void controller_init(void)
{
	controller_state = INITIALIZED;
    
    controller_state = DRAWING;
	controller_drawing_mode = FREE_DRAWING;
    
    laser_position_x = 0;
    laser_position_y = 0;

    output_text = text_to_display;

    controller_font_height = FONT_HEIGHT;
    controller_font_width = FONT_WIDTH;
}

/** 
* @brief process general messages, coming from main() probably
*/
void controller_process_message(controllerMessageFormat_t* controller_message){
    switch(controller_message->message_type){
        case CONTROLLER_INIT:
            controller_init();
            return;
        case CONTROLLER_DRAW_TEXT:
            controller_state = DRAWING;
            controller_drawing_mode = FROM_TEXT;
            break;
        default:
            break;
    }
}

/**
* @brief Processes a message coming from the Laser module
**/
void controller_process_laser(laserMailFormat_t * laser_mail) 
{

}

/**
* @brief Processes a message coming from the Joystick module
**/
void controller_process_joystick(joystickMailFormat_t * joystick_mail) 
{
    laserMailFormat_t * laser_mail;
    servosMailFormat_t * servos_mail;

    if(controller_state == DRAWING){
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
}

/**
* @brief Increments the position by one step in x direction 
**/
void controller_increment_x_position(void){
    laser_position_x += INCREMENT_STEP;
    if(laser_position_x > 1)
    {
        laser_position_x = 1;
    }
}

/**
* @brief Decrements the position by one step in x direction 
**/
void controller_decrement_x_position(void){
    laser_position_x -= INCREMENT_STEP;
    if(laser_position_x < -1)
    {
        laser_position_x = -1;
    }
}

/**
* @brief Increments the position by one step in y direction 
**/
void controller_increment_y_position(void){
    laser_position_y += INCREMENT_STEP;
    if(laser_position_y > 0.5)
    {
        laser_position_y = 0.5;
    }
}

/**
* @brief Decrements the position by one step in y direction 
**/
void controller_decrement_y_position(void){
    laser_position_y -= INCREMENT_STEP;
    if(laser_position_y < -0.5)
    {
        laser_position_y = -0.5;
    }
}


/**
* @brief function which draws one pixel at a time,
* it begins at (0,0) (bottom left) of the first character. 
* The next pixel is the one with the y coordinate incremented by one
* with the same x coordinate, which means that the next pixel is (1,0).
* When the maximum is reached (7 for example), the x coodinate 
* is incremented by 1 and the y coordinate is reset to 0.
*/

void controller_draw_text(uint8_t character_index, uint16_t x_pixel, uint16_t y_pixel) {
    servosMailFormat_t* servosMessage;
    laserMailFormat_t* laserMessage;
    float x_coordinate;
    float y_coordinate;
    uint16_t absolute_pixel_x;
    uint16_t absolute_pixel_y;
    uint8_t pixel_state;

    absolute_pixel_x = character_index*FONT_WIDTH + x_pixel;
    absolute_pixel_y = y_pixel;
    /* align at 0,0 (bottom left) */
    /* need the coordinate of the next pixel */
    text_generator_get_pixel_coordinate(&x_coordinate, &y_coordinate, absolute_pixel_x, absolute_pixel_y);

    /* send command to servo */
    servosMessage = (servosMailFormat_t *)osPoolAlloc(servos_mail_pool);
    servosMessage->message_type = SERVOS_GOTO_POSITION;
    servosMessage->x_position = x_coordinate;
    servosMessage->y_position = y_coordinate;

    osMessagePut(servos_mq, (uint32_t)servosMessage, osWaitForever);
    osDelay(50);
    osPoolFree(servos_mail_pool, servosMessage);

    /* send command to laser */
    pixel_state = text_generator_get_pixel(x_pixel, y_pixel, text_to_display[character_index]);
    if(1 == pixel_state){
        laserMessage = (laserMailFormat_t *)osPoolAlloc(laser_mail_pool);
        laserMessage->message_type = LASER_SET_STATUS;
        laserMessage->laser_state = 1;

        /* IS IT THE CORRECT MESSAGE QUEUE? */
        osMessagePut(laser_mq, (uint32_t)laserMessage, osWaitForever);
        evt = osMessageGet(laser_mq, 1);
        /*sDelay(50);*/
        osPoolFree(laser_mail_pool, laserMessage);

        laserMessage = (laserMailFormat_t *)osPoolAlloc(laser_mail_pool);
        laserMessage->message_type = LASER_SET_STATUS;
        laserMessage->laser_state = 0;
        osMessagePut(laser_mq, (uint32_t)laserMessage, osWaitForever);
        osDelay(50);
        osPoolFree(laser_mail_pool, laserMessage);
    }
}

/**
* @brief This function calculates the next pixel to be displayed. 
* Returns 0 if there is no more pixel to be displayes, 1 otherwise.
**/

uint8_t controller_get_next_pixel_coordinates(uint16_t* next_x, uint16_t* next_y, uint8_t* next_char_idx, uint16_t last_x, uint16_t last_y, uint8_t last_char_idx){
    *next_x = last_x;
    *next_y = last_y + 1;
    *next_char_idx = last_char_idx;

    if(*next_y == controller_font_height){
        *next_x = last_x + 1;
        *next_y = 0;
        if(*next_x == controller_font_width){
            *next_x = 0;
            *next_char_idx = last_char_idx+1;
            if(output_text[*next_char_idx] == '\n') {
                return 0;
            }
        }
    }

    return 1;
}