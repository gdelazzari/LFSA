/*
    -- LFSA Algorithm Library --
    
    Version 0.11
    
    This library lets you use my Line Following Sensor Algorithm to have a good output
    of how many lines and where them are in a reflective sensor array usually implemented
    in a line-following robot.
    
    Idea, algorithm and code by Giacomo De Lazzari
    
    ITIS A. Rossi, Vicenza (Italy)
    
    19/04/2014
*/

#include <math.h>

#include "LFSA.h"

/*
    Global library variables
*/
LFSA_ITYPE sensor_n;
SENSOR_TYPE sensor_t;

SENSOR_VTYPE delta_average;

SENSOR_VTYPE high_average;
SENSOR_VTYPE low_average;

/*
    Configure the algorithm
    
    [cfg_sensor_number] is the number of sensors in the array
    
    [cfg_sensor_type] specifies the behavoir of the sensors, if the value is lower
    when the line is black (SENSOR_BLACK_LOWER) or the opposite (SENSOR_BLACK_HIGHER)
*/
void LFSA_configure(const LFSA_ITYPE cfg_sensor_number, const SENSOR_TYPE cfg_sensor_type)
{
    sensor_n = cfg_sensor_number;
    sensor_t = cfg_sensor_type;
    
    delta_average = 0;
    high_average = 0;
    low_average = 0;
}

/*
    Algorithm core function
    
    [values] is the input values array from the sensor (aka: the values you just read)
    [result] is an array where the function will put the center-relative positions of the lines found
    [black_percentage] is the percentage of black under the sensors
    
    Returns the number of lines detected
*/
LFSA_ITYPE LFSA_process(SENSOR_VTYPE* values, LFSA_PTYPE** result, LFSA_PTYPE* black_percentage)
{
    // Processing variables
    LFSA_ITYPE i;
    
    SENSOR_VTYPE average_v = 0;
    
    static SENSOR_VTYPE* delta;
    SENSOR_VTYPE average_d = 0;
    
    static SENSOR_RESULT* analysis;

    static LFSA_PTYPE* result_a;
    
    LFSA_ITYPE lines_n = 0;
    LFSA_ITYPE black_n = 0;
    
    LFSA_ITYPE center;
    
    // Allocate memory for the variables (if needed)
    if (!delta) delta = (SENSOR_VTYPE*) malloc(sizeof(SENSOR_VTYPE) * sensor_n);
    if (!analysis) analysis = (SENSOR_RESULT*) malloc(sizeof(SENSOR_RESULT) * sensor_n);
    if (!result_a) result_a = (LFSA_PTYPE*) malloc(sizeof(LFSA_PTYPE) * (sensor_n / 2 + (sensor_n % 2)));
    
    if (!delta || !analysis || !result_a) // Did we fail allocating memory?
        return -1;
    
    // First math average of the values
    for (i = 0; i < sensor_n; i++)
        average_v += values[i];
    average_v /= sensor_n;
    
    // Calculate delta from average for every value | Calculate average absolute delta
    for (i = 0; i < sensor_n; i++)
        average_d += abs(delta[i] = values[i] - average_v);
    average_d /= sensor_n;
    
    // Keep track of the average delta
    if (delta_average) delta_average = (delta_average * 2 + average_d) / 3; else delta_average = average_d;
    
    // Check if the current average delta is "wrong" (lower than half the global average delta)
    if (average_d < delta_average / 2)
    {
        // We probably have no line on the ground, check if it is black or white (for [black_percent])
        
        SENSOR_VTYPE black_diff = abs(average_v - ((sensor_t == SENSOR_BLACK_LOWER) ? low_average : high_average)); // Difference from black value
        SENSOR_VTYPE white_diff = abs(average_v - ((sensor_t == SENSOR_BLACK_LOWER) ? high_average : low_average)); // Difference from white value
        
        *black_percentage = (black_diff < white_diff) ? 100 : 0;
        
        result = NULL;
        
        return 0;
    }
    
    // Analyse values
    for (i = 0; i < sensor_n; i++)
    {
        if (abs(delta[i]) > average_d)  // If the delta is enough big we found something, check if could be a line
            analysis[i] = ((sensor_t == SENSOR_BLACK_LOWER && delta[i] < 0) | (sensor_t == SENSOR_BLACK_HIGHER && delta[i] > 0)) ? SENSOR_LINE : SENSOR_NOLINE;
        else
          analysis[i] = SENSOR_NOLINE;
        
        if (delta[i] > 0) if (high_average) high_average = (high_average + values[i]) / 2; else high_average = values[i];
        if (delta[i] < 0) if (low_average) low_average = (low_average + values[i]) / 2; else low_average = values[i];
    }
    
    // Calculate center position
    center = sensor_n / 2 + (sensor_n % 2);
    
    // Work out the line positions and keep track of how many black spots there are
    for (i = 0; i < sensor_n; i++)
    {
        if (analysis[i] == SENSOR_LINE)
        {
            // Store starting position
            LFSA_PTYPE start = (LFSA_PTYPE) i + 1;
            
            // Find end of SENSOR_LINE values group keeping track of the black spots
            do {
              black_n++;
              i++;
            } while (analysis[i] == SENSOR_LINE && i < sensor_n);
            
            // Calculate absolute and then center-relative position of the line
            LFSA_PTYPE a_position = (start + (LFSA_PTYPE) i) / 2;
            LFSA_PTYPE r_position = a_position - (LFSA_PTYPE) center;
            
            // Store the center-relative position into the result array
            result_a[lines_n++] = r_position;
        }
    }
    
    // Assign the result array pointer
    *result = result_a;
    
    // Calculate the black percentage
    *black_percentage = (LFSA_PTYPE) black_n * 100 / (LFSA_PTYPE) sensor_n;
    
    // Return how many lines we actually found
    return lines_n;
}

