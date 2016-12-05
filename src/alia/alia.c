#include "stm32f10x.h"
#include "alia.h"

void RCC_Configuration(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Joystick center button input for button reading */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//$TASK LED on Nucleo
	/* 
	   red D5 PB4
	   green D9 PC7
	   blue D8 PA9
	 */
	// Blue LED on PA9, Arduino D8
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// Green LED on PC7, Arduino D9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	// Red LED on PB4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// Blue LED pin PB4 JTAG  JNTRST pin must be Alternate Remap to be a GPIO
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST, ENABLE);

	// Active low elements, so switch them on!
	GPIO_SetBits(GPIOA, GPIO_Pin_9);
	GPIO_SetBits(GPIOC, GPIO_Pin_7);
	GPIO_SetBits(GPIOB, GPIO_Pin_4);
}

/**
* Initialisation code 
*/
void initialisation(void)
{

	SystemCoreClockUpdate();

	RCC_Configuration();
	GPIO_Configuration();
}
