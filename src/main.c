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
#include "laser_hal.h"
#include "display.h"
#include "font5x7.h"
#include "joystick_app.h"
#include "joystick_hal.h"
#include "main.h"

#define ROW1 0
#define ROW2 8
#define ROW3 16
#define ROW4 24

extern volatile uint32_t ms_ticks;

extern uint8_t joystick_state;
extern uint8_t joystick_rising;
extern uint8_t joystick_falling;

float laser_position_x = 0;
float laser_position_y = 0;
 
 /**  
 * @brief main function
 */
int main(void){
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
    /*    
        if(JOYSTICK_LV_IS(BTN_UP)){
            if(timer_frequency != 5000){
                timer_frequency += 100;
            }
            
            updateTimer(timer_frequency, timer_duty_cycle);
        }
        
        if(JOYSTICK_LV_IS(BTN_DOWN)){
            if(timer_frequency != 200){
                timer_frequency -= 100;
            }
            updateTimer(timer_frequency, timer_duty_cycle);
        }
        
        if(JOYSTICK_LV_IS(BTN_RIGHT)){
            if(timer_duty_cycle != 100){
                timer_duty_cycle += 1;
            }
            updateTimer(timer_frequency, timer_duty_cycle);
        }
        	
        if(JOYSTICK_LV_IS(BTN_LEFT)){
            if(timer_duty_cycle != 0){
                timer_duty_cycle -= 1;
            }
            updateTimer(timer_frequency, timer_duty_cycle);
        }
        
        */
}

void update_display(void){
    
    char text0[25];
    char text1[25];
    char text2[25];
    
    
    if(laser_get_status() == on){
        sprintf(text0, "Laser State: ON");
    } else {
        sprintf(text0, "Laser State: OFF");
    }
 
    sprintf(text1,     "X pos:       %2.2f", laser_position_x);
    sprintf(text2,     "Y pos:       %2.2f", laser_position_y);

    glcd_clear();
    glcd_draw_string_xy(10, ROW1, text0);
    glcd_draw_string_xy(10, ROW2, text1);
    glcd_draw_string_xy(10, ROW3, text2);
    
    glcd_write();
}

void scheduler(void){
    if(JOYSTICK_RE_IS(JOYSTICK_CENTER)){
        if(laser_get_status() == on){
            laser_set_off();
        } else {
            laser_set_on();
        }
        JOYSTICK_RE_CL(JOYSTICK_CENTER);      
    }
    
    if(JOYSTICK_LV_IS(JOYSTICK_RIGHT)){
        laser_position_x += 0.05;
        if(laser_position_x > CANVAS_X_MAX) {
            laser_position_x = CANVAS_X_MAX;
        }
        servos_set_position(laser_position_x, laser_position_y);
    }
    
    if(JOYSTICK_LV_IS(JOYSTICK_LEFT)){
        laser_position_x -= 0.05;
        if(laser_position_x < CANVAS_X_MIN) {
            laser_position_x = CANVAS_X_MIN;
        }
        servos_set_position(laser_position_x, laser_position_y);
    }
    
    if(JOYSTICK_LV_IS(JOYSTICK_UP)){
        laser_position_y += 0.05;
        if(laser_position_y > CANVAS_Y_MAX) {
            laser_position_y = CANVAS_Y_MAX;
        }
        servos_set_position(laser_position_x, laser_position_y);
    }
    
    if(JOYSTICK_LV_IS(JOYSTICK_DOWN)){
        laser_position_y -= 0.05;
        if(laser_position_y < CANVAS_Y_MIN) {
            laser_position_y = CANVAS_Y_MIN;
        }
        servos_set_position(laser_position_x, laser_position_y);
    }
}

void millisecond_interval_timer(void){
    if((ms_ticks % 100) == 0){
        joystick_update();
    }
    
    if((ms_ticks % 100) == 0){
        scheduler();
    }
    
    if((ms_ticks % 80) == 0){
        update_display();
    }
}
