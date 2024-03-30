#ifndef SENSOR_H
#define SENSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BUF_SIZE 33554432
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
int process_command(unsigned char c, unsigned char ch);

void uart_handler();

int calc_checksum(unsigned char cmd, const char *data);

# endif
