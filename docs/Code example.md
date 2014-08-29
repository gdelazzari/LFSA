# Code example

Let's show a piece of code where LFSA is used. The example can be applied very well to a microcontroller which is driving a line-following robot with a PID.

```cpp
int main()
{
    // Configure LFSA
    LFSA_configure (7, SENSOR_BLACK_LOWER);

    // Other code
    ...

    return 0;
}

void INTERRUPT_sensorRead(void)
{
    // Local variables
    int values[7];
    int lines_n, black_percentage;
    float* lines;

    // Read the sensor values
    int i;
    for (i = 0; i < 7; i++)
        values[i] = ADC_readChannel(i);

    // Run the library
    lines_n = LFSA_process(values, &lines, &black_percentage);

    // Give the results to the PID
    if (lines_n == 1)
        PID_error = lines[0]; // Tell the PID to follow the line we found
    else if (lines_n > 1)
        // Do something special when you have more than 1 line
    else {
        if (black_percentage > 50)
            // We probably have a line running perpendicular
            // over all the sensors, act accordingly
        else
            PID_error = 0.00f; // Go forward if there are no lines
    }

    return;
}
```

As you can see it is as simple as calling `LFSA_configure` once and then calling `LFSA_process` every time you have a set of values ready. You can then do whatever you want with the return values.

Easy, or not?
