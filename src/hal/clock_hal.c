#include "stm32f10x.h"
#include "clock_hal.h"

volatile uint32_t ms_ticks;
volatile uint32_t uwTimingDelay;
RCC_ClocksTypeDef RCC_Clocks;

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
    if (uwTimingDelay != 0x00)
    { 
        uwTimingDelay--;
	}
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
    ms_ticks++;	
    TimingDelay_Decrement();
}


void clock_init_hal(void){
    RCC_GetClocksFreq(&RCC_Clocks);
    SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
}
