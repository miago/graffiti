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
 * @file joystick_app.c
 * @author Mirco E. Gysin
 * @date 07 Nov 2016
 * @brief Manages the Joystick
 */

#include "joystick_hal.h"
#include "joystick_app.h"
#include <stdint.h>


uint8_t joystick_state = 0x00;
uint8_t joystick_rising = 0x00;
uint8_t joystick_falling = 0x00;

joystickMailFormat_t joystick_in_message;
joystickEvent_t joystick_event;
joystickState_t joystick_level;

uint8_t joystick_initialized = 0;

/**
 * Initialize the joystick   
 */ 

void joystick_init(void){
	joystick_rising = 0x00;
	joystick_falling = 0x00;
    joystick_initialized = 0x5f;
}

/**
 * Function to update the state of the joytick at the application level
 */
void joystick_update(void){
	joystick_update_hal();
}

joystickMailFormat_t* joystick_process_message(joystickMailFormat_t * joystick_mail)
{
    joystick_in_message = *joystick_mail;
    joystick_mail->message_type = JOYSTICK_NO_REPLY;
    switch(joystick_in_message.message_type) {
        case JOYSTICK_INIT:
            joystick_init();
            break;
        case JOYSTICK_UPDATE_REQ:
            if(joystick_initialized != 0x5f){
                joystick_mail->message_type = JOYSTICK_ERROR;
                return joystick_mail;
            }
            joystick_update_hal();
            
            joystick_mail->message_type = JOYSTICK_UPDATED_VALUES;
            
            /* CENTER BUTTON */
            if(JOYSTICK_RE_IS(JOYSTICK_CENTER))
            {
                joystick_event.center = JOYSTICK_EVT_PRESSED;
                JOYSTICK_RE_CL(JOYSTICK_CENTER);
            } 
            else if(JOYSTICK_FE_IS(JOYSTICK_CENTER))
            {
                joystick_event.center = JOYSTICK_EVT_RELEASED;
                JOYSTICK_FE_CL(JOYSTICK_CENTER);
            } 
            else 
            {
                joystick_event.center = JOYSTICK_EVT_NONE;
            }
            
            if(JOYSTICK_LV_IS(JOYSTICK_CENTER))
            {
                joystick_level.center = JOYSTICK_ST_PRESSED;
            } else 
            {
                joystick_level.center = JOYSTICK_ST_RELEASED;
            } 
            
            
            /* UP BUTTON */
            
            if(JOYSTICK_RE_IS(JOYSTICK_UP))
            {
                joystick_event.up = JOYSTICK_EVT_PRESSED;
                JOYSTICK_RE_CL(JOYSTICK_UP);
            } 
            else if(JOYSTICK_FE_IS(JOYSTICK_CENTER))
            {
                joystick_event.up = JOYSTICK_EVT_RELEASED;
                JOYSTICK_FE_CL(JOYSTICK_UP);
            } 
            else 
            {
                joystick_event.up = JOYSTICK_EVT_NONE;
            }
            
            if(JOYSTICK_LV_IS(JOYSTICK_UP))
            {
                joystick_level.up = JOYSTICK_ST_PRESSED;
            } else 
            {
                joystick_level.up = JOYSTICK_ST_RELEASED;
            } 
            
            /* DOWN BUTTON */
            
            if(JOYSTICK_RE_IS(JOYSTICK_DOWN))
            {
                joystick_event.down = JOYSTICK_EVT_PRESSED;
                JOYSTICK_RE_CL(JOYSTICK_DOWN);
            } 
            else if(JOYSTICK_FE_IS(JOYSTICK_DOWN))
            {
                joystick_event.down = JOYSTICK_EVT_RELEASED;
                JOYSTICK_FE_CL(JOYSTICK_DOWN);
            } 
            else 
            {
                joystick_event.down = JOYSTICK_EVT_NONE;
            }
            
            if(JOYSTICK_LV_IS(JOYSTICK_DOWN))
            {
                joystick_level.down = JOYSTICK_ST_PRESSED;
            } else 
            {
                joystick_level.down = JOYSTICK_ST_RELEASED;
            } 
            
            /* RIGHT BUTTON */
            
            if(JOYSTICK_RE_IS(JOYSTICK_RIGHT))
            {
                joystick_event.right = JOYSTICK_EVT_PRESSED;
                JOYSTICK_RE_CL(JOYSTICK_RIGHT);
            } 
            else if(JOYSTICK_FE_IS(JOYSTICK_RIGHT))
            {
                joystick_event.right = JOYSTICK_EVT_RELEASED;
                JOYSTICK_FE_CL(JOYSTICK_RIGHT);
            } 
            else 
            {
                joystick_event.right = JOYSTICK_EVT_NONE;
            }
            
            if(JOYSTICK_LV_IS(JOYSTICK_RIGHT))
            {
                joystick_level.right = JOYSTICK_ST_PRESSED;
            } else 
            {
                joystick_level.right = JOYSTICK_ST_RELEASED;
            } 
            
            /* LEFT BUTTON */
            
            if(JOYSTICK_RE_IS(JOYSTICK_LEFT))
            {
                joystick_event.left = JOYSTICK_EVT_PRESSED;
                JOYSTICK_RE_CL(JOYSTICK_LEFT);
            } 
            else if(JOYSTICK_FE_IS(JOYSTICK_LEFT))
            {
                joystick_event.left = JOYSTICK_EVT_RELEASED;
                JOYSTICK_FE_CL(JOYSTICK_LEFT);
            } 
            else 
            {
                joystick_event.left = JOYSTICK_EVT_NONE;
            }
            
            if(JOYSTICK_LV_IS(JOYSTICK_LEFT))
            {
                joystick_level.left = JOYSTICK_ST_PRESSED;
            } else 
            {
                joystick_level.left = JOYSTICK_ST_RELEASED;
            } 
           
            
            
            
            joystick_mail->joystick_event = &joystick_event;
            joystick_mail->joystick_state = &joystick_level;
            
            return joystick_mail;
            
            /*break;*/
        default:        
            break;
        
    }
    return joystick_mail;
}
    
