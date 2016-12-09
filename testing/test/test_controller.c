
#include "controller_app.h"
#include "laser_app.h"
#include "servos_app.h"
#include "unity.h"
#include <stdint.h>
#include <cmsis_os.h>

extern uint16_t controller_font_width;
extern uint16_t controller_font_height;
extern char* output_text;

osMessageQId laser_mq;	
osMessageQId servos_mq;	
osPoolId laser_message_pool = (osPoolId)3;
osPoolId servos_message_pool = (osPoolId)4;
laserMessageFormat_t laser_message[100]; /* 100 should be fine */
servosMessageFormat_t servos_message[100];
uint8_t laser_pool_counter = 0;
uint8_t servos_pool_counter = 0;
char testText[20] = "Mirco\n";  

/* sometimes you may want to get at local data in a module.
 * for example: If you plan to pass by reference, this could be useful
 * however, it should often be avoided */

/* UNTESTED */
void *osPoolAlloc (osPoolId pool_id){
	if(pool_id == laser_mail_pool){
		return &laser_message[++laser_pool_counter];
	} else if(pool_id == servos_mail_pool){
		return &servos_message[++servos_pool_counter];
	}
	return 0;
}

void setUp(void)
{
  	/* This is run before EACH TEST */
	controller_init();
	controller_font_height = 4;
	controller_font_width = 3;

	output_text = testText;
}

void tearDown(void)
{
	
}

void test_controller_get_next_pixel_coordinates(void){
	uint16_t next_x;	
	uint16_t next_y;
	uint8_t next_character_index;
	uint8_t ret_value;

	ret_value = controller_get_next_pixel_coordinates(&next_x, &next_y, &next_character_index, 0, 0, 0);
	/* the first pixel to be incremented is the one in y*/
	TEST_ASSERT_EQUAL(next_x, 0); 
	TEST_ASSERT_EQUAL(next_y, 1);
	TEST_ASSERT_EQUAL(next_character_index, 0);
	TEST_ASSERT_EQUAL(ret_value, 1); /* There are more pixels to be displayed */

	ret_value = controller_get_next_pixel_coordinates(&next_x, &next_y, &next_character_index, 0, 1, 0);
	TEST_ASSERT_EQUAL(next_x, 0); 
	TEST_ASSERT_EQUAL(next_y, 2);
	TEST_ASSERT_EQUAL(next_character_index, 0);
	TEST_ASSERT_EQUAL(ret_value, 1); /* There are more pixels to be displayed */

	ret_value = controller_get_next_pixel_coordinates(&next_x, &next_y, &next_character_index, 0, 3, 0);
	/* now the x pixel must be incremented and the y pixel reset to 0 */
	TEST_ASSERT_EQUAL(next_x, 1); 
	TEST_ASSERT_EQUAL(next_y, 0);
	TEST_ASSERT_EQUAL(next_character_index, 0);
	TEST_ASSERT_EQUAL(ret_value, 1); /* There are more pixels to be displayed */

	ret_value = controller_get_next_pixel_coordinates(&next_x, &next_y, &next_character_index, 2, 3, 0);
	/* end of a charater, reset pixel coordinates and increment charater index */
	TEST_ASSERT_EQUAL(next_x, 0); 
	TEST_ASSERT_EQUAL(next_y, 0);
	TEST_ASSERT_EQUAL(next_character_index, 1);
	TEST_ASSERT_EQUAL(ret_value, 1); /* There are more pixels to be displayed */

	ret_value = controller_get_next_pixel_coordinates(&next_x, &next_y, &next_character_index, 2, 3, 3);
	/* end of a charater, reset pixel coordinates and increment charater index */
	TEST_ASSERT_EQUAL(next_x, 0); 
	TEST_ASSERT_EQUAL(next_y, 0);
	TEST_ASSERT_EQUAL(next_character_index, 4);
	TEST_ASSERT_EQUAL(ret_value, 1); /* There are more pixels to be displayed */

	ret_value = controller_get_next_pixel_coordinates(&next_x, &next_y, &next_character_index, 2, 3, 4);
	/* end of string, must return 0 */
	/*
	printf("next x is %d\n", next_x);
	printf("next y is %d\n", next_y);
	printf("next ch index is %d\n", next_character_index);
	*/
	TEST_ASSERT_EQUAL(ret_value, 0); /* There are more pixels to be displayed */
}
