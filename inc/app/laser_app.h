#ifndef LASER_APP_H
#define LASER_APP_H

void laser_init(void);
void laser_set_on(void);
void laser_set_off(void);
enum laser_status_t laser_get_status(void);

#endif 
