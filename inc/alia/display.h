/**
  ******************************************************************************
  * @file     display.h
	* @autor		rnm1
	* @version	V1.0
	* @date			22.02.2016
  * @brief    library file display.c
  ******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DISPLAY_H
#define __DISPLAY_H

/* Includes ------------------------------------------------------------------*/	
#include "stm32f10x.h"

#include "glcd.h"

#include <stdio.h>
#include <stdlib.h>




/* Private defines------------------------------------------------------------*/
/* Prototypes ------------------------------------------------------------------*/
void display_init(void);
void glcd_spi_write(uint8_t c);
void glcd_reset(void);
void display_write_row(uint8_t row, char* text);
void display_clear_row(uint8_t row);
void Display(uint32_t TimeVar, float TempVar, float axVar, float ayVar, float azVar);


#endif /*__DISPLAY_H */

/********** (C) COPYRIGHT BFH TI Bienne - Mechatronics Lab *****END OF FILE****/
