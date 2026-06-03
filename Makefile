.PHONY: all clean test gpio

CC := gcc
CFLAGS := -Wall -Wextra -std=c11
SRC := src/gpio.c
OUT := -o build/gpio

all: gpio

gpio:
	mkdir -p build
	$(CC) $(SRC) $(CFLAGS) $(OUT)

clean:
	rm -rf build/