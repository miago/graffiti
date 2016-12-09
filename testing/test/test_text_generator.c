#include "unity.h"
#include <stdint.h>
#include "text_generator.h"

extern uint16_t canvas_x_size;
extern uint16_t canvas_y_size;
extern uint16_t font_x_size;
extern uint16_t font_y_size;


/* sometimes you may want to get at local data in a module.
 * for example: If you plan to pass by reference, this could be useful
 * however, it should often be avoided
*/

void setUp(void)
{
  	/* This is run before EACH TEST */
  	font_y_size = 7;
  	font_x_size = 5;
}

void tearDown(void)
{

}

void test_get_pixel_space(void){
	uint8_t pixel;

	pixel = text_generator_get_pixel(0, 0, ' ');
	TEST_ASSERT_EQUAL(0, pixel);

	pixel = text_generator_get_pixel(3, 3, ' ');
	TEST_ASSERT_EQUAL(0, pixel);
}

void test_get_pixel_one(void){
	uint8_t pixel;

	pixel = text_generator_get_pixel(2, 0, '1');
	TEST_ASSERT_EQUAL(1, pixel);

	pixel = text_generator_get_pixel(4, 6, '1');
	TEST_ASSERT_EQUAL(0, pixel);

	pixel = text_generator_get_pixel(2, 1, '1');
	TEST_ASSERT_EQUAL(1, pixel);

	pixel = text_generator_get_pixel(2, 5, '1');
	TEST_ASSERT_EQUAL(1, pixel);	
}

/* get the values of the pixels for the character '6' */
void test_get_pixel_six(void){
	uint8_t pixel;

	/*first column */
	pixel = text_generator_get_pixel(0, 0, '6');
	TEST_ASSERT_EQUAL(0, pixel);
	pixel = text_generator_get_pixel(0, 1, '6');
	TEST_ASSERT_EQUAL(1, pixel);
	pixel = text_generator_get_pixel(0, 2, '6');
	TEST_ASSERT_EQUAL(1, pixel);
	pixel = text_generator_get_pixel(0, 3, '6');
	TEST_ASSERT_EQUAL(1, pixel);
	pixel = text_generator_get_pixel(0, 4, '6');
	TEST_ASSERT_EQUAL(1, pixel);
	pixel = text_generator_get_pixel(0, 5, '6');
	TEST_ASSERT_EQUAL(0, pixel);
	pixel = text_generator_get_pixel(0, 6, '6');
	TEST_ASSERT_EQUAL(0, pixel);

	/*second column */
	pixel = text_generator_get_pixel(1, 0, '6');
	TEST_ASSERT_EQUAL(1, pixel);
	pixel = text_generator_get_pixel(1, 1, '6');
	TEST_ASSERT_EQUAL(0, pixel);
	pixel = text_generator_get_pixel(1, 2, '6');
	TEST_ASSERT_EQUAL(0, pixel);
	pixel = text_generator_get_pixel(1, 3, '6');
	TEST_ASSERT_EQUAL(1, pixel);
	pixel = text_generator_get_pixel(1, 4, '6');
	TEST_ASSERT_EQUAL(0, pixel);
	pixel = text_generator_get_pixel(1, 5, '6');
	TEST_ASSERT_EQUAL(1, pixel);
	pixel = text_generator_get_pixel(1, 6, '6');
	TEST_ASSERT_EQUAL(0, pixel);
}

void test_get_index_space(void){
	uint16_t index;

	index = text_generator_get_index(' ');
	TEST_ASSERT_EQUAL(0, index);
}

void test_get_index_0(void){
	uint16_t index;

	index = text_generator_get_index('0');
	TEST_ASSERT_EQUAL(80, index);
}

void test_get_y_pixel_empty(void){
	uint16_t data = 0x00;
	uint8_t pixel;

	pixel = text_generator_get_y_pixel(data, 0);
	TEST_ASSERT_EQUAL(0, pixel);
}

