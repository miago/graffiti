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
 * @file laser.c
 * @author Mirco E. Gysin
 * @date 31 Oct 2016
 * @brief This file controls the laser beam. 
 */


#include "laser.h"
#include <stdint.h>
#include "stm32f10x.h"

enum laser_status_t laser_status = undefined;

void laser_init(void){
	laser_set_off();
	/* enable clock of the desired port */
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}

void laser_set_on(void){
	laser_status = on;
}

void laser_set_off(void){
	laser_status = off;
}

