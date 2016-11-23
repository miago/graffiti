#ifndef LASER_TASK_H
#define LASER_TASK_H

#include <stdint.h>
#include <cmsis_os.h>
#include "laser_app.h"
#include "laser_hal.h"

typedef struct 
{
    laser_status_t state;           //!< Current state of the Laser
    osThreadId tid_Laser;           //!< Handle to the current thread
} laserDataBlock_t;                 //!< Thread Data block defined

typedef struct
{
    uint8_t laser_state;
    uint8_t toggle;
} laserMailFormat_t;

/* function prototypes */ 
void Laser_Thread(void const *argument);
int Laser_Thread_Init(laserDataBlock_t * laserDataBlock);

#endif
