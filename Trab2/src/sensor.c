#include <stdio.h>
#include <stdlib.h>

#include "sensor.h"

// Initialize circular buffer
void init_buffer()
{
    rxb.head = 0;
    rxb.tail = 0;
    rxb.count = 0;

    txb.head = 0;
    txb.tail = 0;
    txb.count = 0;
}

// Put a character into the buffer
void buffer_putc(unsigned char c)
{
    if (txb.count < BUF_SIZE) {
        txb.data[txb.tail] = c;
        txb.tail = (txb.tail + 1) % BUF_SIZE;
        txb.count++;
    }
} 

// Get a character from the buffer
unsigned char buffer_getc()
{
    if (rxb.count > 0) {
        unsigned char c = rxb.data[rxb.head];
        rxb.head = (rxb.head + 1) % BUF_SIZE;
        rxb.count--;           
        return c;
    } else {
        return 0; // Return 0 if buffer is empty
    }
}

// Process received command
void process_command(uint8_t cmd, SensorData *sensor_data, uint8_t data_length)
{

}

void uart_handler()
{
      while (txb.count > 0) {
        rxb.data[rxb.tail] = txb.data[txb.head];
        rxb.tail = (rxb.tail + 1) % BUF_SIZE;
        rxb.count++;
        txb.head = (txb.head + 1) % BUF_SIZE;
        txb.count--;
    }
}

int calc_checksum()
{

}
