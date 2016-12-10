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
extern osPoolId laser_message_pool;

extern osMessageQId servos_mq;
extern osPoolId servos_message_pool;

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

char text_to_display[28] = " Mirco Gysin\n";

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

            controller_empty_message_queue(servos_mq, servos_message_pool);
            controller_empty_message_queue(servos_mq_in, servos_message_pool);
            controller_empty_message_queue(laser_mq, laser_message_pool);
            controller_empty_message_queue(laser_mq_in, laser_message_pool);
      
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
void controller_process_laser(laserMessageFormat_t * laser_mail) 
{

}

/**
* @brief Processes a message coming from the Joystick module
**/
void controller_process_joystick(joystickMessageFormat_t * joystick_mail) 
{
    laserMessageFormat_t * laser_mail;
    servosMessageFormat_t * servos_mail;

    if(controller_state == DRAWING){
    	if(controller_drawing_mode == FREE_DRAWING) {
    		if(joystick_mail->message_type == JOYSTICK_UPDATED_VALUES) {
                if(joystick_mail->joystick_event->center == JOYSTICK_EVT_PRESSED) {
                    laser_mail = (laserMessageFormat_t*) osPoolAlloc(laser_message_pool);
                    if(laser_mail){
                        laser_mail->message_type = LASER_TOGGLE;
                        osMessagePut(laser_mq, (uint32_t)laser_mail, osWaitForever);
                    }
                }
                if(joystick_mail->joystick_event->up == JOYSTICK_EVT_PRESSED){
                    controller_increment_y_position();
                    servos_mail = (servosMessageFormat_t*) osPoolAlloc(servos_message_pool);
                    if(servos_mail){
                        servos_mail->message_type = SERVOS_GOTO_POSITION;
                        servos_mail->x_position = laser_position_x;
                        servos_mail->y_position = laser_position_y;
                        osMessagePut(servos_mq, (uint32_t)servos_mail, osWaitForever);
                    }
                }
                
                if(joystick_mail->joystick_event->down == JOYSTICK_EVT_PRESSED){
                    controller_decrement_y_position();
                    servos_mail = (servosMessageFormat_t*) osPoolAlloc(servos_message_pool);
                    if(servos_mail){
                        servos_mail->message_type = SERVOS_GOTO_POSITION;
                        servos_mail->x_position = laser_position_x;
                        servos_mail->y_position = laser_position_y;
                        osMessagePut(servos_mq, (uint32_t)servos_mail, osWaitForever);
                    }
                }
                
                if(joystick_mail->joystick_event->right == JOYSTICK_EVT_PRESSED){
                    controller_decrement_x_position();
                    servos_mail = (servosMessageFormat_t*) osPoolAlloc(servos_message_pool);
                    if(servos_mail){
                        servos_mail->message_type = SERVOS_GOTO_POSITION;
                        servos_mail->x_position = laser_position_x;
                        servos_mail->y_position = laser_position_y;
                        osMessagePut(servos_mq, (uint32_t)servos_mail, osWaitForever);
                    }
                }
                
                if(joystick_mail->joystick_event->left == JOYSTICK_EVT_PRESSED){
                    controller_increment_x_position();
                    servos_mail = (servosMessageFormat_t*) osPoolAlloc(servos_message_pool);
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
    servosMessageFormat_t* servosMessage;
    servosMessageFormat_t* secondaryServosMessage;
    laserMessageFormat_t* laserMessage;
    laserMessageFormat_t* secondaryLaserMessage;
    controllerMessageFormat_t* next_message;

    float x_coordinate;
    float y_coordinate;
    uint16_t absolute_pixel_x;
    uint16_t absolute_pixel_y;
    uint8_t pixel_state;
    osEvent evt;
    uint16_t x_shift = TEXT_OFFSET_X;
    uint16_t y_shift = TEXT_OFFSET_Y;
    
    uint16_t next_x, next_y;
    uint16_t next_character_idx;
    uint16_t is_there_more = 1;
    
    if( (y_pixel == 0) && (x_pixel == 0) && (character_index == 0)) {

        absolute_pixel_x = character_index*FONT_WIDTH + x_pixel + x_shift - 3;
        absolute_pixel_y = y_pixel + y_shift - 3;

        /* get the coordinate of the pixel in the x,y plane, needed to
            then move the servos to that position 
        */
        text_generator_get_pixel_coordinate(&x_coordinate, &y_coordinate, absolute_pixel_x, absolute_pixel_y);

        /* send command to servo */
        servosMessage = (servosMessageFormat_t *)osPoolAlloc(servos_message_pool);
        servosMessage->message_type = SERVOS_GOTO_POSITION;
        servosMessage->x_position = x_coordinate;
        servosMessage->y_position = y_coordinate; 
        osMessagePut(servos_mq, (uint32_t)servosMessage, osWaitForever);

        /* wait until command has been executed */
        evt = osMessageGet(servos_mq_in, osWaitForever);

        secondaryServosMessage = (servosMessageFormat_t*) evt.value.p;
        if(secondaryServosMessage->message_type != SERVOS_OK)
        {
            /* something is wrong here! */
            //while(1);
        }
        /* free up the memory */
        osPoolFree(servos_message_pool, servosMessage);
        osPoolFree(servos_message_pool, secondaryServosMessage);
        
        osDelay(VERY_FIRST_PIXEL_PAUSE);
        
         absolute_pixel_x = character_index*FONT_WIDTH + x_pixel + x_shift - 2;
        absolute_pixel_y = y_pixel + y_shift - 2;

        /* get the coordinate of the pixel in the x,y plane, needed to
            then move the servos to that position 
        */
        text_generator_get_pixel_coordinate(&x_coordinate, &y_coordinate, absolute_pixel_x, absolute_pixel_y);

        /* send command to servo */
        servosMessage = (servosMessageFormat_t *)osPoolAlloc(servos_message_pool);
        servosMessage->message_type = SERVOS_GOTO_POSITION;
        servosMessage->x_position = x_coordinate;
        servosMessage->y_position = y_coordinate; 
        osMessagePut(servos_mq, (uint32_t)servosMessage, osWaitForever);

        /* wait until command has been executed */
        evt = osMessageGet(servos_mq_in, osWaitForever);

        secondaryServosMessage = (servosMessageFormat_t*) evt.value.p;
        if(secondaryServosMessage->message_type != SERVOS_OK)
        {
            /* something is wrong here! */
            //while(1);
        }
        /* free up the memory */
        osPoolFree(servos_message_pool, servosMessage);
        osPoolFree(servos_message_pool, secondaryServosMessage);
        
        osDelay(FIRST_PIXEL_PAUSE);
        
        absolute_pixel_x = character_index*FONT_WIDTH + x_pixel + x_shift - 1;
        absolute_pixel_y = y_pixel + y_shift - 1;

        /* get the coordinate of the pixel in the x,y plane, needed to
            then move the servos to that position 
        */
        text_generator_get_pixel_coordinate(&x_coordinate, &y_coordinate, absolute_pixel_x, absolute_pixel_y);

        /* send command to servo */
        servosMessage = (servosMessageFormat_t *)osPoolAlloc(servos_message_pool);
        servosMessage->message_type = SERVOS_GOTO_POSITION;
        servosMessage->x_position = x_coordinate;
        servosMessage->y_position = y_coordinate; 
        osMessagePut(servos_mq, (uint32_t)servosMessage, osWaitForever);

        /* wait until command has been executed */
        evt = osMessageGet(servos_mq_in, osWaitForever);

        secondaryServosMessage = (servosMessageFormat_t*) evt.value.p;
        if(secondaryServosMessage->message_type != SERVOS_OK)
        {
            /* something is wrong here! */
            //while(1);
        }
        /* free up the memory */
        osPoolFree(servos_message_pool, servosMessage);
        osPoolFree(servos_message_pool, secondaryServosMessage);
        
        osDelay(FIRST_PIXEL_PAUSE);
    } else if(y_pixel == 0){
        /*  instead of going directly to the first point of each line, we move
            there gently, hoping that the location will be more precise.
            We simply go two pixels below the starting point
        */
        
        absolute_pixel_x = character_index*FONT_WIDTH + x_pixel + x_shift - 2;
        absolute_pixel_y = y_pixel + y_shift - 2;

        /* get the coordinate of the pixel in the x,y plane, needed to
            then move the servos to that position 
        */
        text_generator_get_pixel_coordinate(&x_coordinate, &y_coordinate, absolute_pixel_x, absolute_pixel_y);

        /* send command to servo */
        servosMessage = (servosMessageFormat_t *)osPoolAlloc(servos_message_pool);
        servosMessage->message_type = SERVOS_GOTO_POSITION;
        servosMessage->x_position = x_coordinate;
        servosMessage->y_position = y_coordinate; 
        osMessagePut(servos_mq, (uint32_t)servosMessage, osWaitForever);

        /* wait until command has been executed */
        evt = osMessageGet(servos_mq_in, osWaitForever);

        secondaryServosMessage = (servosMessageFormat_t*) evt.value.p;
        if(secondaryServosMessage->message_type != SERVOS_OK)
        {
            /* something is wrong here! */
            //while(1);
        }
        /* free up the memory */
        osPoolFree(servos_message_pool, servosMessage);
        osPoolFree(servos_message_pool, secondaryServosMessage);
        
        osDelay(FIRST_PIXEL_PAUSE);

        absolute_pixel_x = character_index*FONT_WIDTH + x_pixel + x_shift - 1;
        absolute_pixel_y = y_pixel + y_shift - 1;

        /* get the coordinate of the pixel in the x,y plane, needed to
            then move the servos to that position 
        */
        text_generator_get_pixel_coordinate(&x_coordinate, &y_coordinate, absolute_pixel_x, absolute_pixel_y);

        /* send command to servo */
        servosMessage = (servosMessageFormat_t *)osPoolAlloc(servos_message_pool);
        servosMessage->message_type = SERVOS_GOTO_POSITION;
        servosMessage->x_position = x_coordinate;
        servosMessage->y_position = y_coordinate; 
        osMessagePut(servos_mq, (uint32_t)servosMessage, osWaitForever);

        /* wait until command has been executed */
        evt = osMessageGet(servos_mq_in, osWaitForever);

        secondaryServosMessage = (servosMessageFormat_t*) evt.value.p;
        if(secondaryServosMessage->message_type != SERVOS_OK)
        {
            /* something is wrong here! */
            //while(1);
        }
        /* free up the memory */
        osPoolFree(servos_message_pool, servosMessage);
        osPoolFree(servos_message_pool, secondaryServosMessage);
        
        osDelay(FIRST_PIXEL_PAUSE);
    }
    
    /* move servos to the desired position */
    absolute_pixel_x = character_index*FONT_WIDTH + x_pixel + x_shift;
    absolute_pixel_y = y_pixel + y_shift;
    
    /* get actual coordinates from the pixel coordinate */
    text_generator_get_pixel_coordinate(&x_coordinate, &y_coordinate, absolute_pixel_x, absolute_pixel_y);

    /* send command to servo */
    servosMessage = (servosMessageFormat_t *)osPoolAlloc(servos_message_pool);
    servosMessage->message_type = SERVOS_GOTO_POSITION;
    servosMessage->x_position = x_coordinate;
    servosMessage->y_position = y_coordinate;

    osMessagePut(servos_mq, (uint32_t)servosMessage, osWaitForever);
    /* wait until command has been executed */
    evt = osMessageGet(servos_mq_in, osWaitForever);

    secondaryServosMessage = (servosMessageFormat_t*) evt.value.p;
    if(secondaryServosMessage->message_type != SERVOS_OK)
    {
        /* something is wrong here! */
        //while(1);
    }
    /* free up the memory */
    osPoolFree(servos_message_pool, servosMessage);
    osPoolFree(servos_message_pool, secondaryServosMessage);

    pixel_state = text_generator_get_pixel(x_pixel, y_pixel, output_text[character_index]);
    /* Do something only if we have to illuminate that point */
    if(1 == pixel_state){
    /*if(1){*/
        /* let the servos stabilize */
        osDelay(SERVOS_STABILIZATION_TIME);

        laserMessage = (laserMessageFormat_t *)osPoolAlloc(laser_message_pool);
        laserMessage->message_type = LASER_SET_STATUS;
        laserMessage->laser_state = 1;
        osMessagePut(laser_mq, (uint32_t)laserMessage, osWaitForever);
   
        evt = osMessageGet(laser_mq_in, osWaitForever);

        secondaryLaserMessage = (laserMessageFormat_t*) evt.value.p;
        if(secondaryLaserMessage->message_type != LASER_OK)
        {
            /* something is wrong here! */
            //while(1);
        }
        /* free up the memory */
        osPoolFree(laser_message_pool, laserMessage);
        osPoolFree(laser_message_pool, secondaryLaserMessage);

        osDelay(LASER_ON_TIME);

        laserMessage = (laserMessageFormat_t *)osPoolAlloc(laser_message_pool);
        laserMessage->message_type = LASER_SET_STATUS;
        laserMessage->laser_state = 0;
        osMessagePut(laser_mq, (uint32_t)laserMessage, osWaitForever);
        evt = osMessageGet(laser_mq_in, osWaitForever);

        secondaryLaserMessage = (laserMessageFormat_t*) evt.value.p;
        if(secondaryLaserMessage->message_type != LASER_OK)
        {
            /* something is wrong here! */
            while(1);
        }
        /* free up the memory */
        osPoolFree(laser_message_pool, laserMessage);
        osPoolFree(laser_message_pool, secondaryLaserMessage);
    }
    
    is_there_more = text_generator_get_next_pixel_coordinates(&next_x, &next_y, &next_character_idx, x_pixel, y_pixel, character_index, output_text);
 
    if(is_there_more) {
        next_message = (controllerMessageFormat_t *)osPoolAlloc(controller_message_pool);
        next_message->message_type = CONTROLLER_DRAW_TEXT_NEXT;
        next_message->x_pixel = next_x;
        next_message->y_pixel = next_y;
        next_message->character_idx = next_character_idx;
        osMessagePut(controller_mq, (uint32_t)next_message, osWaitForever);
    }
}

/** 
* @brief empty a message queue
*/
void controller_empty_message_queue(osMessageQId message_queue_id, osPoolId message_pool_id){
    osEvent evt;

    do {
        evt = osMessageGet(message_queue_id, 0);
        if(evt.status == osEventMessage) {
            if(message_pool_id){
                osPoolFree(controller_message_pool, evt.value.p);
            }
        }
    } while(evt.status == osEventMessage);
}


