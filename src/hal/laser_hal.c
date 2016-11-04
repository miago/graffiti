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
 * @file laser_hal.c
 * @author Mirco E. Gysin
 * @date 04 Nov 2016
 * @brief This file controls the laser beam at Hardware Level. 
 */

#include "stm32f10x.h"
#include "laser_hal.h"


void laser_init_hal(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	/* set clock related stuff */
	
	/* TODO check which port it is! */
	if(LASER_GPIO_PORT == GPIOA)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	} else if(LASER_GPIO_PORT == GPIOB){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	} else if(LASER_GPIO_PORT == GPIOC){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	}
	
	/* set gpio as output */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = LASER_GPIO_PIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
}

void laser_set_status_hal(enum laser_status_t new_state){
	if(new_state == on) {
		GPIO_WriteBit(LASER_GPIO_PORT, LASER_GPIO_PIN, Bit_SET);
	} else if(new_state == off){
		GPIO_WriteBit(LASER_GPIO_PORT, LASER_GPIO_PIN, Bit_RESET);
	}
}

enum laser_status_t laser_get_status_hal(void){
	uint8_t laser_status_u8;
	laser_status_u8 = GPIO_ReadOutputDataBit(LASER_GPIO_PORT, LASER_GPIO_PIN);
	if(laser_status_u8 == 0x00) {
		return off;
	} else {
		return on;
	}
}
