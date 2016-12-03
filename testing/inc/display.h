
#ifndef DISPLAY_H
#define DISPLAY_H
#include <stdint.h>

void display_init(void);
void glcd_spi_write(uint8_t c);
void glcd_reset(void);
void Display(uint32_t TimeVar, float TempVar, float axVar, float ayVar, float azVar);


#endif
