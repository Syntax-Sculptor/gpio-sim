/*
 * SyntaxSculptor
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

typedef struct gpio_port_t {
    // Skipping out on volatile just because this is being simulated.
    uint32_t direction;
    uint32_t output;
    uint32_t input;
} gpio_port_t;

typedef enum gpio_status_t {
    GPIO_OK = 0,
    GPIO_ERROR_NULL_PORT,
} gpio_status_t;

/**
 * Initializes a GPIO port.
 */
gpio_status_t gpio_init(gpio_port_t* port);

#endif 