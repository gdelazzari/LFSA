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

#ifndef _LFSA_H
#define _LFSA_H


/*
    Configure the includes considering that we need
    -> malloc
    -> NULL
    
    <math.h> is already included in the library .c file
*/
#include <stdlib.h>

/*
    Configure the variable types used
    
    You can adjust them to save RAM memory or to have more precision
*/
#define SENSOR_VTYPE        unsigned int	// Variable type for sensor values
                                        	// -> uint8_t for ADC up to 8bit
                                        	// -> uint16_t for ADC up to 16bit
                                        	// -> float for precision, scale is up to you

#define LFSA_PTYPE          int				// Variable type for line position indication and percentages (aka. return type)
											// Must be a signed variable type
                                        
#define LFSA_ITYPE          unsigned int	// Variable type for general numbers
                                        	// (change to uint8_t or unsigned char if you don't have a lot of memory free)

#define LFSA_STYPE        	int				// Variable type for signed numbers, internally used by library
											// Leave int or if memory constrained put short (char/int8_t) at your own risk,
											// don't know how big is the data which goes there

/*
    Used to represent the line sensors behavoir
*/
typedef enum {
    SENSOR_BLACK_LOWER = 0,
    SENSOR_BLACK_HIGHER = 1
} SENSOR_TYPE;

/*
    Used to represent the analysed result of a single sensor (internally used, used should not care)
*/
typedef enum {
	SENSOR_NOLINE = 0,
    SENSOR_LINE = 1
} SENSOR_RESULT;

/*
    Configure the algorithm
    
    [cfg_sensor_number] is the number of sensors in the array
    
    [cfg_sensor_type] specifies the behavoir of the sensors, if the value is lower
    when the line is black (SENSOR_BLACK_LOWER) or the opposite (SENSOR_BLACK_HIGHER)
*/
void LFSA_configure(const LFSA_ITYPE cfg_sensor_number, const SENSOR_TYPE cfg_sensor_type);

/*
    Algorithm core function
    
    [values] is the input values array from the sensor (aka: the values you just read)
    [result] is an array where the function will put the center-relative positions of the lines found
    [black_percentage] is the percentage of black under the sensors
    
    Returns the number of lines detected
*/
LFSA_ITYPE LFSA_process(SENSOR_VTYPE* values, LFSA_PTYPE** result, LFSA_PTYPE* black_percentage);


#endif

