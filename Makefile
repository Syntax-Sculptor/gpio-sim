# ------------------------------------------
# SyntaxSculptor
# 
# SPDX-License-Identifier: MIT
# ------------------------------------------
 
.PHONY: all clean test gpio

CC := gcc
CFLAGS := -Wall -Wextra -std=c11 -Wpedantic -Werror
INCLUDES := -I lib/
TEST_INCLUDES := -I ext/unity/
SRC := src/gpio.c
TESTS := tests/test_gpio.c ext/unity/unity.c
TESTS_OUT := build/tests
OUT := build/gpio.o

all: gpio

gpio:
	mkdir -p build
	$(CC) -c $(SRC) $(CFLAGS) $(INCLUDES) -o $(OUT)

test:
	mkdir -p build
	$(CC) $(SRC) $(TESTS) $(CFLAGS) $(TEST_INCLUDES) $(INCLUDES) -o $(TESTS_OUT)
	./$(TESTS_OUT)

clean:
	rm -rf build/