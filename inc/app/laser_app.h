#ifndef LASER_APP_H
#define LASER_APP_H

#define CANVAS_X_MIN -1
#define CANVAS_X_MAX +1
#define CANVAS_Y_MIN -0.5
#define CANVAS_Y_MAX +0.5

void laser_init(void);
void laser_set_on(void);
void laser_set_off(void);
enum laser_status_t laser_get_status(void);

#endif 
