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
 * @file laser_app.h
 * @author Mirco E. Gysin
 * @date 21 Nov 2016
 * @brief Header file of laser_app.c
 */

#ifndef LASER_APP_H
#define LASER_APP_H

#define CANVAS_X_MIN -1
#define CANVAS_X_MAX +1
#define CANVAS_Y_MIN -0.5
#define CANVAS_Y_MAX +0.5

void laser_init(void);
void laser_set_on(void);
void laser_set_off(void);
enum laser_status_t laser_get_status(void);

#endif 
