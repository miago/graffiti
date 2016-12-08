
#include "text_generator.h"
#include "font5x7.h"
#include <stdint.h>

/**
* @brief Number of pixels in X of the canvas
**/
uint16_t canvas_x_size = TG_CANVAS_X_PIXELS;

/**
* @brief Number of pixels in Y of the canvas
**/
uint16_t canvas_y_size = TG_CANVAS_Y_PIXELS;

/**
* @brief Number of x pixels of the font
*/
uint16_t font_x_size = TG_FONT_X_PIXELS;

/**
* @brief Number of y pixels of the font
*/

uint16_t font_y_size = TG_FONT_Y_PIXELS;


/**
* @brief get the pixel status of a given pixel of a given character
* the pixel can be either 0 (non illuminated) or 1 (illuminated)
**/

uint8_t text_generator_get_pixel(uint8_t x_coor, uint8_t y_coor, char character){
	uint16_t index;
	uint16_t data;
	index = text_generator_get_index(character);
	index = index + x_coor;
	data = Font5x7[index];

	return text_generator_get_y_pixel(data, y_coor);
}

/**
* @brief get the start index of a desired character
**/

uint16_t text_generator_get_index(char character){
	uint16_t index;
	index = (character - TG_FIRST_CHAR)*font_x_size;
	return index;	
}

/**
* @brief get the y pixel of an x data block
**/

uint8_t text_generator_get_y_pixel(uint16_t data, uint8_t y_pixel){
	uint8_t pixel = 0;
	pixel = data >> (font_y_size-1-y_pixel);
	pixel = pixel & 0x01;
	return pixel;
}

/** 
* @brief returns (via pointers) the x,y coordinates (the center) of a desired pixel
**/

void text_generator_get_pixel_coordinate(float* x_ret, float* y_ret, uint16_t x_pixel, uint16_t y_pixel){
	float pixel_size_x, pixel_size_y;

	pixel_size_x = text_generator_calculate_pixel_size_x();
	pixel_size_y = text_generator_calculate_pixel_size_y();

	*x_ret = TG_CANVAS_MIN_X + pixel_size_x/2 + pixel_size_x*x_pixel;
	*y_ret = TG_CANVAS_MIN_Y + pixel_size_y/2 + pixel_size_y*y_pixel;
}

/**
* @brief calculate the width of a pixel
**/
float text_generator_calculate_pixel_size_x(void){
	return ((TG_CANVAS_MAX_X - TG_CANVAS_MIN_X) / (float)canvas_x_size);
}

/**
* @brief calculate the height of a pixel
**/
float text_generator_calculate_pixel_size_y(void){
	return ((TG_CANVAS_MAX_Y - TG_CANVAS_MIN_Y) / (float)canvas_y_size);
}

/**
* @brief This function calculates the next pixel to be displayed. 
* Returns 0 if there is no more pixel to be displayes, 1 otherwise.
**/

uint8_t text_generator_get_next_pixel_coordinates(uint16_t* next_x, uint16_t* next_y, uint16_t* next_char_idx, uint16_t last_x, uint16_t last_y, uint16_t last_char_idx, char* text){
    *next_x = last_x;
    *next_y = last_y + 1;
    *next_char_idx = last_char_idx;

    if(*next_y == font_y_size){
        *next_x = last_x + 1;
        *next_y = 0;
        if(*next_x == font_x_size){
            *next_x = 0;
            *next_char_idx = last_char_idx+1;
            if(text[*next_char_idx] == '\n') {
                return 0;
            }
        }
    }

    return 1;
}
