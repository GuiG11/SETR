#ifndef SENSOR_H
#define SENSOR_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_DATA 50
#define MAX_SAMPLES 20

typedef struct 
{
    int temp;
    int humidity;
    int CO2;
} Data;

void readAllData();

void readOneValue(char choice);

void returnLastSamples();

void resetHistory();

void randomFill();

void generateTestData();

#endif
