
#include "joystick_app.h"
#include "joystick_hal.h"
#include "unity.h"
#include <stdint.h>


extern uint8_t joystick_state;
extern uint8_t joystick_rising;
extern uint8_t joystick_falling;

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

void test_joystick_init(void){
	joystick_init();
	
	/* After initialisation rising edge and falling edge registers must be zero */ 
	TEST_ASSERT_EQUAL(0x00, joystick_rising);
	TEST_ASSERT_EQUAL(0x00, joystick_falling);
}

void test_joystick_macros_level(void){
	joystick_init();
	
	JOYSTICK_LV_ST(JOYSTICK_CENTER);
	TEST_ASSERT_EQUAL(1, (joystick_state&(1<<JOYSTICK_CENTER))>>JOYSTICK_CENTER);
	
	JOYSTICK_LV_ST(JOYSTICK_RIGHT);
	TEST_ASSERT_EQUAL(1, (joystick_state&(1<<JOYSTICK_RIGHT))>>JOYSTICK_RIGHT);
	
	TEST_ASSERT_EQUAL(1, JOYSTICK_LV_IS(JOYSTICK_RIGHT));
	TEST_ASSERT_EQUAL(0, JOYSTICK_LV_IS(JOYSTICK_LEFT));
}

void test_joystick_macros_rising(void){
	joystick_init();
	
	TEST_ASSERT_EQUAL(0, JOYSTICK_RE_IS(JOYSTICK_UP));
	TEST_ASSERT_EQUAL(0, JOYSTICK_RE_IS(JOYSTICK_DOWN));
	TEST_ASSERT_EQUAL(0, JOYSTICK_RE_IS(JOYSTICK_LEFT));
	TEST_ASSERT_EQUAL(0, JOYSTICK_RE_IS(JOYSTICK_RIGHT));
	TEST_ASSERT_EQUAL(0, JOYSTICK_RE_IS(JOYSTICK_CENTER));
	JOYSTICK_RE_ST(JOYSTICK_UP);
	TEST_ASSERT_EQUAL(1, JOYSTICK_RE_IS(JOYSTICK_UP));
	TEST_ASSERT_EQUAL(0, JOYSTICK_RE_IS(JOYSTICK_DOWN));
	TEST_ASSERT_EQUAL(0, JOYSTICK_RE_IS(JOYSTICK_LEFT));
	TEST_ASSERT_EQUAL(0, JOYSTICK_RE_IS(JOYSTICK_RIGHT));
	TEST_ASSERT_EQUAL(0, JOYSTICK_RE_IS(JOYSTICK_CENTER));
	JOYSTICK_RE_ST(JOYSTICK_LEFT);
	TEST_ASSERT_EQUAL(1, JOYSTICK_RE_IS(JOYSTICK_UP));
	TEST_ASSERT_EQUAL(0, JOYSTICK_RE_IS(JOYSTICK_DOWN));
	TEST_ASSERT_EQUAL(1, JOYSTICK_RE_IS(JOYSTICK_LEFT));
	TEST_ASSERT_EQUAL(0, JOYSTICK_RE_IS(JOYSTICK_RIGHT));
	TEST_ASSERT_EQUAL(0, JOYSTICK_RE_IS(JOYSTICK_CENTER));
	JOYSTICK_RE_CL(JOYSTICK_LEFT);
	JOYSTICK_RE_CL(JOYSTICK_CENTER);
	TEST_ASSERT_EQUAL(1, JOYSTICK_RE_IS(JOYSTICK_UP));
	TEST_ASSERT_EQUAL(0, JOYSTICK_RE_IS(JOYSTICK_DOWN));
	TEST_ASSERT_EQUAL(0, JOYSTICK_RE_IS(JOYSTICK_LEFT));
	TEST_ASSERT_EQUAL(0, JOYSTICK_RE_IS(JOYSTICK_RIGHT));
	TEST_ASSERT_EQUAL(0, JOYSTICK_RE_IS(JOYSTICK_CENTER));

}

void test_joystick_macros_falling(void){
	joystick_init();
	
	TEST_ASSERT_EQUAL(0, JOYSTICK_FE_IS(JOYSTICK_UP));
	TEST_ASSERT_EQUAL(0, JOYSTICK_FE_IS(JOYSTICK_DOWN));
	TEST_ASSERT_EQUAL(0, JOYSTICK_FE_IS(JOYSTICK_LEFT));
	TEST_ASSERT_EQUAL(0, JOYSTICK_FE_IS(JOYSTICK_RIGHT));
	TEST_ASSERT_EQUAL(0, JOYSTICK_FE_IS(JOYSTICK_CENTER));
	
	JOYSTICK_FE_ST(JOYSTICK_DOWN);
	TEST_ASSERT_EQUAL(1, JOYSTICK_FE_IS(JOYSTICK_DOWN));
	TEST_ASSERT_EQUAL(0, JOYSTICK_FE_IS(JOYSTICK_LEFT));
	
	JOYSTICK_FE_CL(JOYSTICK_DOWN);
	TEST_ASSERT_EQUAL(0, JOYSTICK_FE_IS(JOYSTICK_DOWN));
	
}