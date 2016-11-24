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
 * @file joystick_task.h
 * @author Mirco E. Gysin
 * @date 23 Nov 2016
 * @brief This file contains the definitions for joystick_task.c
 */

#ifndef JOYSTICK_TASK_H
#define JOYSTICK_TASK_H

#include <stdint.h>
#include <cmsis_os.h>

typedef enum
{
	/* commands to the joystick module */
	INIT,
	UPDATE_REQ, /* someone is requesting an update of state of 
	the joysticks buttons*/

	/* commands from the joystick module to other modules */

	UPDATED_VALUES /* provided the updated values */
} joystickMessageType_t;

typedef enum
{
	evt_pressed,
	evt_released,
	evt_no_event
} joystickButtonEvent_t;

typedef enum
{
	st_pressed,
	st_released
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

typedef struct
{
	joystickMessageType_t message_type;
    joystickState_t joystick_state;
    joystickEvent_t joystick_event;
} joystickMailFormat_t;

typedef struct
{
    osThreadId tid_Joystick;  
} joystickDataBlock_t;

void Joystick_Thread(void const *argument);

#endif
