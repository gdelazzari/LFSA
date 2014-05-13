LFSA Library
--------------------------------------------------------

This library lets you use my Line Following Sensor Algorithm to have a good output
of how many lines and where them are in a reflective sensor array usually implemented
in a line-following robot.

Before using the library, check the header file and configure the library with the best settings for you.

You should include the header files needed to use malloc() and where NULL is defined (usually stdlib.h).
Then you have to set the variable types that the library should use:

SENSOR_VTYPE is the variable type that is used by the reflective sensors readings. For example if you are using an 8-bit ADC you should use [uint8_t], if the ADC is more than 8-bit but within 16-bit you should use [uint16_t]. If you want a lot of precision you can use the [float] type but it will use more memory and CPU time (if you don't have an FPU).

LFSA_PTYPE is the variable type used to contain the results of the processing, mainly the found lines's positions and the percentage of black under the sensor array. You can use [uint8_t] if you don't want to eat up too much RAM. [int] is the default value. Even there, you can use [float] to have more precision.

LFSA_ITYPE is the integer type internally used by the library e.g. in the [for] loops. Leave [int] except if you don't have a lot of memory free. If so, you can use [uint8_t].

This is all... just check the header file comments and the example program to understand how the library works and...

Have fun!

--------------------------------------------------------

Idea, algorithm and code by Giacomo De Lazzari

ITIS A. Rossi, Vicenza (Italy)

19/04/2014
