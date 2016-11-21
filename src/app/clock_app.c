/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
	
#include <stdint.h>
#include "clock_app.h"
#include "clock_hal.h"

void clock_init(void){
    clock_init_hal();
}
