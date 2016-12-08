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

#include <string.h>
#include <stdio.h>
#include "controller_app.h"
#include "display_app.h"
#include "joystick_app.h"
#include "laser_app.h"
#include "servos_app.h"
#include "globals.h"
#include "text_generator.h"
#include <cmsis_os.h>
#include "Serial.h"


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

extern osMessageQId laser_mq_in;
extern osMessageQId servos_mq_in;
extern osPoolId controller_message_pool;
extern osMessageQId controller_mq;
extern osPoolId display_message_pool;
extern osMessageQId display_mq;

/** 
* @brief Contains the current x position of the laser/servos
**/
float laser_position_x;

/**
* @brief Contains the current y position of the laser/servos
**/
float laser_position_y;

uint8_t current_menu_element_id;

char text_to_display[28] = "ouam pas :(\n";

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
    
    //SER_Initialize();
}

/** 
* @brief process general messages, coming from main() probably
*/
void controller_process_message(controllerMessageFormat_t* controller_message){
    controllerMessageFormat_t* next_message;
    switch(controller_message->message_type){
        case CONTROLLER_INIT:
            controller_init();
            osPoolFree(controller_message_pool, controller_message);
            return;
        case CONTROLLER_DRAW_TEXT:
            controller_state = DRAWING;
            controller_drawing_mode = FROM_TEXT;
        
            //osPoolFree(controller_message_pool, controller_message);
      
            next_message = (controllerMessageFormat_t *)osPoolAlloc(controller_message_pool);
            next_message->message_type = CONTROLLER_DRAW_TEXT_NEXT;
            next_message->x_pixel = 0;
            next_message->y_pixel = 0;
            next_message->character_idx = 0;
            osMessagePut(controller_mq, (uint32_t)next_message, osWaitForever);
            break;
        case CONTROLLER_DRAW_TEXT_NEXT:
            controller_draw_text(controller_message->character_idx, controller_message->x_pixel, controller_message->y_pixel);
            osPoolFree(controller_message_pool, controller_message);
        
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

void controller_draw_text(uint16_t character_index, uint16_t x_pixel, uint16_t y_pixel) {
    servosMailFormat_t* servosMessage;
    laserMailFormat_t* laserMessage;
    controllerMessageFormat_t* next_message;
    displayMessageFormat_t* display_message;
    displayMessageFormat_t* display_message_X;
    displayMessageFormat_t* display_message_Y;
    float x_coordinate;
    float y_coordinate;
    uint16_t absolute_pixel_x;
    uint16_t absolute_pixel_y;
    uint8_t pixel_state;
    osEvent evt;
    char x_row[15];
    char y_row[15];
    uint16_t x_shift = 5;
    uint16_t y_shift = 5;
    
    uint16_t next_x, next_y;
    uint16_t next_character_idx;
    uint16_t is_there_more = 1;
    
    // TODO: empty queues!
    
    // go gently to the starting point
    //printf("HELLOW\n");
    absolute_pixel_x = character_index*FONT_WIDTH + x_pixel+ x_shift - 3;
    absolute_pixel_y = y_pixel + y_shift - 3;
    /* align at 5,3 (bottom left) */
    text_generator_get_pixel_coordinate(&x_coordinate, &y_coordinate, absolute_pixel_x, absolute_pixel_y);

    /* send command to servo */
    servosMessage = (servosMailFormat_t *)osPoolAlloc(servos_mail_pool);
    servosMessage->message_type = SERVOS_GOTO_POSITION;
    servosMessage->x_position = x_coordinate;
    servosMessage->y_position = y_coordinate; 

    osMessagePut(servos_mq, (uint32_t)servosMessage, osWaitForever);
    evt = osMessageGet(servos_mq_in, osWaitForever);
    osDelay(50); /* ugly, very ugly */
    osPoolFree(servos_mail_pool, servosMessage);
        

    while(is_there_more == 1){
        
        if(y_pixel == 0){
            // go gently to the starting point
            //printf("HELLOW\n");
            absolute_pixel_x = character_index*FONT_WIDTH + x_pixel+ x_shift ;
            absolute_pixel_y = y_pixel + y_shift - 1;
            /* align at 5,3 (bottom left) */
            text_generator_get_pixel_coordinate(&x_coordinate, &y_coordinate, absolute_pixel_x, absolute_pixel_y);

            /* send command to servo */
            servosMessage = (servosMailFormat_t *)osPoolAlloc(servos_mail_pool);
            servosMessage->message_type = SERVOS_GOTO_POSITION;
            servosMessage->x_position = x_coordinate;
            servosMessage->y_position = y_coordinate; 

            osMessagePut(servos_mq, (uint32_t)servosMessage, osWaitForever);
            evt = osMessageGet(servos_mq_in, osWaitForever);
            osDelay(100); /* ugly, very ugly */
            osPoolFree(servos_mail_pool, servosMessage);
        }
        
        display_message = (displayMessageFormat_t*)osPoolAlloc(display_message_pool);
        display_message->message_type=DISPLAY_CLEAR_ALL;
        osMessagePut(display_mq, (uint32_t)display_message, osWaitForever);
        
        osDelay(100);
        //printf("HELLOW\n");
        absolute_pixel_x = character_index*FONT_WIDTH + x_pixel+ x_shift;
        absolute_pixel_y = y_pixel + y_shift;
        /* align at 5,3 (bottom left) */
        text_generator_get_pixel_coordinate(&x_coordinate, &y_coordinate, absolute_pixel_x, absolute_pixel_y);

        /* send command to servo */
        servosMessage = (servosMailFormat_t *)osPoolAlloc(servos_mail_pool);
        servosMessage->message_type = SERVOS_GOTO_POSITION;
        servosMessage->x_position = x_coordinate;
        servosMessage->y_position = y_coordinate;

        osMessagePut(servos_mq, (uint32_t)servosMessage, osWaitForever);
        evt = osMessageGet(servos_mq_in, osWaitForever);
        osDelay(100); /* ugly, very ugly */
        osPoolFree(servos_mail_pool, servosMessage);
        
        /*
        sprintf(x_row, "X: %02d %1.3f", absolute_pixel_x, x_coordinate);
        sprintf(y_row, "Y: %02d %1.3f", absolute_pixel_y, y_coordinate);
        
        display_message_X = (displayMessageFormat_t*)osPoolAlloc(display_message_pool);
        display_message_X->message_type=DISPLAY_WRITE;
        display_message_X->row_number=1;
        display_message_X->text=x_row;
        osMessagePut(display_mq, (uint32_t)display_message_X, osWaitForever);
        
        display_message_Y = (displayMessageFormat_t*)osPoolAlloc(display_message_pool);
        display_message_Y->message_type=DISPLAY_WRITE;
        display_message_Y->row_number=2;
        display_message_Y->text=y_row;
        osMessagePut(display_mq, (uint32_t)display_message_Y, osWaitForever);
*/ 
        
        /* wait additional time when coming from the top */
    /*    if(y_pixel == 0) {
            osDelay(2000);
        }*/

        /* send command to laser */
        pixel_state = text_generator_get_pixel(x_pixel, y_pixel, output_text[character_index]);
        if(1 == pixel_state){
            laserMessage = (laserMailFormat_t *)osPoolAlloc(laser_mail_pool);
            laserMessage->message_type = LASER_SET_STATUS;
            laserMessage->laser_state = 1;

            /* IS IT THE CORRECT MESSAGE QUEUE? */
            /* let the servos stabilize */
            osDelay(50);
            osMessagePut(laser_mq, (uint32_t)laserMessage, osWaitForever);
            evt = osMessageGet(laser_mq_in, osWaitForever);
            osDelay(200);
            osPoolFree(laser_mail_pool, laserMessage);
            osPoolFree(laser_mail_pool, evt.value.p);

            laserMessage = (laserMailFormat_t *)osPoolAlloc(laser_mail_pool);
            laserMessage->message_type = LASER_SET_STATUS;
            laserMessage->laser_state = 0;
            osMessagePut(laser_mq, (uint32_t)laserMessage, osWaitForever);
            evt = osMessageGet(laser_mq_in, osWaitForever);
            osDelay(20);
            osPoolFree(laser_mail_pool, laserMessage);
            osPoolFree(laser_mail_pool, evt.value.p);
        }
        
        is_there_more = text_generator_get_next_pixel_coordinates(&next_x, &next_y, &next_character_idx, x_pixel, y_pixel, character_index, output_text);
        x_pixel = next_x;
        y_pixel = next_y;
        character_index = next_character_idx;
        
        /*osDelay(30);
        osPoolFree(display_message_pool, display_message);
        osPoolFree(display_message_pool, display_message_X);
        osPoolFree(display_message_pool, display_message_Y);*/
    } /* end while loop */
    
    /* next pixel */
    
 
    if(is_there_more) {
        next_message = (controllerMessageFormat_t *)osPoolAlloc(controller_message_pool);
        next_message->message_type = CONTROLLER_DRAW_TEXT_NEXT;
        next_message->x_pixel = next_x;
        next_message->y_pixel = next_y;
        next_message->character_idx = next_character_idx;
        osMessagePut(controller_mq, (uint32_t)next_message, osWaitForever);
    }
}


