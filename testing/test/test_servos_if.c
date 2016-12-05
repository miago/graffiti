#include "servos_task.h"
#include "unity.h"
#include <stdint.h>

extern uint8_t servos_initialized;

/* sometimes you may want to get at local data in a module.
 * for example: If you plan to pass by reference, this could be useful
 * however, it should often be avoided
*/

void setUp(void)
{
  	/* This is run before EACH TEST */
	/* somehow this flag is not reset */
	servos_initialized = 0;
}

void tearDown(void)
{
	servos_initialized = 0;
}

void test_servos_init(void){
	servosMailFormat_t servos_message;
	servosMailFormat_t* servos_return_message;

	servos_message.message_type = SERVOS_INIT;
	servos_return_message = servos_process_message(&servos_message);

	TEST_ASSERT_EQUAL(SERVOS_OK, servos_return_message->message_type);
}

void test_servos_without_init(void){
	servosMailFormat_t servos_message;
	servosMailFormat_t* servos_return_message;

	servos_message.message_type = SERVOS_GOTO_POSITION;
	servos_return_message = servos_process_message(&servos_message);

	TEST_ASSERT_EQUAL(SERVOS_ERROR, servos_return_message->message_type);
}

void test_servos_goto_position(void){
	servosMailFormat_t servos_message;
	servosMailFormat_t* servos_return_message;

	servos_message.message_type = SERVOS_INIT;
	servos_process_message(&servos_message);

	servos_message.message_type = SERVOS_GOTO_POSITION;
	servos_return_message = servos_process_message(&servos_message);

	TEST_ASSERT_EQUAL(SERVOS_OK, servos_return_message->message_type);
}
