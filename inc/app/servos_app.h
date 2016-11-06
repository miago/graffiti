
#ifndef SERVOS_APP_H
#define SERVOS_APP_H

#include "servos_hal.h"

#define SERVOS_INITIAL_PAN_ANGLE 0
#define SERVOS_INITIAL_TILT_ANGLE 3.141592
#define SERVOS_DISTANCE_TO_WALL 1.3

void servos_init(void);
void servos_set_angles(float tilt_angle, float pan_angle);
void servos_set_position(void);
float servos_get_pan_angle(void);
float servos_get_tilt_angle(void);
void servos_set_pan_angle(float new_pan_angle);
void servos_set_tilt_angle(float new_tilt_angle);
Angles servos_point_to_angles(Point* p) ;

#endif
