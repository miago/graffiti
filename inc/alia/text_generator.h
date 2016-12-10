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
 * @file text_generator.h
 * @author Mirco E. Gysin
 * @date 05 Dec 2016
 * @brief Header file of text_generator.c
 */

#ifndef TEXT_GENERATOR_H
#define TEXT_GENERATOR_H

#include <stdint.h>

#define TG_FIRST_CHAR 0x20

/*
TODO: take this values from somewhere
*/
#define TG_CANVAS_MIN_Y -0.5
#define TG_CANVAS_MAX_Y +0.5
#define TG_CANVAS_MAX_X +1.0
#define TG_CANVAS_MIN_X -1.0

uint8_t text_generator_get_pixel(uint8_t x_coor, uint8_t y_coor, char character);
uint16_t text_generator_get_index(char character);
uint8_t text_generator_get_y_pixel(uint16_t data, uint8_t y_pixel);
void text_generator_get_pixel_coordinate(float* x_ret, float* y_ret, uint16_t x_pixel, uint16_t y_pixel);
float text_generator_calculate_pixel_size_x(void);
float text_generator_calculate_pixel_size_y(void);
uint8_t text_generator_get_next_pixel_coordinates(uint16_t* next_x, uint16_t* next_y, uint16_t* next_char_idx, uint16_t last_x, uint16_t last_y, uint16_t last_char_idx, char* text);

#endif
