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
int process_command(unsigned char c, unsigned char ch)
{
    // Open the file for reading
    FILE *file = fopen("data.csv", "r");
    if (file == NULL) {
        printf("Error opening file!");
        return -1;
    }

    int temp, humidity, co2;
    char str_value[20];
    char checksum_str[5];
    switch (c)
    {
    case 'A':
        // Read values from the file and put them into the buffer
        while (fscanf(file, "%d, %d, %d", &temp, &humidity, &co2) == 3) {
            buffer_putc(SOF_SYM);
            buffer_putc(' '); // Add space after each value
            buffer_putc(c);
            buffer_putc(' '); 
            // Convert values to formatted string
            if (temp >= 0)
                sprintf(str_value, "+%d %d %d", temp, humidity, co2);
            else
                sprintf(str_value, "%d %d %d", temp, humidity, co2);

            for (int i = 0; str_value[i] != '\0'; i++) {
                buffer_putc(str_value[i]);
            }
            buffer_putc(' ');
            int checksum = calc_checksum('A', str_value);
            // Convert checksum to string
            sprintf(checksum_str, "%d", checksum);
            for (int i = 0; checksum_str[i] != '\0'; i++) {
                buffer_putc(checksum_str[i]);
            }
            buffer_putc(' '); 
            buffer_putc(EOF_SYM);
            buffer_putc('\n');
        }
        break;

    case 'P':
        while (fscanf(file, "%d, %d, %d", &temp, &humidity, &co2) == 3) {
            buffer_putc(SOF_SYM);
            buffer_putc(' '); 
            buffer_putc(c);
            buffer_putc(' '); 
            buffer_putc(ch);
            buffer_putc(' '); 
                
            if (ch == 't') {
                sprintf(str_value, "%d", temp);
            }
            else if (ch == 'h') {
                sprintf(str_value, "%d", humidity);
            }
            else if (ch == 'c') {
                sprintf(str_value, "%d", co2);
            }

            for (int i = 0; str_value[i] != '\0'; i++) {
                buffer_putc(str_value[i]);
            }

            buffer_putc(' '); 

            int checksum = calc_checksum('P', str_value);
            // Convert checksum to string
            sprintf(checksum_str, "%d", checksum);
            for (int i = 0; checksum_str[i] != '\0'; i++) {
                buffer_putc(checksum_str[i]);
            }

            buffer_putc(' '); 
            buffer_putc(EOF_SYM);
            buffer_putc('\n');
        }
        break;

    default:
        break;
    }

    fclose(file);
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

int calc_checksum(unsigned char cmd, const char *data) {
    int checksum = 0;

    checksum += cmd;
    while (*data != '\0') {
        if (*data != ' ')
            checksum += *data;
        data++;
    }

    return checksum;
}