void test_get_y_pixel_six(void){
	uint16_t data = 0x3C; /* first column of '6' */
	uint8_t pixel;

	pixel = text_generator_get_y_pixel(data, 0);
	TEST_ASSERT_EQUAL(0, pixel);
	pixel = text_generator_get_y_pixel(data, 1);
	TEST_ASSERT_EQUAL(1, pixel);
	pixel = text_generator_get_y_pixel(data, 2);
	TEST_ASSERT_EQUAL(1, pixel);
	pixel = text_generator_get_y_pixel(data, 3);
	TEST_ASSERT_EQUAL(1, pixel);
	pixel = text_generator_get_y_pixel(data, 4);
	TEST_ASSERT_EQUAL(1, pixel);
	pixel = text_generator_get_y_pixel(data, 5);
	TEST_ASSERT_EQUAL(0, pixel);
	pixel = text_generator_get_y_pixel(data, 6);
	TEST_ASSERT_EQUAL(0, pixel);

}

void test_get_y_pixel_one(void){
	uint16_t data = 0x08; /* 0b1000*/
	uint8_t pixel;

	pixel = text_generator_get_y_pixel(data, 0);
	TEST_ASSERT_EQUAL(0, pixel);

	pixel = text_generator_get_y_pixel(data, 1);
	TEST_ASSERT_EQUAL(0, pixel);

	pixel = text_generator_get_y_pixel(data, 2);
	TEST_ASSERT_EQUAL(0, pixel);

	pixel = text_generator_get_y_pixel(data, 3);
	TEST_ASSERT_EQUAL(1, pixel);

	pixel = text_generator_get_y_pixel(data, 4);
	TEST_ASSERT_EQUAL(0, pixel);
}

void test_get_pixel_coordinate(void){
	canvas_x_size = 2;
	canvas_y_size = 1;
	float x,y;

	text_generator_get_pixel_coordinate(&x, &y, 0, 0);
	TEST_ASSERT_FLOAT_WITHIN(000.1, -0.5, x);
	TEST_ASSERT_FLOAT_WITHIN(000.1, 0, y);

	text_generator_get_pixel_coordinate(&x, &y, 1, 0);
	TEST_ASSERT_FLOAT_WITHIN(0.001, +0.5, x);
	TEST_ASSERT_FLOAT_WITHIN(0.001, 0, y);
}

void test_get_pixel_coordinate_2(void){
	canvas_x_size = 8;
	canvas_y_size = 4;
	float x,y;

	text_generator_get_pixel_coordinate(&x, &y, 4, 2);

	TEST_ASSERT_FLOAT_WITHIN(000.1, 0.125, x);
	TEST_ASSERT_FLOAT_WITHIN(000.1, 0.125, y);

	text_generator_get_pixel_coordinate(&x, &y, 7, 0);

	TEST_ASSERT_FLOAT_WITHIN(0.001, 1-0.125, x);
	TEST_ASSERT_FLOAT_WITHIN(0.001, -0.5+0.125, y);	


}

void test_calculate_pixel_size(void){
	float pixel_size_x;
	float pixel_size_y;

	canvas_x_size = 2; /* two pixels in x */
	canvas_y_size = 1; /* one pixel in y*/

	pixel_size_x = text_generator_calculate_pixel_size_x();
	pixel_size_y = text_generator_calculate_pixel_size_y();

	TEST_ASSERT_FLOAT_WITHIN(0.001, 1, pixel_size_x);
	TEST_ASSERT_FLOAT_WITHIN(0.001, 1, pixel_size_y);

	canvas_x_size = 20; /* two pixels in x */
	canvas_y_size = 10; /* one pixel in y*/

	pixel_size_x = text_generator_calculate_pixel_size_x();
	pixel_size_y = text_generator_calculate_pixel_size_y();

	TEST_ASSERT_FLOAT_WITHIN(0.001, 0.1, pixel_size_x);
	TEST_ASSERT_FLOAT_WITHIN(0.001, 0.1, pixel_size_y);

	canvas_x_size = 34; /* two pixels in x */
	canvas_y_size = 17; /* one pixel in y*/

	pixel_size_x = text_generator_calculate_pixel_size_x();
	pixel_size_y = text_generator_calculate_pixel_size_y();
	
	TEST_ASSERT_FLOAT_WITHIN(0.001, 0.05882, pixel_size_x);
	TEST_ASSERT_FLOAT_WITHIN(0.001, 0.05882, pixel_size_y);
}

