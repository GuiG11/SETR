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

    // Open the file for reading
    FILE *file = fopen("data.csv", "r");
    if (file == NULL) {
        printf("Error opening file!");
        return -1;
    }

    // Read values from the file and put them into the buffer
    int temp, humidity, co2;
    while (fscanf(file, "%d, %d, %d", &temp, &humidity, &co2) == 3) {
        buffer_putc(SOF_SYM);
        buffer_putc(' '); 
        buffer_putc(c);
        buffer_putc(' '); 
        char str_value[20];
        snprintf(str_value, sizeof(str_value), "%d %d %d", temp, humidity, co2);
        for (int i = 0; str_value[i] != '\0'; i++) {
            buffer_putc((unsigned char)str_value[i]);
        }
        buffer_putc(' '); // Add space after each value
        buffer_putc(EOF_SYM);
        buffer_putc('\n');
    }
    fclose(file);

    uart_handler();

    unsigned char received_char;
    while ((received_char = buffer_getc())) {
         printf("%c", received_char);
    }
    printf("\n");

    return 0;
}
