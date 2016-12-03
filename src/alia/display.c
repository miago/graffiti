/**
  ******************************************************************************
  * @file    display.c 
  * @author  rnm1
  * @version V1.0
  * @date    22.02.2016
  * @brief   Hardware specific display functions
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 BFH TI Bienne - rnm1 </center></h2>
  *
  ******************************************************************************
	* @information
	*
	*
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "display.h"
#include "osObjects.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t display_initialized = 0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/



void display_init(void){

    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
    
    /* Set up GPIO for SPI pins (SCK PA5, MOSI PA7) */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	/* GPIO_Mode_AF_PP means Alternate Function Push Pull */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Set up GPIO for SPI pin (SS PB6) */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOB, & GPIO_InitStructure);	
	/* disable spi slave, 1 means disables */
	GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_SET);
	
	/* Set up GPIO for Display (RST PA6) */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	/* Drive reset pin high: reset display */
	GPIO_WriteBit(GPIOA, GPIO_Pin_6, Bit_SET);
	
	/* Set up GPIO for Display (A0 PA8), selects instruction/data*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
    
    SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	
	SPI_Init(SPI1, &SPI_InitStructure);
	
	//SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE);
	
	SPI_Cmd(SPI1, ENABLE);
    
}

void glcd_spi_write(uint8_t c)
{
	//$TASK glcd
	/* GLCD SELECT */
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);
	
	/*!< Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	
	SPI_I2S_SendData(SPI1, (uint16_t) c);

	/* Wait until byte has been written */
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) != RESET);

	/* GLCD DESELECT */
	GPIO_SetBits(GPIOB, GPIO_Pin_6);
}

void glcd_reset(void)
{
	//$TASK glcd
	
	/* GLCD SELECT */
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);
	
	/* GLCD RESET LOW() */
	GPIO_ResetBits(GPIOA, GPIO_Pin_6);
	
    /* wait 10 ms */
    osDelay(10);
	
	/* GLCD RESET HIGH() */
	GPIO_SetBits(GPIOA, GPIO_Pin_6);
	
	/* GLCD DESELECT */
	
	GPIO_SetBits(GPIOB, GPIO_Pin_6);
}

/**
  * @brief  Displays the current time, the temperatur and the acceleration.
  * @param  TimeVar: RTC counter value.
	* @param	TempVar: Temperatur value.
	* @param	axVar: x accleration value.
	* @param	ayVar: y accleration value.
	* @param	azVar: z accleration value.
  * @retval None
  */
void Display(uint32_t TimeVar, float TempVar, float axVar, float ayVar, float azVar)
{
	//$TASK RTC  
  /* Reset RTC Counter when Time is 23:59:59 */
  /* Compute  hours */
  /* Compute minutes */
  /* Compute seconds */
	
	glcd_clear_buffer();
	
	//$TASK RTC  
  /* write TimeVar to display */
	
	//$TASK LM75B
	/* write TempVar to display*/
	
	//$TASK MMA7660
	/* write accelerations as decimal to display*/

	/* draw bar graphs*/

	glcd_write();
}

/********** (C) COPYRIGHT BFH TI Bienne - Mechatronics Lab *****END OF FILE****/
