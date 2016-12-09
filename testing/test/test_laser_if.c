
#include "laser_task.h"
/*#include "laser_hal.h"*/
#include "unity.h"
#include <stdint.h>

extern uint8_t laser_initialized;

/* sometimes you may want to get at local data in a module.
 * for example: If you plan to pass by reference, this could be useful
 * however, it should often be avoided */

void setUp(void)
{
  /* This is run before EACH TEST */
	/* somehow this flag is not reset */
	laser_initialized = 0;
}

void tearDown(void)
{
	laser_initialized = 0;
}

void test_laser_init(void){
	
	laserMessageFormat_t laser_message;
	laserMessageFormat_t* laser_return_message;

	laser_message.message_type = LASER_INIT;
	laser_return_message = laser_process_message(&laser_message);

	TEST_ASSERT_EQUAL(LASER_OK, laser_return_message->message_type);
}

void test_laser_without_init(void){
	laserMessageFormat_t laser_message;
	laserMessageFormat_t* laser_return_message;

	laser_message.message_type = LASER_SET_STATUS;
	laser_return_message = laser_process_message(&laser_message);

	TEST_ASSERT_EQUAL(LASER_ERROR, laser_return_message->message_type);
}

void test_laser_get_status(void){
	laserMessageFormat_t laser_message;
	laserMessageFormat_t* laser_return_message;

	laser_message.message_type = LASER_INIT;
	laser_process_message(&laser_message);

	laser_message.message_type = LASER_GET_STATUS;
	laser_return_message = laser_process_message(&laser_message);

	TEST_ASSERT_EQUAL(LASER_STATUS, laser_return_message->message_type);
	TEST_ASSERT_EQUAL(0, laser_return_message->laser_state);

	laser_message.message_type = LASER_SET_STATUS;
	laser_message.laser_state = 1;
	laser_return_message = laser_process_message(&laser_message);
	TEST_ASSERT_EQUAL(1, laser_return_message->laser_state);
}

void test_laser_set_status(void){
	laserMessageFormat_t laser_message;
	laserMessageFormat_t* laser_return_message;

	laser_message.message_type = LASER_INIT;
	laser_process_message(&laser_message);

	laser_message.message_type = LASER_SET_STATUS;
	laser_message.laser_state = 0;
	laser_return_message = laser_process_message(&laser_message);
	TEST_ASSERT_EQUAL(LASER_OK, laser_return_message->message_type);

	laser_message.message_type = LASER_GET_STATUS;
	laser_return_message = laser_process_message(&laser_message);
	TEST_ASSERT_EQUAL(0, laser_return_message->laser_state);

	laser_message.message_type = LASER_SET_STATUS;
	laser_message.laser_state = 1;
	laser_process_message(&laser_message);

	laser_message.message_type = LASER_GET_STATUS;
	laser_return_message = laser_process_message(&laser_message);
	TEST_ASSERT_EQUAL(1, laser_return_message->laser_state);
}

void test_laser_toggle(void){
	laserMessageFormat_t laser_message;
	laserMessageFormat_t* laser_return_message;

	laser_message.message_type = LASER_INIT;
	laser_process_message(&laser_message);

	laser_message.message_type = LASER_TOGGLE;
	laser_return_message = laser_process_message(&laser_message);
	TEST_ASSERT_EQUAL(LASER_OK, laser_return_message->message_type);

	laser_message.message_type = LASER_GET_STATUS;
	laser_return_message = laser_process_message(&laser_message);

	TEST_ASSERT_EQUAL(1, laser_return_message->laser_state);

	laser_message.message_type = LASER_TOGGLE;
	laser_process_message(&laser_message);

	laser_message.message_type = LASER_GET_STATUS;
	laser_return_message = laser_process_message(&laser_message);

	TEST_ASSERT_EQUAL(0, laser_return_message->laser_state);
}