#ifndef LASER_TASK_H
#define LASER_TASK_H

#include <stdint.h>
#include <cmsis_os.h>
#include "laser_app.h"
#include "laser_hal.h"

typedef enum
{
	/* Messages which can be sent to the laser */
	INIT, /* Reuqest initialisation of laser */
	GET_STATUS, /* Request status of the laser */
	SET_STATUS, /* Request that laser is set to 
	the provided value */
	SET_TOGGLE, /* Request that the laser status 
	is toggled */


	/* Responses which the laser can give */
	OK, /* This is the default response when the message
	has been executed correctly */
	STATUS /* With this messsage the status of the led
	is provided */
} laserMessageType_t;

typedef struct 
{
    osThreadId tid_Laser;           //!< Handle to the current thread
} laserDataBlock_t;                 //!< Thread Data block defined

typedef struct
{
	laserMessageType_t message_type;
    uint8_t laser_state;
    uint8_t toggle;
} laserMailFormat_t;

/* function prototypes */ 
void Laser_Thread(void const *argument);
int Laser_Thread_Init(laserDataBlock_t * laserDataBlock);

#endif
