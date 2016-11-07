 
#ifndef JOYSTICK_HAL_H
#define JOYSTICK_HAL_H

#include <stdint.h>
 
void joystick_init_hal(void);
void joystick_update_hal(void);

/* 
    * Level (LV) macros: 
    * IS: boolean true if button has high state
    * CL: clear level bit
    * ST: set level bit
*/
#define JOYSTICK_LV_IS(x) ((joystick_state & (1<<x)) == (1<<x)) 
#define JOYSTICK_LV_CL(x) (joystick_state &= ~(1<<x))
#define JOYSTICK_LV_ST(x) (joystick_state |= (1<<x))

/* 
    * Rising edge (RE) macros: 
    * IS: boolean true if button has pending rising edge bit
    * CL: clear rising edge bit
    * ST: set rising edge bit
*/
#define JOYSTICK_RE_IS(x) ((joystick_rising & (1<<x)) == (1<<x)) 
#define JOYSTICK_RE_CL(x) (joystick_rising &= ~(1<<x))
#define JOYSTICK_RE_ST(x) (joystick_rising |= (1<<x))

/* 
    * Falling edge (FE) macro: 
    * IS: boolean true if button has pending falling edge bit
    * CL: clear falling edge bit
    * ST: set falling edge bit
*/
#define JOYSTICK_FE_IS(x) ((joystick_falling & (1<<x)) == (1<<x)) 
#define JOYSTICK_FE_CL(x) (joystick_falling &= ~(1<<x))
#define JOYSTICK_FE_ST(x) (joystick_falling |= (1<<x))
	 
#endif
