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
 * @file servos_hal.c
 * @author Mirco E. Gysin
 * @date 05 Nov 2016
 * @brief This file controls the laser beam at Hardware Level. 
 */

#include "stm32f10x.h"
#include "servos_hal.h"

void servos_init_hal(void){
	TIM_TimeBaseInitTypeDef timer_structure;
    TIM_OCInitTypeDef TIM_OC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    
    timer_structure.TIM_ClockDivision = TIM_CKD_DIV4;
    timer_structure.TIM_CounterMode = TIM_CounterMode_Up;
    timer_structure.TIM_Period = 10000-1; 
    timer_structure.TIM_Prescaler = 143; 
    TIM_TimeBaseInit(TIM3, &timer_structure);
    
    /* Timer Output Compare Mode PWM */
    TIM_OC_InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OC_InitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OC_InitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set;
    TIM_OC_InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC_InitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OC_InitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OC_InitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
    TIM_OC_InitStructure.TIM_Pulse = 750; 
    TIM_OC3Init(TIM3, &TIM_OC_InitStructure);
    
    /* Set gpio + surrounding gpios to output to supply the servo
        PC6 to 3.3V
        PC5 to GND
        PC8 is PWM signal out
    */
    
    /* PC6 to 1*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_SET);

    /* PC5 to 0*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    GPIO_WriteBit(GPIOC, GPIO_Pin_5, Bit_RESET);
    
    
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
    /* PC8 signal out */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    TIM_Cmd(TIM3, ENABLE);
}

uint16_t servos_get_timer_period_hal(void){
	return TIMER_PERIOD;
}
