
#include <cmsis_os.h>		// CMSIS RTOS header file
#include "stm32f10x.h"
#include "myAppData.h"
#include "laser_app.h"

/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/

void ThreadA(void const *argument);	// thread function
osThreadId tid_Thread;		// thread id
osThreadDef(ThreadA, osPriorityNormal, 1, 0);	// thread object

int Init_ThreadA(threadData_t * dataBlock)
{

	tid_Thread = osThreadCreate(osThread(ThreadA), dataBlock);
	dataBlock->tid_Thread = tid_Thread;
	if (!tid_Thread)
		return (-1);

	return (0);
}

void ThreadA(void const *argument)
{

	threadData_t *value = (threadData_t *) argument;

	while (1) {
		;		// Insert thread code here...
		osDelay(value->delay);
		value->state ^= 1;
		if (value->state) {
			GPIO_WriteBit(value->portId, value->pinId, Bit_RESET);
		} else {
			GPIO_WriteBit(value->portId, value->pinId, Bit_SET);
		}
		osThreadYield();	// suspend thread
	}
}


int Init_ThreadLaser(threadData_t * dataBlock){
    laser_init();
}

void ThreadLaser(void const *argument){
    
}

