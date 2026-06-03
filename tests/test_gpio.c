/*
 * SyntaxSculptor
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdlib.h>
#include <stdio.h>

#include "unity.h"

static uint32_t registers;

void tearDown(void) {

}

void setUp(void) {
    registers = 0x00000000;
}

int main(void) {
    UNITY_BEGIN();

    return UNITY_END();
}