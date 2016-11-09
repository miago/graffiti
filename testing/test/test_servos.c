
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
extern uint16_t servos_timer_period;

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

void test_servos_point_to_angles(void){
	Point p;
	Angles angles;
	servos_distance_to_wall = 1;
	
	/* 
		trivial case at point 0,0
	*/
	p.x = 0;
	p.y = 0;
	angles = servos_point_to_angles(&p);
	TEST_ASSERT_FLOAT_WITHIN(0.001, 0, angles.tilt);
	TEST_ASSERT_FLOAT_WITHIN(0.001, 0, angles.pan);
	
	/* 
		case at angle 45 degrees upwards (pi/4)
	*/
	p.x = 0;
	p.y = 1;
	angles = servos_point_to_angles(&p);
	TEST_ASSERT_FLOAT_WITHIN(0.001, 0, angles.pan);
	TEST_ASSERT_FLOAT_WITHIN(0.001, 0.78539816339, angles.tilt);
	
	/*
		case at angle 45 degree downwards 
	*/
	p.x = 0;
	p.y = -1;
	angles = servos_point_to_angles(&p);
	TEST_ASSERT_FLOAT_WITHIN(0.001, 0, angles.pan);
	TEST_ASSERT_FLOAT_WITHIN(0.001, -0.78539816339, angles.tilt);
	
	/*
		case at -0.5, -0.5 
	*/
	
	p.x = -0.5;
	p.y = -0.5;
	angles = servos_point_to_angles(&p);
	TEST_ASSERT_FLOAT_WITHIN(0.001, -0.463648, angles.pan);
	TEST_ASSERT_FLOAT_WITHIN(0.001, -0.463648, angles.tilt);
}

void test_servos_angle_to_timervalue(void) {
	servos_timer_period = 10000;
	
	uint16_t tv = servos_angle_to_timervalue(0);
	/* at 10000, 1ms corresponds to 750 ticks 
		10000 = 20ms, 10000ticks/20 = 20ms/20, 
		500ticks = 1ms
	*/
	TEST_ASSERT_EQUAL(500, tv);

	tv = servos_angle_to_timervalue(3.141592653589793);

	/* at 10000, 2ms correspond to 10000/20*2=1000ticks*/

	TEST_ASSERT_EQUAL(1000, tv);

	tv = servos_angle_to_timervalue(3.141592653589793/2);

	TEST_ASSERT_EQUAL(750, tv);


	


	
}