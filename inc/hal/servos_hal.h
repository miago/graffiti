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
 * @date 05 Nov 2016
 */
 
#ifndef SERVOS_HAL_H
#define SERVOS_HAL_H

#include "stm32f10x.h"

#define TIMER_PERIOD (10000)

typedef struct {
	float x, y;
} Point;

typedef struct {
	float tilt, pan;
} Angles;

void servos_init_hal(void);
void servos_set_angles_hal(Angles * new_angles);
uint16_t servos_get_timer_period_hal(void);
void servos_set_pan_angle_hal(uint16_t period);
void servos_set_tilt_angle_hal(uint16_t period);

#endif
