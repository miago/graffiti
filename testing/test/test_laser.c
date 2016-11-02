
#include "laser.h"
#include "unity.h"
#include <stdint.h>


/* sometimes you may want to get at local data in a module.
 * for example: If you plan to pass by reference, this could be useful
 * however, it should often be avoided */
extern enum laser_status_t laser_status; 
extern 

void setUp(void)
{
  /* This is run before EACH TEST */
}

void tearDown(void)
{
}

void test_laser_init(void)
{
  /* Laser must be undefined at the beginning */
  TEST_ASSERT_EQUAL(undefined, laser_status);
  laser_init();
  /* After initialisation it is turned off */
  TEST_ASSERT_EQUAL(off, laser_status);
}