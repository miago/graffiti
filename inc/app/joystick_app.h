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

void joystick_init(void);

void joystick_update(void);

#endif
