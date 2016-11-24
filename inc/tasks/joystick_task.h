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
#include "joystick_app.h"


typedef struct
{
    osThreadId tid_Joystick;  
} joystickDataBlock_t;

int Joystick_Thread_Init(joystickDataBlock_t * joystickDataBlock);
void Joystick_Thread(void const *argument);

#endif
