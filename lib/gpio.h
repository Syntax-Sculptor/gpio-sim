/*
 * SyntaxSculptor
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef GPIO_H
#define GPIO_H

#define GPIO_NUM_PINS 32

#include <stdint.h>

typedef struct gpio_port_t {
    uint32_t direction;
    uint32_t output;
    uint32_t input;
} gpio_port_t;

typedef enum gpio_status_t {
    GPIO_OK = 0,
    GPIO_ERROR_NULL_PORT,
    GPIO_ERROR_INVALID_PIN,
    GPIO_ERROR_INVALID_DIRECTION,
    GPIO_ERROR_ILLEGAL_PIN_WRITE,
    GPIO_ERROR_NULL_VALUE,
} gpio_status_t;

typedef enum gpio_direction_t {
    GPIO_INPUT = 0,
    GPIO_OUTPUT,
} gpio_direction_t;

typedef enum gpio_value_t {
    GPIO_LOW = 0,
    GPIO_HIGH,
} gpio_value_t;

/**
 * Initializes a GPIO port.
 */
gpio_status_t gpio_init(gpio_port_t* port);

gpio_status_t gpio_set_direction(gpio_port_t* port, unsigned int pin, gpio_direction_t direction);

gpio_status_t gpio_write_high(gpio_port_t* port, unsigned int pin);

gpio_status_t gpio_write_low(gpio_port_t* port, unsigned int pin);

gpio_status_t gpio_read(gpio_port_t* port, unsigned int pin, gpio_value_t* out);

#endif 