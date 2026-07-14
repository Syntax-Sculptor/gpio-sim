# GPIO-Sim

## Introduction

GPIO-Sim is a C library that simulates 32-pin GPIO registers. Along with the library are numerous unit tests written using the [Unity](https://github.com/ThrowTheSwitch/Unity) library.

GPIO-Sim utilizes three 32-bit registers: `direction`, `input`, and `output`, which does the following:
- `direction` determines whether a pin is input or output
- `input` determines whether an input pin is high/low
- `output` determines whether an output pin is high/low

This is a learning project so I can familiarize myself with:
- Embedded Systems principles
- Test Driven Development
- GitHub Actions

## Dependencies

To compile this project, you will need:

- A Linux-based system
- GCC (any version that can compile C11)
- Make

The Unity library is already provided in the repo, so it does not need to be installed separately.

## Building and Testing

To build the GPIO object file, run `make` or `make gpio`. Running the command will create `gpio.o` in `build/`.

To run the unit tests, run `make test`. It will compile the test runner and run it.

To remove the built artifacts, run `make clean`.
