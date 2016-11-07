
#ifndef JOYSTICK_APP_H
#define JOYSTICK_APP_H 

#include <stdint.h>

#define JOYSTICK_UP          0
#define JOYSTICK_DOWN        1
#define JOYSTICK_LEFT        2
#define JOYSTICK_RIGHT       3
#define JOYSTICK_CENTER      4

void joystick_init(void);

void joystick_update(void);

#endif
