/*
 * SyntaxSculptor
 *
 * SPDX-License-Identifier: MIT
 */

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

void test_gpio_set_direction_rejects_null_port(void) {
    TEST_ASSERT_EQUAL(GPIO_ERROR_NULL_PORT, gpio_set_direction(NULL, 0, GPIO_INPUT));
}

void test_gpio_set_direction_rejects_invalid_pin(void) {
    gpio_port_t port = {
        .direction = 0x1u,
        .output = 0x0u,
        .input = 0x0u,
    };
    
    TEST_ASSERT_EQUAL(GPIO_ERROR_INVALID_PIN, gpio_set_direction(&port, GPIO_NUM_PINS, GPIO_INPUT));
    TEST_ASSERT_EQUAL_UINT32(0x00000001u, port.direction);
    TEST_ASSERT_EQUAL_UINT32(0x00000000u, port.output);
    TEST_ASSERT_EQUAL_UINT32(0x00000000u, port.input);
}

void test_gpio_set_direction_rejects_invalid_direction(void) {
    gpio_port_t port = {
        .direction = 0x1u,
        .output = 0x0u,
        .input = 0x0u,
    };
    
    TEST_ASSERT_EQUAL(GPIO_ERROR_INVALID_DIRECTION, gpio_set_direction(&port, 0, 5));
    TEST_ASSERT_EQUAL_UINT32(0x00000001u, port.direction);
    TEST_ASSERT_EQUAL_UINT32(0x00000000u, port.output);
    TEST_ASSERT_EQUAL_UINT32(0x00000000u, port.input);
}

void test_gpio_set_direction_output_pin_0(void) {
    gpio_port_t port = {
        .direction = 0x0u,
        .output = 0x0u,
        .input = 0x0u,
    };
    TEST_ASSERT_EQUAL(GPIO_OK, gpio_set_direction(&port, 0, GPIO_OUTPUT));
    TEST_ASSERT_EQUAL_UINT32(0x00000001u, port.direction);
    TEST_ASSERT_EQUAL_UINT32(0x00000000u, port.output);
    TEST_ASSERT_EQUAL_UINT32(0x00000000u, port.input);   
}

void test_gpio_set_direction_output_pin_1(void) {
    gpio_port_t port = {
        .direction = 0x0u,
        .output = 0x0u,
        .input = 0x0u,
    };
    TEST_ASSERT_EQUAL(GPIO_OK, gpio_set_direction(&port, 1, GPIO_OUTPUT));
    TEST_ASSERT_EQUAL_UINT32(0x00000002u, port.direction);
    TEST_ASSERT_EQUAL_UINT32(0x00000000u, port.output);
    TEST_ASSERT_EQUAL_UINT32(0x00000000u, port.input);
}

void test_gpio_set_direction_output_pin_31(void) {
    gpio_port_t port = {
        .direction = 0x0u,
        .output = 0x0u,
        .input = 0x0u,
    };
    TEST_ASSERT_EQUAL(GPIO_OK, gpio_set_direction(&port, 31, GPIO_OUTPUT));
    TEST_ASSERT_EQUAL_UINT32(0x80000000u, port.direction);
    TEST_ASSERT_EQUAL_UINT32(0x00000000u, port.output);
    TEST_ASSERT_EQUAL_UINT32(0x00000000u, port.input);
}

void test_gpio_set_direction_preserves_bits(void) {
    gpio_port_t port = {
        .direction = 0x1u, // Pin 0 set initially
        .output = 0x0u,
        .input = 0x0u,
    };
    TEST_ASSERT_EQUAL(GPIO_OK, gpio_set_direction(&port, 1, GPIO_OUTPUT));
    TEST_ASSERT_EQUAL_UINT32(0x00000003u, port.direction);

    TEST_ASSERT_EQUAL(GPIO_OK, gpio_set_direction(&port, 2, GPIO_OUTPUT));
    TEST_ASSERT_EQUAL_UINT32(0x00000007u, port.direction);
    
    TEST_ASSERT_EQUAL_UINT32(0x00000000u, port.output);
    TEST_ASSERT_EQUAL_UINT32(0x00000000u, port.input);
}

void test_gpio_set_direction_input_clears_bits(void) {
    gpio_port_t port = {
        .direction = 0x3u, // Pins 0 and 1 set initially
        .output = 0x0u,
        .input = 0x0u,
    };
    TEST_ASSERT_EQUAL(GPIO_OK, gpio_set_direction(&port, 1, GPIO_INPUT));
    TEST_ASSERT_EQUAL_UINT32(0x00000001u, port.direction);

    TEST_ASSERT_EQUAL(GPIO_OK, gpio_set_direction(&port, 0, GPIO_INPUT));
    TEST_ASSERT_EQUAL_UINT32(0x00000000u, port.direction);
    
    TEST_ASSERT_EQUAL_UINT32(0x00000000u, port.output);
    TEST_ASSERT_EQUAL_UINT32(0x00000000u, port.input);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_gpio_init_resets_registers);
    RUN_TEST(test_gpio_init_rejects_null_port);
    RUN_TEST(test_gpio_set_direction_rejects_null_port);
    RUN_TEST(test_gpio_set_direction_rejects_invalid_pin);
    RUN_TEST(test_gpio_set_direction_rejects_invalid_direction);
    RUN_TEST(test_gpio_set_direction_output_pin_0);
    RUN_TEST(test_gpio_set_direction_output_pin_1);
    RUN_TEST(test_gpio_set_direction_output_pin_31);
    RUN_TEST(test_gpio_set_direction_input_clears_bits);
    RUN_TEST(test_gpio_set_direction_preserves_bits);


    return UNITY_END();
}