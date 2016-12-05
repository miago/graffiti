#include "cmsis_os.h"


osMessageQId osMessageCreate (const osMessageQDef_t *queue_def, osThreadId thread_id){

}

osThreadId osThreadCreate (const osThreadDef_t *thread_def, void *argument){

}

osPoolId osPoolCreate (const osPoolDef_t *pool_def){

}

osEvent osMessageGet (osMessageQId queue_id, uint32_t millisec){

}

osStatus osPoolFree (osPoolId pool_id, void *block){

}

osStatus osThreadYield (void){

}

osStatus osDelay (uint32_t millisec){

}

osStatus osMessagePut (osMessageQId queue_id, uint32_t info, uint32_t millisec){
	
}