
#include "controller_app.h"
#include "laser_app.h"
#include "servos_app.h"
#include "unity.h"
#include <stdint.h>
#include <cmsis_os.h>


osMessageQId laser_mq;	
osMessageQId servos_mq;	
osPoolId laser_mail_pool = 0;
osPoolId servos_mail_pool = 1;
laserMailFormat_t laser_message_pool[3];
servosMailFormat_t servos_message_pool[3];

/* sometimes you may want to get at local data in a module.
 * for example: If you plan to pass by reference, this could be useful
 * however, it should often be avoided */

void *osPoolAlloc (osPoolId pool_id){
	if(pool_id == laser_mail_pool){
		return &laser_message_pool[0];
	} else if(pool_id == servos_message_pool){
		return &servos_message_pool[0];
	}
	return 0;
}

void setUp(void)
{
  /* This is run before EACH TEST */

}

void tearDown(void)
{
	
}

