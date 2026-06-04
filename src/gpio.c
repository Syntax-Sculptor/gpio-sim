/*
 * SyntaxSculptor
 *
 * SPDX-License-Identifier: MIT
 */

#include "gpio.h"
#include <stdlib.h>

static int is_valid_pin(unsigned int pin) {
    return pin < GPIO_NUM_PINS;
}

static int is_input_pin(uint32_t pins, unsigned int pin) {
    return (pins & (1u << pin)) == 0u;
}

gpio_status_t gpio_init(gpio_port_t* port) {
    if (port == NULL) {
        return GPIO_ERROR_NULL_PORT;
    }

    port->direction = 0x00000000u;
    port->input = 0x00000000u;
    port->output = 0x00000000u;

    return GPIO_OK;
}

gpio_status_t gpio_set_direction(gpio_port_t* port, unsigned int pin, gpio_direction_t direction) {
    if (port == NULL) {
        return GPIO_ERROR_NULL_PORT;
    }
    else if (!is_valid_pin(pin)) {
        return GPIO_ERROR_INVALID_PIN;
    }
    else if (direction != GPIO_INPUT && direction != GPIO_OUTPUT) {
        return GPIO_ERROR_INVALID_DIRECTION;
    }

    if (direction == GPIO_OUTPUT) {
        port->direction |= (1u << pin);
    }
    else {
        port->direction &= ~(1u << pin);
    }

    return GPIO_OK;
}

gpio_status_t gpio_write_high(gpio_port_t* port, unsigned int pin) {
    if (port == NULL) {
        return GPIO_ERROR_NULL_PORT;
    }
    else if (!is_valid_pin(pin)) {
        return GPIO_ERROR_INVALID_PIN;
    }
    else if (is_input_pin(port->direction, pin)) {
        return GPIO_ERROR_ILLEGAL_PIN_WRITE;
    }

    port->output |= (1u << pin);

    return GPIO_OK;
}

gpio_status_t gpio_write_low(gpio_port_t* port, unsigned int pin) {
    if (port == NULL) {
        return GPIO_ERROR_NULL_PORT;
    }
    else if (!is_valid_pin(pin)) {
        return GPIO_ERROR_INVALID_PIN;
    }
    else if (is_input_pin(port->direction, pin)) {
        return GPIO_ERROR_ILLEGAL_PIN_WRITE;
    }

    port->output &= ~(1u << pin);

    return GPIO_OK;
}

gpio_status_t gpio_read(const gpio_port_t* port, unsigned int pin, gpio_value_t* out) {
    if (port == NULL) {
        return GPIO_ERROR_NULL_PORT;
    }
    else if (out == NULL) {
        return GPIO_ERROR_NULL_OUTPUT;
    }
    else if (!is_valid_pin(pin)) {
        return GPIO_ERROR_INVALID_PIN;
    }

    uint32_t target_register;
    
    if (is_input_pin(port->direction, pin)) {
        target_register = port->input;
    } else {
        target_register = port->output;
    }

    if ((target_register & (1u << pin)) != 0u) {
        *out = GPIO_HIGH;
    }
    else {
        *out = GPIO_LOW;
    }

    return GPIO_OK;
}