void test_text_generator_get_next_pixel_coordinates(void){
	uint16_t next_x;	
	uint16_t next_y;
	uint16_t next_character_index;
	uint8_t ret_value;

	char text[10] = "Mirco\n";

  	font_x_size = 3;
	font_y_size = 4;

	ret_value = text_generator_get_next_pixel_coordinates(&next_x, &next_y, &next_character_index, 0, 0, 0, text);
	/* the first pixel to be incremented is the one in y*/
	TEST_ASSERT_EQUAL(next_x, 0); 
	TEST_ASSERT_EQUAL(next_y, 1);
	TEST_ASSERT_EQUAL(next_character_index, 0);
	TEST_ASSERT_EQUAL(ret_value, 1); /* There are more pixels to be displayed */

	ret_value = text_generator_get_next_pixel_coordinates(&next_x, &next_y, &next_character_index, 0, 1, 0, text);
	TEST_ASSERT_EQUAL(next_x, 0); 
	TEST_ASSERT_EQUAL(next_y, 2);
	TEST_ASSERT_EQUAL(next_character_index, 0);
	TEST_ASSERT_EQUAL(ret_value, 1); /* There are more pixels to be displayed */

	ret_value = text_generator_get_next_pixel_coordinates(&next_x, &next_y, &next_character_index, 0, 3, 0, text);
	/* now the x pixel must be incremented and the y pixel reset to 0 */
	TEST_ASSERT_EQUAL(next_x, 1); 
	TEST_ASSERT_EQUAL(next_y, 0);
	TEST_ASSERT_EQUAL(next_character_index, 0);
	TEST_ASSERT_EQUAL(ret_value, 1); /* There are more pixels to be displayed */

	ret_value = text_generator_get_next_pixel_coordinates(&next_x, &next_y, &next_character_index, 2, 3, 0, text);
	/* end of a charater, reset pixel coordinates and increment charater index */
	TEST_ASSERT_EQUAL(next_x, 0); 
	TEST_ASSERT_EQUAL(next_y, 0);
	TEST_ASSERT_EQUAL(next_character_index, 1);
	TEST_ASSERT_EQUAL(ret_value, 1); /* There are more pixels to be displayed */

	ret_value = text_generator_get_next_pixel_coordinates(&next_x, &next_y, &next_character_index, 2, 3, 3, text);
	/* end of a charater, reset pixel coordinates and increment charater index */
	TEST_ASSERT_EQUAL(next_x, 0); 
	TEST_ASSERT_EQUAL(next_y, 0);
	TEST_ASSERT_EQUAL(next_character_index, 4);
	TEST_ASSERT_EQUAL(ret_value, 1); /* There are more pixels to be displayed */

	ret_value = text_generator_get_next_pixel_coordinates(&next_x, &next_y, &next_character_index, 2, 3, 4, text);
	/* end of string, must return 0 */
	/*
	printf("next x is %d\n", next_x);
	printf("next y is %d\n", next_y);
	printf("next ch index is %d\n", next_character_index);
	*/
	TEST_ASSERT_EQUAL(ret_value, 0); /* There are more pixels to be displayed */

}

void test_text_generator_get_next_pixel_coordinates_2(void){
	uint16_t next_x;	
	uint16_t next_y;
	uint16_t next_character_index;
	uint8_t ret_value;

	char text[10] = "Mirco\n";

  	font_x_size = 5;
	font_y_size = 7;

	ret_value = text_generator_get_next_pixel_coordinates(&next_x, &next_y, &next_character_index, 4, 6, 0, text);
	/* the first pixel to be incremented is the one in y*/
	TEST_ASSERT_EQUAL(next_x, 0); 
	TEST_ASSERT_EQUAL(next_y, 0);
	TEST_ASSERT_EQUAL(next_character_index, 1);
	TEST_ASSERT_EQUAL(ret_value, 1); /* There are more pixels to be displayed */

}
