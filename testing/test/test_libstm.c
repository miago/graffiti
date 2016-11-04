#include "unity.h"
#include <stdint.h>
#include "stm32f10x.h"

extern uint16_t GPIOA_value;

/* sometimes you may want to get at local data in a module.
 * for example: If you plan to pass by reference, this could be useful
 * however, it should often be avoided */

void setUp(void){
  /* This is run before EACH TEST */
}

void tearDown(void){
}

void test_GPIO_WriteBit(void){
	/* at the beginning I would like to have the port set to 0 */
	TEST_ASSERT_EQUAL(0x0000, GPIOA_value);
	GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
	
	TEST_ASSERT_EQUAL(0x0001, GPIOA_value);
	GPIO_WriteBit(GPIOA, GPIO_Pin_6, Bit_SET);
	TEST_ASSERT_EQUAL(0x0041, GPIOA_value);
	GPIO_WriteBit(GPIOA, GPIO_Pin_15, Bit_SET);
	TEST_ASSERT_EQUAL(0x8041, GPIOA_value);
	
	/* clear bits */
	GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET);
	TEST_ASSERT_EQUAL(0x8041, GPIOA_value);
	GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
	TEST_ASSERT_EQUAL(0x8040, GPIOA_value);
}

void test_GPIO_ReadOutputDataBit(void) {
	uint8_t bit_value;
	GPIOA_value = 0x0000;
	bit_value = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0);
	TEST_ASSERT_EQUAL(0x00, bit_value);
	bit_value = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_4);
	TEST_ASSERT_EQUAL(0x00, bit_value);
	bit_value = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_15);
	TEST_ASSERT_EQUAL(0x00, bit_value);
	GPIOA_value = 0x0001;
	bit_value = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0);
	TEST_ASSERT_EQUAL(0x01, bit_value);
	bit_value = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_15);
	TEST_ASSERT_EQUAL(0x00, bit_value);
	
	GPIOA_value = 0xFFFF;
	bit_value = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0);
	TEST_ASSERT_EQUAL(0x01, bit_value);
	bit_value = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_15);
	TEST_ASSERT_EQUAL(0x01, bit_value);
	bit_value = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_7);
	TEST_ASSERT_EQUAL(0x01, bit_value);
}

void test_GPIO_ReadOutputData(void) {
	GPIOA_value = 0x0000;
	TEST_ASSERT_EQUAL(0x0000, GPIO_ReadOutputData(GPIOA));
	
	GPIOA_value = 0x1234;
	TEST_ASSERT_EQUAL(0x1234, GPIO_ReadOutputData(GPIOA));
	
	GPIOA_value = 0x6354;
	TEST_ASSERT_EQUAL(0x6354, GPIO_ReadOutputData(GPIOA));
}