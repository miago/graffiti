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
 * @file main.c
 * @author Mirco E. Gysin
 * @date 20 Oct 2016
 * @brief This is the main file of the Temporary Graffity project 
 */
  
#include "stm32f10x.h"
#include "clock_app.h"
#include "servos_app.h"
#include "servos_hal.h"
#include "laser_app.h"
#include "display.h"
#include "font5x7.h"

extern volatile uint32_t ms_ticks;

 
 /**  
 * @brief main function
 */
int main(void){
    int a = 0;
	clock_init();
    servos_init();
    laser_init();
    display_init();
 
    
    glcd_command(0xA5); 
    glcd_select_screen((uint8_t *)&glcd_buffer, &glcd_bbox);
	glcd_reset();
	glcd_ST7565R_init();
    glcd_tiny_set_font(Font5x7, 5, 7, GLCD_LCD_HEIGHT, GLCD_LCD_WIDTH);
	glcd_clear_buffer();
	glcd_tiny_draw_string(0, 0, "TEST!");
	glcd_write();

    //servos_set_pan_angle(((float)a)/1000.0);
    servos_set_position(-1, -1);
    delay_ms(300);
    servos_set_position(1, 1);
    
    laser_set_off();
    
    delay_ms(1000);
    
    laser_set_on();
    
    delay_ms(1000);
    
    laser_set_off();
    
    delay_ms(1000);
    
    laser_set_on();

    
    while(1);
    
    
}

