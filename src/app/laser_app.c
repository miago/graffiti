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
 * @file laser_app.c
 * @author Mirco E. Gysin
 * @date 31 Oct 2016
 * @brief This file controls the laser beam. 
 */


#include "laser_app.h"
#include "laser_hal.h"
#include <stdint.h>


void laser_init(void){
	laser_init_hal();
	laser_set_off();
}

void laser_set_on(void){
	enum laser_status_t ls = on;
	laser_set_status_hal(ls);
}

void laser_set_off(void){
	enum laser_status_t ls = off;
	laser_set_status_hal(ls);
}

enum laser_status_t laser_get_status(void){
	return laser_get_status_hal();
}
