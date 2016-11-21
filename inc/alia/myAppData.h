/**
* Thread Data Block definition
* @file     myAppData.h
* @date     08.11.2015
* @version  1.0
* @author   bfh-ti/dnd1
* 
* @warning
* THE PRESENT SOFTWARE CODE IS FOR EDUCATIONAL PURPOSES ONLY, VOID OF ANY
* WARRANTY WHATSOEVER
*
* <h2><center>smile from time to time</center></h2>
*
* @section sHw Hardware used
*
* mcbstm32C
*
* @section sIde Development tool used
*
* uVision MDK-ARM 5.16a or later
*/



#ifndef __myAppCommons
#define __myAppCommons



typedef struct 
{
  uint32_t pinId;         //!< Pin toggled by this thread
	GPIO_TypeDef *  portId;        //!< Port used for this pin
  int32_t delay;          //!< Delay of LED toggling
	int32_t beepTime;       //!< Time during which the beep will be active
	int32_t beepFreq;       //!< Frequency of beep
	uint8_t state;          //!< Current state of the LED
	osThreadId tid_Thread;  //!< Handle to the current thread
} threadData_t;           //!< Thread Data block defined





#endif  // __myAppCommons
