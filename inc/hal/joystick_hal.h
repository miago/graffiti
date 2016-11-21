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
 * @file joystick_hal.h
 * @author Mirco E. Gysin
 * @date 21 Nov 2016
 * @brief Header file of joystick_hal.c
 */

 
#ifndef JOYSTICK_HAL_H
#define JOYSTICK_HAL_H

#include <stdint.h>
 
void joystick_init_hal(void);
void joystick_update_hal(void);

/* 
    * Level (LV) macros: 
    * IS: boolean true if button has high state
    * CL: clear level bit
    * ST: set level bit
*/
#define JOYSTICK_LV_IS(x) ((joystick_state & (1<<x)) == (1<<x)) 
#define JOYSTICK_LV_CL(x) (joystick_state &= ~(1<<x))
#define JOYSTICK_LV_ST(x) (joystick_state |= (1<<x))

/* 
    * Rising edge (RE) macros: 
    * IS: boolean true if button has pending rising edge bit
    * CL: clear rising edge bit
    * ST: set rising edge bit
*/
#define JOYSTICK_RE_IS(x) ((joystick_rising & (1<<x)) == (1<<x)) 
#define JOYSTICK_RE_CL(x) (joystick_rising &= ~(1<<x))
#define JOYSTICK_RE_ST(x) (joystick_rising |= (1<<x))

/* 
    * Falling edge (FE) macro: 
    * IS: boolean true if button has pending falling edge bit
    * CL: clear falling edge bit
    * ST: set falling edge bit
*/
#define JOYSTICK_FE_IS(x) ((joystick_falling & (1<<x)) == (1<<x)) 
#define JOYSTICK_FE_CL(x) (joystick_falling &= ~(1<<x))
#define JOYSTICK_FE_ST(x) (joystick_falling |= (1<<x))
	 
#endif
