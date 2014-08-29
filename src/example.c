/*
    LFSA Example Program
    
    This program tests the LFSA library
    
    Idea, algorithm and code by Giacomo De Lazzari
    ITIS A. Rossi, Vicenza (Italy)
    giacky98.mail@gmail.com
    
    Copyright (C) 2014

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include <stdio.h>
#include <unistd.h>

#include "LFSA.h"

#define TEST_N          10
#define SENSOR_N        7

int test[TEST_N][SENSOR_N] = {
    { 78, 81, 32, 80, 80, 77, 80 }, // -1 with normal light
    { 70, 73, 71, 72, 26, 69, 72 }, // +1 with low light
    { 51, 50, 52, 53, 54, 21, 52 }, // +2 with very low light
    { 45, 99, 98, 99, 97, 97, 98 }, // -3 with high light
    { 78, 31, 79, 80, 80, 28, 80 }, // -2 ; +2
    { 78, 34, 79, 80, 36, 80, 37 }, // -2 ; +1 ; +3
    
    { 78, 81, 79, 80, 80, 80, 82 }, // all white
    { 32, 34, 36, 35, 36, 32, 31 }, // all black
    { 78, 81, 56, 55, 81, 80, 80 }, // -0.5
    { 78, 81, 79, 80, 81, 54, 55 }, // +2.5
};

int main()
{
    printf("Configuring...\n");
	  LFSA_configure(SENSOR_N, SENSOR_BLACK_LOWER);
    printf("Done, running some test\n\n");
    
    int black_percent;
    int* lines;
    int lines_n;
    
    int i; for (i = 0; i < 10; i++)
    {
        lines_n = LFSA_process((int *) test[i % TEST_N], &lines, (int *) &black_percent);
        
        printf("TEST %i\nFound %i line(s), %i%% black\n", i + 1, lines_n, black_percent);
        
        int j; for (j = 0; j < lines_n; j++)
            printf("Line %i: %i\n", j + 1, *(lines + j));
        
        printf("\n");
    }
    
    printf("Finish\n\n");
	
    return 0;
}
