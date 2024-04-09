/**
* \file main.c
* \brief Main function.
* \details This module provides a menu where the user can choose if they want to read real-time data variables from the sensor,
* return the last 20 samples of each variable or reset the data history.
* They are also able to specify which variable they would like to read if not interested in reading all the variables.
* This module uses the functions implemented in \c sensor.c for these operations.
*
* \authors Guilherme Guarino 104154, Simão Pinto 102776 - 03/2024
*/

#include <stdio.h>
#include <stdlib.h>

#include "sensor.h"
#include "unity.h"

int main() 
{   
    unsigned char cmd;
    unsigned char ch;
    init_buffer(); // Initialize buffer

    do {
        printf( "Select 'A': Reads the real-time values of the variables provided by the sensor\n"
                "Select 'P': Reads the real-time value of one of the sensors\n"
                "Select 'L': Returns the last 20 samples of each variable\n"
                "Select 'R': Resets the history\n"
                "Select 'E': Exit\n"
                "\nSelect a command: ");

        scanf(" %c", &cmd);
        getchar(); // Consume newline character

        if (cmd != 'A' && cmd != 'P' && cmd != 'L' && cmd != 'R' && cmd != 'E') {
            printf("Invalid option! Choose again: ");
        }

        switch (cmd)
        {
        case 'A':
            process_command(cmd, 0);
            break;
        
        case 'P':
            printf( "\nSelect 't': Reads the real-time value of the temperature\n"
                    "Select 'h': Reads the real-time value of the humidity\n"
                    "Select 'c': Reads the real-time value of the CO2\n"
                    "\nSelect a command: ");
            do {
                scanf(" %c", &ch);
                getchar();

                if (ch != 't' && ch != 'h' && ch != 'c') {
                    printf("Invalid option! Choose again: ");
                }
            } while (ch != 't' && ch != 'h' && ch != 'c');
            process_command(cmd, ch);
            break;

        case 'L':
            process_command(cmd, 0);
            break;

        case 'R':
            process_command(cmd, 0);
            printf("\nHistory reset!");
            break;

        default:
            break;
        }

        printf("\n");
        
        uart_handler();

        unsigned char received_char;
        while ((received_char = buffer_getc())) {
            printf("%c", received_char);
        }
        printf("\n");

    } while (cmd != 'E');
    
    printf("Goodbye!\n");

    return 0;
}
