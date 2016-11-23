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
 * @file laser_hal.h
 * @author Mirco E. Gysin
 * @date 04 Nov 2016
 * @brief Header file of laser_hal.c
 */
 
#ifndef LASER_HAL_H
#define LASER_HAL_H

#include "stm32f10x.h"
 
#define LASER_GPIO_PIN GPIO_Pin_6
#define LASER_GPIO_PORT GPIOC


typedef enum
{
	undefined,
	on, 
	off
} laser_status_t;




void laser_init_hal(void);
void laser_set_status_hal(laser_status_t new_state);
laser_status_t laser_get_status_hal(void);

#endif
