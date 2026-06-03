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