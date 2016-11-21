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
 * @file joystick_hal.c
 * @author Mirco E. Gysin
 * @date 07 Nov 2016
 * @brief Manages the Joystick at hardware level
 */
 
#include "joystick_hal.h"
#include "joystick_app.h"
#include "stm32f10x.h"
#include <stdint.h>
 
extern uint8_t joystick_state;
extern uint8_t joystick_rising;
extern uint8_t joystick_falling;

/*
                                    UP          DOWN        LEFT        RIGHT       CENTER
*/

GPIO_TypeDef * joystick_ports[5] = {   GPIOA,      	GPIOB,      	GPIOC,      	GPIOC,      	GPIOB};
uint16_t joystick_pins[5] =        {      4,        0,          	1,          	0,          	5};
uint16_t joystick_ids[5] =         {  JOYSTICK_UP,  JOYSTICK_DOWN,  JOYSTICK_LEFT,  JOYSTICK_RIGHT, JOYSTICK_CENTER};
 
/**
 * Initialize the joystick at hardware level
 */

void joystick_init_hal(void){
	
	uint8_t cnt = 0;
	/*
     UP connected to: A2     -> PA4 
     DOWN connected to: A3   -> PB0
     LEFT connected to: A4   -> PC1
     RIGHT connected to: A5  -> PC0
     CENTER connected to D4  -> PB5
    */
    
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);
        
    /* 
        Set them all to inputs:
    */
    
    /* Set up GPIO for UP button (PA4) */
	
	for(cnt = 0; cnt < 5; cnt++){
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStructure.GPIO_Pin = (1<<joystick_pins[cnt]);
		GPIO_Init(joystick_ports[cnt], & GPIO_InitStructure);	
	}
}

/**
* Update the joystick values at hardware level
*/

void joystick_update_hal(void){
	uint8_t id = 0;
	for(id = 0; id < 5; id++){
        if((joystick_ports[id]->IDR & (1<<joystick_pins[id])) == 0x00){
        /* Falling Edge */
            if(JOYSTICK_LV_IS(joystick_ids[id])){
            /* Button state was previously high */
                JOYSTICK_FE_ST(joystick_ids[id]);
            }
            JOYSTICK_LV_CL(joystick_ids[id]);
        } else { /* Button is high */
            /* Rising Edge, button state was previously low */
            if(!JOYSTICK_LV_IS(joystick_ids[id])){
                JOYSTICK_RE_ST(joystick_ids[id]);
            }
            JOYSTICK_LV_ST(joystick_ids[id]);
        }
    }
}
