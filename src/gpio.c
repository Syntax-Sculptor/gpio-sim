/*
 * SyntaxSculptor
 *
 * SPDX-License-Identifier: MIT
 */

#include "gpio.h"
#include <stdlib.h>

gpio_status_t gpio_init(gpio_port_t* port) {
    if (port == NULL) {
        return GPIO_ERROR_NULL_PORT;
    }

    port->direction = 0x00000000u;
    port->input = 0x00000000u;
    port->output = 0x00000000u;

    return GPIO_OK;
}

gpio_status_t gpio_set_direction(gpio_port_t* port, unsigned int pin_num, gpio_direction_t direction) {
    if (port == NULL) {
        return GPIO_ERROR_NULL_PORT;
    }
    else if (pin_num >= GPIO_NUM_PINS) {
        return GPIO_ERROR_INVALID_PIN;
    }
    else if (direction != GPIO_INPUT && direction != GPIO_OUTPUT) {
        return GPIO_ERROR_INVALID_DIRECTION;
    }

    if (direction == GPIO_OUTPUT) {
        port->direction |= (1u << pin_num);
    }
    else {
        port->direction &= ~(1u << pin_num);
    }

    return GPIO_OK;
}