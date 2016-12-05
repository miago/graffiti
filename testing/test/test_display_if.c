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

	displayMessageFormat_t display_message;
	displayMessageFormat_t* display_response;

	display_message.message_type = DISPLAY_INIT;
	display_response = display_process_message(&display_message);

	TEST_ASSERT_EQUAL(DISPLAY_OK, display_response->message_type);
}

void test_display_without_init(void){
	displayMessageFormat_t display_message;
	displayMessageFormat_t* display_response;

	display_message.message_type = DISPLAY_WRITE;
	display_response = display_process_message(&display_message);	

	TEST_ASSERT_EQUAL(DISPLAY_ERROR, display_response->message_type);
}

void test_display_glcd_reset(void){
	displayMessageFormat_t display_message;
	displayMessageFormat_t* display_response;

	display_message.message_type = DISPLAY_INIT;
	display_process_message(&display_message);

	display_message.message_type = DISPLAY_RESET;
	display_response = display_process_message(&display_message);
	TEST_ASSERT_EQUAL(DISPLAY_OK, display_response->message_type);		
}

void test_display_write(void){
	displayMessageFormat_t display_message;
	displayMessageFormat_t* display_response;

	display_message.message_type = DISPLAY_INIT;
	display_process_message(&display_message);

	display_message.message_type = DISPLAY_WRITE;
	display_response = display_process_message(&display_message);
	TEST_ASSERT_EQUAL(DISPLAY_OK, display_response->message_type);
}

void test_display_clear_row(void){
	displayMessageFormat_t display_message;
	displayMessageFormat_t* display_response;

	display_message.message_type = DISPLAY_INIT;
	display_process_message(&display_message);

	display_message.message_type = DISPLAY_CLEAR_ROW;
	display_response = display_process_message(&display_message);
	TEST_ASSERT_EQUAL(DISPLAY_OK, display_response->message_type);
}