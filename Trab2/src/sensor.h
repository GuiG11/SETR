#ifndef SENSOR_H
#define SENSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BUF_SIZE 32
#define SOF_SYM '#'
#define EOF_SYM '!'

// UART circular buffer structure
typedef struct {
    unsigned char data[BUF_SIZE];
    unsigned int head;
    unsigned int tail;
    unsigned int count;
} circularBuffer;


// UART reception and transmission buffers
static circularBuffer rxb; // Reception buffer
static circularBuffer txb; // Transmission buffer

typedef struct {
    int32_t temp;
    int32_t humidity;
    int32_t CO2;
} SensorData;

// Initialize circular buffer
void init_buffer();

// Put a character into the buffer
void buffer_putc(unsigned char c);

// Get a character from the buffer
unsigned char buffer_getc();

// Process received command
void process_command(uint8_t cmd, SensorData *sensor_data, uint8_t data_length);

void uart_handler();

int calc_checksum();

# endif
