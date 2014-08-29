# LFSA Quick Start guide

LFSA stands for _Line Following Sensor Array Algorithm_. As the name says it is an algorithm useful to process data coming from a reflective line sensor usually mounted on a robot.

It works with sensor arrays; you can have 4, 5, 6 or whatever number of sensors you want.

What tries the algorithm to do is not just finding where the line(s) is/are, but mainly working with noisy signals that are very common in this type of readings (think for example of someone taking a picture with flash near the robot).

The algorithm does not require any type of calibration because it's not using a "comparative" approach (e.g. "if value is higher than X then the ground is white, otherwise it is black"), so it is even simpler to use but also more powerful because of its adaptability.

LFSA is available as a C library (a .c and a .h file) that you can easly integrate in your project.
