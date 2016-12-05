
#include "text_generator.h"
#include "font5x7.h"
#include <stdint.h>

uint16_t canvas_x_size = TG_PIXELS_X;
uint16_t canvas_y_size = TG_PIXELS_Y;

uint8_t text_generator_get_pixel(uint8_t x_coor, uint8_t y_coor, char character){
	uint8_t index;
	uint16_t data;
	index = text_generator_get_index(character);
	index = index + x_coor;
	data = Font5x7[index];

	return text_generator_get_y_pixel(data, y_coor);
}

uint8_t text_generator_get_index(char character){
	uint8_t index;
	index = (character - TG_FIRST_CHAR)*TG_X_PIXELS;
	return index;	
}

uint8_t text_generator_get_y_pixel(uint16_t data, uint8_t y_pixel){
	uint8_t pixel = 0;
	pixel = data & (1<<y_pixel);

	if(pixel == 0x00) {
		return 0;	
	} else {
		return 1;
	}	
}

/* 
* returns the x,y coordinate of a desired pixel
*/

void text_generator_get_pixel_coordinate(float* x_ret, float* y_ret, uint16_t x_pixel, uint16_t y_pixel){
	float pixel_size_x, pixel_size_y;

	pixel_size_x = text_generator_calculate_pixel_size_x();
	pixel_size_y = text_generator_calculate_pixel_size_y();

	*x_ret = TG_CANVAS_MIN_X + pixel_size_x/2 + pixel_size_x*x_pixel;
	*y_ret = TG_CANVAS_MIN_Y + pixel_size_y/2 + pixel_size_y*y_pixel;
}

float text_generator_calculate_pixel_size_x(void){
	return ((TG_CANVAS_MAX_X - TG_CANVAS_MIN_X) / (float)canvas_x_size);
}

float text_generator_calculate_pixel_size_y(void){
	return ((TG_CANVAS_MAX_Y - TG_CANVAS_MIN_Y) / (float)canvas_y_size);
}
