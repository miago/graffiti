#include "stm32f10x.h"
#include <stdio.h>

uint16_t GPIOA_value = 0x0000;
uint16_t GPIOB_value = 0x0000;

void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState){
}

void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState){
	
}

void GPIO_PinRemapConfig(uint32_t GPIO_Remap, FunctionalState NewState){
	
}

void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct){
}

void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal){
	if(GPIOx == GPIOA) 
	{
		if(BitVal == Bit_SET) {
			GPIOA_value |= GPIO_Pin;
		} else {
			GPIOA_value &= ~GPIO_Pin;
		}
	} else {
		printf("!!!WARNING, YOU ARE USING AN UNIMPLEMENTED FEATURE!!!\n\r");
	}
}

uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	uint16_t port_value = 0;
	uint8_t ret_value = 0;
	
	if(GPIOx == GPIOA){
		port_value = GPIOA_value;
	} 
	else if(GPIOx == GPIOB) {
		port_value = GPIOB_value;
	} else {
		printf("!!!WARNING, YOU ARE USING AN UNIMPLEMENTED FEATURE!!!\n\r");
	}
	
	if((port_value&GPIO_Pin) == 0x0000){
		ret_value = 0x00;
	} else {
		ret_value = 0x01;
	}
	
	return ret_value;
}

uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx) {
	if(GPIOx == GPIOA){
		return GPIOA_value;
	} 
	else if(GPIOx == GPIOB) {
		return GPIOB_value;
	} else {
		printf("!!!WARNING, YOU ARE USING AN UNIMPLEMENTED FEATURE!!!\n\r");
	}
	
	return 0xFFFF;
}

void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState){
	
}

void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct){
	
}

void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct){
	
}
