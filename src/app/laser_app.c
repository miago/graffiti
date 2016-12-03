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
 * @file laser_app.c
 * @author Mirco E. Gysin
 * @date 31 Oct 2016
 * @brief This file controls the laser beam. 
 */

#include "laser_app.h"
#include "laser_hal.h"
#include "laser_task.h"
#include <stdint.h>

uint8_t initialized = 0;

void laser_init(void)
{
	laser_init_hal();
	laser_set_off();
    initialized = 1;
}

void laser_set_on(void)
{
	laser_status_t ls = on;
	laser_set_status_hal(ls);
}

void laser_set_off(void){
	laser_status_t ls = off;
	laser_set_status_hal(ls);
}

laser_status_t laser_get_status(void){
	return laser_get_status_hal();
}

laserMailFormat_t* laser_process_message(laserMailFormat_t* mail)
{
    laser_status_t laser_status;
    if((mail->message_type != LASER_INIT) && (initialized == 0)){
        mail->message_type = LASER_ERROR;
        return mail;
    }

    switch(mail->message_type){
        case LASER_INIT:
            laser_init();
            mail->message_type = LASER_OK;
            mail->laser_state = 0;
            return mail;

        case LASER_SET_STATUS:
            if(mail->laser_state == 1) {
                laser_set_on();
            } else {
                laser_set_off();
            }

            mail->message_type = LASER_OK;
            return mail;

        case LASER_GET_STATUS:
            mail->message_type = LASER_STATUS;

            laser_status = laser_get_status();
            if(laser_status == on) {
                mail->laser_state = 1;
            } else {
                mail->laser_state = 0;
            }

            return mail;

        case LASER_TOGGLE:
            laser_status = laser_get_status();
            if(laser_status == on) {
                laser_set_off();
            } else {
                laser_set_on();
            }
            mail->message_type = LASER_OK;
            return mail;
        default:
            break;
    }
    mail->message_type = LASER_ERROR;
    return mail;
}
