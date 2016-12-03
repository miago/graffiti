#include "display_app.h"
#include "unity.h"
#include <stdint.h>

extern uint8_t display_initialized;

/* sometimes you may want to get at local data in a module.
 * for example: If you plan to pass by reference, this could be useful
 * however, it should often be avoided
*/

void setUp(void)
{
  	/* This is run before EACH TEST */
	/* somehow this flag is not reset */
	display_initialized = 0;
}

void tearDown(void)
{
	display_initialized = 0;
}

void test_display_init(void){
	/*
	displayMessageFormat_t display_message;
	displayMessageFormat_t* display_response;

	display_message.message_type = DISPLAY_INIT;
	display_response = display_process_message(&display_message);

	TEST_ASSERT_EQUAL(DISPLAY_OK, display_response->message_type);
	*/
}