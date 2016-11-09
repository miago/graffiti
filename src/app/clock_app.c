/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
	
#include <stdint.h>
#include "clock_app.h"
#include "clock_hal.h"

extern uint32_t uwTimingDelay;

void delay_ms(volatile uint32_t nTime)
{ 
	uwTimingDelay = nTime;

	while(uwTimingDelay != 0);
}

void clock_init(void){
    clock_init_hal();
}
