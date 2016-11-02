#include "unity.h"
#include <stdint.h>
#include "stm32f10x.h"

extern uint16_t GPIOA_value;

/* sometimes you may want to get at local data in a module.
 * for example: If you plan to pass by reference, this could be useful
 * however, it should often be avoided */

void setUp(void)
{
  /* This is run before EACH TEST */
}

void tearDown(void)
{
}

void test_GPIO_WriteBit(void)
{
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