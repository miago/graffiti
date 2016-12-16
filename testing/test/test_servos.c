
#include "servos_app.h"
#include "servos_hal.h"
#include "unity.h"
#include <math.h>
#include <stdint.h>


/* sometimes you may want to get at local data in a module.
 * for example: If you plan to pass by reference, this could be useful
 * however, it should often be avoided */
 
extern float servos_tilt_angle;
extern float servos_pan_angle;
extern float servos_distance_to_wall;
extern uint8_t servos_initialized;

void setUp(void){
  /* This is run before EACH TEST */
	servos_init();
}

void tearDown(void){
	
}

void test_servos_init(void){
	
	/* 
		TEST_ASSERT_FLOAT_WITHIN(delta, expected, actual) 
	*/

	TEST_ASSERT_EQUAL(1, servos_initialized);
	
	TEST_ASSERT_FLOAT_WITHIN(0.001, SERVOS_INITIAL_PAN_ANGLE, servos_pan_angle);
	TEST_ASSERT_FLOAT_WITHIN(0.001, SERVOS_INITIAL_TILT_ANGLE, servos_tilt_angle);
}

void test_servos_get_servos_pan_angle(void){
	servos_pan_angle = 1.451;
	TEST_ASSERT_FLOAT_WITHIN(0.001, 1.451, servos_get_pan_angle());
	
	servos_pan_angle = 0.12345;
	TEST_ASSERT_FLOAT_WITHIN(0.001, 0.12345, servos_get_pan_angle());
}

void test_servos_set_servos_pan_angle(void){
	servos_set_pan_angle(0.521);
	TEST_ASSERT_FLOAT_WITHIN(0.001, 0.521, servos_pan_angle);
	
	servos_set_pan_angle(1.064);
	TEST_ASSERT_FLOAT_WITHIN(0.001, 1.064, servos_pan_angle);
}

void test_servos_get_servos_tilt_angle(void){
	servos_tilt_angle = 0.8365;
	TEST_ASSERT_FLOAT_WITHIN(0.001, 0.8365, servos_get_tilt_angle());
	
	servos_tilt_angle = 0.015;
	TEST_ASSERT_FLOAT_WITHIN(0.001, 0.015, servos_get_tilt_angle());
}

void test_servos_set_servos_tilt_angle(void){
	servos_set_tilt_angle(0.1122);
	TEST_ASSERT_FLOAT_WITHIN(0.001, 0.1122, servos_tilt_angle);
	
	servos_set_tilt_angle(0.9525);
	TEST_ASSERT_FLOAT_WITHIN(0.001, 0.9525, servos_tilt_angle);
}


/*

	New routine, without distance.	
	the canvas has a width of 2 and a heigth of 1.

	Point 0,0 is in the middle of the canvas
	
	Points -1 respectively +1 in the x axis are at an angle of 45 degrees
	Point -0.5 of the y coordinate is at an angle of 0 degree (or maybe 
	180, depending on where the angle of the servo starts).

*/
void test_servos_point_to_angles(void){
	Point p;
	Angles angles;
	
	p.x = 0;
	p.y = 0;
	
	angles = servos_point_to_angles(&p);
	
	TEST_ASSERT_FLOAT_WITHIN(0.001, 0, angles.pan);

	TEST_ASSERT_FLOAT_WITHIN(0.001, 0.4636, angles.tilt);
	
	p.x = -1;
	p.y = -0.5;
	
	angles = servos_point_to_angles(&p);
	
	TEST_ASSERT_FLOAT_WITHIN(0.001, -3.141592653589/4, angles.pan);
	
	TEST_ASSERT_FLOAT_WITHIN(0.001, 0, angles.tilt);
	
	p.x = 1;
	p.y = 0.5;
	
	angles = servos_point_to_angles(&p);
	
	TEST_ASSERT_FLOAT_WITHIN(0.001, 3.141592653589/4, angles.pan);
	
	TEST_ASSERT_FLOAT_WITHIN(0.001, 3.141592653589/4, angles.tilt);
	
}

void test_servos_pan_angle_to_timervalue(void) {
	
	uint16_t tv = servos_pan_angle_to_timervalue(0);

	TEST_ASSERT_EQUAL(750, tv);
	
	tv = servos_pan_angle_to_timervalue(-3.141592653589793/2);

	TEST_ASSERT_UINT16_WITHIN(1, 1208, tv);
	
	tv = servos_pan_angle_to_timervalue(+3.141592653589793/2);

	TEST_ASSERT_UINT16_WITHIN(1, 292, tv);
}

void test_servos_tilt_angle_to_timervalue(void) {
	uint16_t tv = servos_tilt_angle_to_timervalue(0);
	
	/* by definition/measurement */
	TEST_ASSERT_EQUAL(375, tv);

	tv = servos_tilt_angle_to_timervalue(3.14159265/2);

	TEST_ASSERT_EQUAL(815, tv);
}

void test_servos_get_point_of_spiral_last(void){
	Point p;
	p = servos_get_point_of_spiral(0, 0, 2, 1, 5);
	TEST_ASSERT_FLOAT_WITHIN(0.001, -1, p.x);
	TEST_ASSERT_FLOAT_WITHIN(0.001, 1, p.y);
}

