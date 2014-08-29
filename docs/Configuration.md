# Configuration

Now let's look at some options that the library offers. They all concern about variable types. This lets you make the library faster, more memory-efficient or more precise depending on your needs. There are four configurable variable types:

+   **SENSOR_VTYPE** is the variable type that is used by the reflective sensors readings. For example if you are using an 8-bit ADC you should use `uint8_t`, if the ADC is more than 8-bit but within 16-bit you should use `uint16_t`. If you want a lot of precision you can use the `float` type but it will use more memory and CPU time (if you don't have an FPU).
+   **LFSA_PTYPE** is the variable type used to contain the results of the processing, mainly the found lines's positions and the percentage of black under the sensor array. You can use `uint8_t` if you don't want to eat up too much RAM. `int` is the default value. Even there, you can use `float` to have more precision.
+   **LFSA_ITYPE** is the integer type internally used by the library (e.g. in the for loops). Leave `int` except if you don't have a lot of memory free. If so, you can use `uint8_t`.
+   **LFSA_STYPE** is the signed integer type internally used by the library. Leave `int` as default. If you are really memory constrained then you can use `int16_t` or even `int8_t` but at your own risk, because I can't tell how big will be the numbers that will be stored in theese variables (so there's some overflow risk). Anyhow remember to use signed data types (e.g. `int16_t` and **NOT** `uint16_t`) or it will cause a lot of problems.

In summary, we can say that you can just leave the default types if you have enough memory, maybe changing `LFSA_PTYPE` to `float` to have more precision on line position values. Instead if you are running on a not very powerful microcontroller (e.g. 8-bit AVR) you can change some types to `uint8_t` to save memory and to obtain a low running time.

Again, you should be fine with the default types.
