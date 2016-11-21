#include "stm32f10x.h"
#include "clock_hal.h"
#include "main.h"

RCC_ClocksTypeDef RCC_Clocks;


void clock_init_hal(void){
    RCC_GetClocksFreq(&RCC_Clocks);
    SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
}
