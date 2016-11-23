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
 * @file controller_task.h
 * @author Mirco E. Gysin
 * @date 23 Nov 2016
 * @brief This file contains the definitions for controller_task.c
 */

#ifndef CONTROLLER_TASK_H
#define CONTROLLER_TASK_H

typedef struct 
{
    osThreadId tid_Controller;           //!< Handle to the current thread
} ControllerDataBlock_t;                 //!< Controller Data block defined


#endif