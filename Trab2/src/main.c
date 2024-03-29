#include <stdio.h>
#include <stdlib.h>

#include "sensor.h"
#include "unity.h"

int main() 
{   
    unsigned char c;
    init_buffer(); // Initialize buffer

    do {
        printf( "Select 'A': Reads the real-time values of the variables provided by the sensor\n"
                "Select 'P': Reads the real-time value of one of the sensors\n"
                "Select 'L': Returns the last 20 samples of each variable\n"
                "Select 'R': Resets the history\n"
                "Select 'E': Exit\n"
                "Choose: ");
        do {
            scanf("%c", &c);
            printf("\n");
            getchar();
            if (c != 'A' && c != 'P' && c != 'L' && c != 'R' && c != 'E') {
                printf("Invalid option! Choose again: ");
            }
        } while (c != 'A' && c != 'P' && c != 'L' && c != 'R' && c != 'E');

        unsigned char ch;
        if (c == 'P') {
            printf( "Select 't': Reads the real-time value of the temperature\n"
                   "Select 'h': Reads the real-time value of the humidity\n"
                    "Select 'c': Reads the real-time value of the CO2\n"
                    "Choose: ");
            do {
                scanf("%c", &ch);
                printf("\n");
                process_command(c, ch);
                getchar();
                if (ch != 't' && ch != 'h' && ch != 'c') {
                    printf("Invalid option! Choose again: ");
                }
            } while (ch != 't' && ch != 'h' && ch != 'c');
        } else {
            process_command(c, ch);
        }

        uart_handler();

        unsigned char received_char;
        while ((received_char = buffer_getc())) {
            printf("%c", received_char);
        }
        printf("\n");

    } while (c != 'E');
    printf("Goodbye!\n");

    return 0;
}
