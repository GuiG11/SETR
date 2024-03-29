#ifndef SENSOR_H
#define SENSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BUF_SIZE 128
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

// Initialize circular buffer
void init_buffer();

// Put a character into the buffer
void buffer_putc(unsigned char c);

// Get a character from the buffer
unsigned char buffer_getc();

// Process received command
void process_command();

void uart_handler();

int calc_checksum();

# endif
