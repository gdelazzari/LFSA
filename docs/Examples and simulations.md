# Benchmark and tests

After writing it I tested the library as much as I could and the results where pretty interesting. The library ran very fast even on microcontrollers (mainly referring to STM32) even without FPU.

Below you can find the benchmark results and the report of the simulations.

## Benchmarks

The library was tested on a Linux system (AMD FX-8350 64-bit 8 Core @ 4.0 GHz, 64-bit, Ubuntu 14.04), on an STM32F100RB microcontroller (ARM Cortex-M3 @ 24MHz, 32-bit, no FPU) and on Arduino (AVR core @ 16MHz, 8-bit, no FPU).

All the test cases were using an array of 7 sensors.

Below are the results

| Platform | Core | Bits | Clock | Exec. time (float) | Exec time (int) |
| -- | -- | -- | -- | -- | -- |
| AMD Linux | 8 | 64-bit | 4.0 GHz | 2.2 µS | 1.3 µS |
| Cortex-M3 | 1 | 32-bit | 24 MHz | 3.5 µS | 2.1 µS |
| Arduino | 1 | 8-bit | 16 MHz | 13.2 µS | 7.1 µS |


## Simulations

The algorithm has not been tested on a robot _yet_, but I ran some simulations with different light conditions and various noise. The results where actually very good.

The simulations input data is below, it is represented by a graph where the X axe contains the sensor numbers and the Y axe the sensor values. In every case the algorithm answered correctly (please note that theese are the same test cases which are included in the _example.c_ file of the library).