void test_servos_get_point_of_spiral_first(void){
	Point p;
	/* Point servos_get_point_of_spiral(float x, float y, float pixel_size, uint16_t windings, uint16_t point_number); */
	p = servos_get_point_of_spiral(    0,       0,       5, 			   1,                 0            );
	TEST_ASSERT_FLOAT_WITHIN(0.001, 0, p.x);
	TEST_ASSERT_FLOAT_WITHIN(0.001, 0, p.y);

	p = servos_get_point_of_spiral(    -1.23,       -4.2,       5, 			   1,                 0            );
	TEST_ASSERT_FLOAT_WITHIN(0.001, -1.23, p.x);
	TEST_ASSERT_FLOAT_WITHIN(0.001, -4.2, p.y);
}


void test_servos_get_point_of_spiral_second(void) { 
	Point p;
	/* Point servos_get_point_of_spiral(float x, float y, float pixel_size, uint16_t windings, uint16_t point_number); */
	p = servos_get_point_of_spiral(1, 1, 12, 2, 1);
	TEST_ASSERT_FLOAT_WITHIN(0.001, 1, p.x);
	TEST_ASSERT_FLOAT_WITHIN(0.001, 4, p.y);
}

void test_servos_get_point_of_spiral_third(void) {
	Point p;
	/* Point servos_get_point_of_spiral(float x, float y, float pixel_size, uint16_t windings, uint16_t point_number); */
	p = servos_get_point_of_spiral(1, 1, 12, 2, 2);
	TEST_ASSERT_FLOAT_WITHIN(0.001, 4, p.x);
	TEST_ASSERT_FLOAT_WITHIN(0.001, 4, p.y);
}

void test_servos_get_point_of_spiral_fourth(void) {
	Point p;
	/* Point servos_get_point_of_spiral(float x, float y, float pixel_size, uint16_t windings, uint16_t point_number); */
	p = servos_get_point_of_spiral(1, 1, 12, 2, 3);
	TEST_ASSERT_FLOAT_WITHIN(0.001, 4, p.x);
	TEST_ASSERT_FLOAT_WITHIN(0.001, -2, p.y);
}

void test_servos_get_point_of_spiral_fifth(void) {
	Point p;
	/* Point servos_get_point_of_spiral(float x, float y, float pixel_size, uint16_t windings, uint16_t point_number); */
	p = servos_get_point_of_spiral(1, 1, 12, 2, 4);
	TEST_ASSERT_FLOAT_WITHIN(0.001, -2, p.x);
	TEST_ASSERT_FLOAT_WITHIN(0.001, -2, p.y);
}

void test_servos_get_point_of_spiral_sixth(void) {
	Point p;
	/* Point servos_get_point_of_spiral(float x, float y, float pixel_size, uint16_t windings, uint16_t point_number); */
	p = servos_get_point_of_spiral(1, 1, 12, 2, 5);
	TEST_ASSERT_FLOAT_WITHIN(0.001, -2, p.x);
	TEST_ASSERT_FLOAT_WITHIN(0.001, 7, p.y);
}

void test_servos_get_point_of_spiral_seventh(void) {
	Point p;
	/* Point servos_get_point_of_spiral(float x, float y, float pixel_size, uint16_t windings, uint16_t point_number); */
	p = servos_get_point_of_spiral(1, 1, 12, 2, 6);
	TEST_ASSERT_FLOAT_WITHIN(0.001, 7, p.x);
	TEST_ASSERT_FLOAT_WITHIN(0.001, 7, p.y);
}

void test_servos_get_point_of_spiral_eighth(void){
	Point p;
	/* Point servos_get_point_of_spiral(float x, float y, float pixel_size, uint16_t windings, uint16_t point_number); */
	p = servos_get_point_of_spiral(1, 1, 12, 2, 7);
	TEST_ASSERT_FLOAT_WITHIN(0.001, 7, p.x);
	TEST_ASSERT_FLOAT_WITHIN(0.001, -5, p.y);
}

void test_servos_get_point_of_spiral_ninth(void){
	Point p;
	/* Point servos_get_point_of_spiral(float x, float y, float pixel_size, uint16_t windings, uint16_t point_number); */
	p = servos_get_point_of_spiral(1, 1, 12, 2, 8);
	TEST_ASSERT_FLOAT_WITHIN(0.001, -5, p.x);
	TEST_ASSERT_FLOAT_WITHIN(0.001, -5, p.y);
}

void test_servos_get_number_of_points_in_spiral(void){
	uint16_t nr_of_points;


	nr_of_points = servos_get_number_of_points_in_spiral(1);

	TEST_ASSERT_EQUAL(6, nr_of_points);

}

void test_get_interspiral_space(void) {
	float iss;

	iss = servos_get_interspiral_space(10.0, 1);

	TEST_ASSERT_FLOAT_WITHIN(0.001, 5, iss);

	iss = servos_get_interspiral_space(4, 2);

	TEST_ASSERT_FLOAT_WITHIN(0.001, 1, iss);

	iss = servos_get_interspiral_space(6, 3);

	TEST_ASSERT_FLOAT_WITHIN(0.001, 1, iss);

	iss = servos_get_interspiral_space(10, 3);

	TEST_ASSERT_FLOAT_WITHIN(0.001, 1.666666, iss);
}