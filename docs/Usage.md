# Usage

So, how do you use LFSA? Well, it's very simple.
(for now ignore the custom variable types e.g. `LFSA_ITYPE` or `SENSOR_VTYPE`).

There are just two functions:

```cpp
LFSA_configure(LFSA_ITYPE cfg_sensor_number, SENSOR_TYPE cfg_sensor_type);
LFSA_process(SENSOR_VTYPE* values, LFSA_PTYPE** result, LFSA_PTYPE* black_percentage);
```

### LFSA_configure

The first one, as the name says, is use to configurate the library. It is called just one time with two parameters:
+   `cfg_sensor_number` is the number of reflective sensors you are using in you array.
+   `cfg_sensor_type` is how the sensors behave when they detect a dark color. The value could be `SENSOR_BLACK_LOWER` or `SENSOR_BLACK_HIGHER`.

### LFSA_process

The other function is used to actually run the algorithm with the sensor values you've just read. You have to call the function with the following parameters:
+   `* values` is a pointer to an array of `cfg_sensor_number` elements which contains the values of the sensors that the algorithm should process.
+   `** result` is a pointer to a pointer to an array which will contain the position of the lines that the algorithm has found.
+   `* black_percentage` is a pointer to a variable which will contain the percentage of black under the sensors.

The function returns the number of lines found.

