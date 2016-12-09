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
 * @file joystick_app.h
 * @author Mirco E. Gysin
 * @date 07 Nov 2016
 * @brief Header file of joystick_app.c
 */


#ifndef JOYSTICK_APP_H
#define JOYSTICK_APP_H 

#include <stdint.h>


#define JOYSTICK_UP          0
#define JOYSTICK_DOWN        1
#define JOYSTICK_LEFT        2
#define JOYSTICK_RIGHT       3
#define JOYSTICK_CENTER      4

typedef enum
{
	JOYSTICK_EVT_PRESSED,
	JOYSTICK_EVT_RELEASED,
	JOYSTICK_EVT_NONE
} joystickButtonEvent_t;

typedef enum
{
	JOYSTICK_ST_PRESSED,
	JOYSTICK_ST_RELEASED
} joystickButtonState_t;

typedef struct
{
	joystickButtonEvent_t center;
	joystickButtonEvent_t left;
	joystickButtonEvent_t right;
	joystickButtonEvent_t up;
	joystickButtonEvent_t down;
} joystickEvent_t;

typedef struct
{
	joystickButtonState_t center;
	joystickButtonState_t left;
	joystickButtonState_t right;
	joystickButtonState_t up;
	joystickButtonState_t down;
} joystickState_t;

typedef enum
{
	/* commands to the joystick module */
	JOYSTICK_INIT,
	JOYSTICK_UPDATE_REQ, /* someone is requesting an update of state of 
	the joysticks buttons*/

	/* commands from the joystick module to other modules */
    JOYSTICK_NO_REPLY,
    JOYSTICK_ERROR, /* when joystick has not been initialized */
	JOYSTICK_UPDATED_VALUES /* provides the updated values */
} joystickMessageType_t;

typedef struct
{
	joystickMessageType_t message_type;
    joystickState_t * joystick_state;
    joystickEvent_t * joystick_event;
} joystickMessageFormat_t;

void joystick_init(void);

void joystick_update(void);

joystickMessageFormat_t* joystick_process_message(joystickMessageFormat_t * joystick_mail);

#endif
