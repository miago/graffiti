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
 * @file servos_task.h
 * @author Mirco E. Gysin
 * @date 23 Nov 2016
 * @brief Header file of servos_task.c
 */

#ifndef SERVOS_TASK_K
#define SERVOS_TASK_K

#include <stdint.h>
#include <cmsis_os.h>
#include "servos_app.h"
#include "servos_hal.h"

typedef struct 
{
    osThreadId tid_Servos;
} servosDataBlock_t;


/* function prototypes */ 
void Servos_Thread(void const *argument);
int Servos_Thread_Init(servosDataBlock_t * servosDataBlock);

#endif
