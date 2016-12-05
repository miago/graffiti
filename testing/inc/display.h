
#ifndef DISPLAY_H
#define DISPLAY_H
#include <stdint.h>

#define ROW1 0
#define ROW2 8
#define ROW3 16

void display_init(void);
void glcd_spi_write(uint8_t c);
void glcd_reset(void);
void display_write_row(uint8_t row, char* text);
void display_clear_row(uint8_t row);
void Display(uint32_t TimeVar, float TempVar, float axVar, float ayVar, float azVar);

#endif
