#ifndef TEXT_GENERATOR_H
#define TEXT_GENERATOR_H

#include <stdint.h>

#define TG_FIRST_CHAR 0x20
#define TG_X_PIXELS 5
#define TG_Y_PIXELS 7
#define TG_PIXELS_X 100
#define TG_PIXELS_Y 50
#define TG_CANVAS_MIN_Y -0.5
#define TG_CANVAS_MAX_Y +0.5
#define TG_CANVAS_MIN_X -1.0
#define TG_CANVAS_MAX_X +1.0

uint8_t text_generator_get_pixel(uint8_t x_coor, uint8_t y_coor, char character);
uint8_t text_generator_get_index(char character);
uint8_t text_generator_get_y_pixel(uint16_t data, uint8_t y_pixel);
void text_generator_get_pixel_coordinate(float* x_ret, float* y_ret, uint16_t x_pixel, uint16_t y_pixel);
float text_generator_calculate_pixel_size_x(void);
float text_generator_calculate_pixel_size_y(void);

#endif