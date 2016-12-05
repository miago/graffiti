#include "unity.h"
#include <stdint.h>
#include "text_generator.h"

extern uint16_t canvas_x_size;
extern uint16_t canvas_y_size;

/* sometimes you may want to get at local data in a module.
 * for example: If you plan to pass by reference, this could be useful
 * however, it should often be avoided
*/

void setUp(void)
{
  	/* This is run before EACH TEST */
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

void test_get_index_space(void){
	uint8_t index;

	index = text_generator_get_index(' ');
	TEST_ASSERT_EQUAL(0, index);
}

void test_get_index_0(void){
	uint8_t index;

	index = text_generator_get_index('0');
	TEST_ASSERT_EQUAL(80, index);
}

void test_get_y_pixel_empty(void){
	uint16_t data = 0x00;
	uint8_t pixel;

	pixel = text_generator_get_y_pixel(data, 0);
	TEST_ASSERT_EQUAL(0, pixel);
}

void test_get_y_pixel_filled(void){
	uint16_t data = 0x05; /* 0b0101*/
	uint8_t pixel;

	pixel = text_generator_get_y_pixel(data, 0);
	TEST_ASSERT_EQUAL(1, pixel);

	pixel = text_generator_get_y_pixel(data, 1);
	TEST_ASSERT_EQUAL(0, pixel);

	pixel = text_generator_get_y_pixel(data, 2);
	TEST_ASSERT_EQUAL(1, pixel);

	pixel = text_generator_get_y_pixel(data, 3);
	TEST_ASSERT_EQUAL(0, pixel);

	pixel = text_generator_get_y_pixel(data, 4);
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
