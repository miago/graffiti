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

#define MIN_PERIOD 100
#define MAX_PERIOD 1500

extern volatile uint32_t ms_ticks;

extern uint8_t joystick_state;
extern uint8_t joystick_rising;
extern uint8_t joystick_falling;

uint16_t laser_period_x = 750;
uint16_t laser_period_y = 750;
 
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
    
    servos_set_pan_angle_hal(laser_period_x);
    servos_set_tilt_angle(laser_period_y);
    
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
 
    sprintf(text1,     "X period:    %d", laser_period_x);
    sprintf(text2,     "Y period:    %d", laser_period_y);

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
        laser_period_x += 1;
        if(laser_period_x > MAX_PERIOD) {
            laser_period_x = MAX_PERIOD;
        }
        servos_set_pan_angle_hal(laser_period_x);
    }
    
    if(JOYSTICK_LV_IS(JOYSTICK_LEFT)){
        laser_period_x -= 1;
        if(laser_period_x < MIN_PERIOD) {
            laser_period_x = MIN_PERIOD;
        }
        servos_set_pan_angle_hal(laser_period_x);
    }
    
    if(JOYSTICK_LV_IS(JOYSTICK_UP)){
        laser_period_y += 1;
        if(laser_period_y > MAX_PERIOD) {
            laser_period_y = MAX_PERIOD;
        }
        servos_set_tilt_angle_hal(laser_period_y);
    }
    
    if(JOYSTICK_LV_IS(JOYSTICK_DOWN)){
        laser_period_y -= 1;
        if(laser_period_y < MIN_PERIOD) {
            laser_period_y = MIN_PERIOD;
        }
        servos_set_tilt_angle_hal(laser_period_y);
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
