#ifndef LASER_H
#define LASER_H

void laser_init(void);
void laser_set_on(void);
void laser_set_off(void);

enum laser_status_t {
	undefined,
	on, 
	off
};

#endif 
