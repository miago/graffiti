
#include "laser_app.h"
#include "laser_hal.h"
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
	enum laser_status_t laser_status;
	laser_init();
	
	/* After initialisation it is turned off */
	laser_status = laser_get_status(); 
	TEST_ASSERT_EQUAL(off, laser_status);
}

void test_laser_set_on(void){
	enum laser_status_t laser_status;
	laser_init();
	
	laser_set_on();
	laser_status = laser_get_status(); 
	TEST_ASSERT_EQUAL(on, laser_status);
}
