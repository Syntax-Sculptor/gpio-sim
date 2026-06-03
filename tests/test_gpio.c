/*
 * SyntaxSculptor
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "unity.h"
#include "gpio.h"

void tearDown(void) {}

void setUp(void) {}

void test_gpio_init_resets_registers(void) {
    gpio_port_t port = {
        .direction = 0x10000101u,
        .output = 0x10000101u,
        .input = 0x10000101u
    };

    TEST_ASSERT_EQUAL(GPIO_OK, gpio_init(&port));
    TEST_ASSERT_EQUAL_UINT32(0x00000000u, port.direction);
    TEST_ASSERT_EQUAL_UINT32(0x00000000u, port.output);
    TEST_ASSERT_EQUAL_UINT32(0x00000000u, port.input);
}

void test_gpio_init_rejects_null_port(void) {
    TEST_ASSERT_EQUAL(GPIO_ERROR_NULL_PORT, gpio_init(NULL));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_gpio_init_resets_registers);
    RUN_TEST(test_gpio_init_rejects_null_port);

    return UNITY_END();
}