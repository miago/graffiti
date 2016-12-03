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
 * @file laser_task.h
 * @author Mirco E. Gysin
 * @date 23 Nov 2016
 * @brief Header file of laser_task.c
 */

#ifndef LASER_TASK_H
#define LASER_TASK_H

#include <stdint.h>
#include <cmsis_os.h>
#include "laser_app.h"
#include "laser_hal.h"

typedef struct 
{
    osThreadId tid_Laser;
} laserDataBlock_t;


/* function prototypes */ 


void Laser_Thread(void const *argument);

int Laser_Thread_Init(laserDataBlock_t * laserDataBlock);

#endif
