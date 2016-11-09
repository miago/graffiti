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
 * @file joystick_app.c
 * @author Mirco E. Gysin
 * @date 07 Nov 2016
 * @brief Manages the Joystick
 */

#include "joystick_hal.h"
#include "joystick_app.h"
#include <stdint.h>


uint8_t joystick_state = 0x00;
uint8_t joystick_rising = 0x00;
uint8_t joystick_falling = 0x00;

void joystick_init(void){
	joystick_rising = 0x00;
	joystick_falling = 0x00;
}

void joystick_update(void){
	joystick_update_hal();
}
