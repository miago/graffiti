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
 * @file controller_app.c
 * @author Mirco E. Gysin
 * @date 23 Nov 2016
 * @brief This file contains the logic of the controller
 */

#include "controller_app.h"
#include "joystick_task.h"

controllerState_t controller_state;
drawingMode_t controller_drawing_mode;


void controller_init(void)
{
	controller_state = INIT;
	controller_drawing_mode = FREE_DRAWING;
}


void controller_process_laser() 
{

}

void controller_process_joystick() 
{
	if(controller_drawing_mode == FREE_DRAWING) {
		if
	}
}
