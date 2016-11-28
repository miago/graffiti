
#include "laser_task.h"
/*#include "laser_hal.h"*/
#include "unity.h"
#include <stdint.h>


/* sometimes you may want to get at local data in a module.
 * for example: If you plan to pass by reference, this could be useful
 * however, it should often be avoided */

void setUp(void)
{
  /* This is run before EACH TEST */
}

void tearDown(void)
{
	
}

void test_laser_init(void){
	
	laserMailFormat_t laser_message;
	laserMailFormat_t laser_return_message;

	laser_message.message_type = LASER_INIT;
	laser_return_message = laser_process_message(laser_message);

	TEST_ASSERT_EQUAL(LASER_OK, laser_return_message.message_type);
}