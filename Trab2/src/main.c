#include <stdio.h>
#include <stdlib.h>

#include "sensor.h"
#include "unity.h"

int main() 
{   
    unsigned char c;
    init_buffer(); // Initialize buffer

    printf( "Select 'A': Reads the real-time values of the variables provided by the sensor\n"
            "Select 'P': Reads the real-time value of one of the sensors\n"
            "Select 'L': Returns the last 20 samples of each variable\n"
            "Select 'R': Resets the history\n"
            "Choose: ");
    scanf("%c", &c);
    printf("\n");

    buffer_putc(SOF_SYM);
    buffer_putc(' '); // Add space after each value
    buffer_putc(c);
    buffer_putc(' '); // Add space after each value

    // Open the file for reading
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Error opening file!");
        return -1;
    }

    // Read values from the file and put them into the buffer
    int value;
    while (fscanf(file, "%d", &value) == 1) {
        char str_value[20];
        snprintf(str_value, sizeof(str_value), "%d", value);
        for (int i = 0; str_value[i] != '\0'; i++) {
            buffer_putc((unsigned char)str_value[i]);
        }
        buffer_putc(' '); // Add space after each value
    }

    buffer_putc(EOF_SYM);

    uart_handler();

    unsigned char received_char;
    while ((received_char = buffer_getc())) {
         printf("%c", received_char);
    }
    printf("\n");

    return 0;
}
