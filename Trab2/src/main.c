#include <stdio.h>
#include <stdlib.h>

#include "sensor.h"
#include "unity.h"

int main() 
{   
    char choice;

    // randomFill();
    generateTestData();

    do {
        printf( "\nSelect 'A' to read real-time values of the variables provided by the sensor\n"
                "Select 'P' to read real-time value of one of the sensors\n"
                "Select 'L' to see the last 20 samples of each variable\n"
                "Select 'R' to reset the history\n"
                "Select 'E' to exit\n\n"
                "Choose: ");

        do 
        {        
            scanf("%c", &choice);
            getchar();
            if (choice != 'A' && choice != 'P' && choice != 'L' && choice != 'R' && choice != 'E') {
                printf("Invalid option! Choose again: ");
            }

        } while (choice != 'A' && choice != 'P' && choice != 'L' && choice != 'R' && choice != 'E'); 

        switch (choice)
        {
        case 'A':
            // lê todos os valores registados pelo sensor
            readAllData();
            break;

        case 'P':
            // lê um dos valores registados pelo sensor
            printf( "\nSelect 'T' if you want to read temperature values\n"
                    "Select 'H' if you want to read humidity values\n"
                    "Select 'C' if you want to read CO2 values\n\n"
                    "Choose: ");

            do 
            {        
                scanf("%c", &choice);
                getchar();
                if (choice != 'T' && choice != 'H' && choice != 'C') {
                    printf("Invalid option! Choose again: ");
                }

            } while (choice != 'T' && choice != 'H' && choice != 'C');  

            readOneValue(choice);      
            break;

        case 'L':
            // retorna as últimas 20 amostras dos valores lidos pelo sensor
            returnLastSamples();
            break;

        case 'R':
            // limpa o histórico
            resetHistory();
            break;        

        case 'E':
            printf("Goodbye!\n");
            break;

        default:
            break;
        }

    } while (choice != 'E');

    return 0;
}
