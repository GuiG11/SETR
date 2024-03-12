/**
* \file main.c
* \brief Main function.
* \details This module provides a menu where the user can choose if they want to add,
* remove or search for data. It uses the functions implemented in \c dll.c for these operations.
*
* There is a character array variable named \c node, which is initialized with the value \c "info"
* by default. It can be changed to better suit the requirements of a specific application.
*
* \authors Guilherme Guarino 104154, Simão Pinto 102776 - 03/2024
*/

#include <stdlib.h>
#include <stdio.h>

#include "dll.h"

int main(void) {

    DLL dll;
    MyDLLInit(&dll);

    int option;
    uint16_t key;
    char data[MAX_DATA_SIZE];

    ////////////////////////////////////////////////////
    char node[] = "info";       /**< Choose data name */
    ////////////////////////////////////////////////////

    do {
        printf("\n------------------ MENU ------------------\n"
               "01: Insert new %s in the list\n"
               "02: Remove %s from the list\n"
               "03: Find %s in the list\n"
               "04: Find the next %s in the list\n"
               "05: Find the previous %s in the list\n"
               "06: Randomly fill the list\n"
               "07: Sort list in ascending order\n" 
               "08: Show entire list\n"
               "09: Clear list\n"
               "00: Exit\n\n"
               "Please choose an option: ",node,node,node,node,node);
    
        do{
            scanf("%d", &option);
            if (option < 0 || option > 9)
                printf("Invalid option, try again: ");
        } while (option < 0 || option > 9);
        
        printf("\n");

        switch (option) {

        case 1:             /* Add data */
            if (dll.num_elements >= MAX_ELEMENTS) {
                printf("Cannot insert more data. The list is full.\n");
                break; // Avoids asking user for input if list is full
            }
            
            printf("Enter user key: ");
            scanf("%hd", &key);
            
            printf("Add new %s to the list: ",node);
            while (getchar() != '\n');          // This line and the next were seen on a C programming website 
            fgets(data, MAX_DATA_SIZE, stdin);  // to know how to read data with spaces

            MyDLLInsert(&dll, key, data);
            printf("\n");
            break;
            
        case 2:             /* Remove data */
            if (MyDLLisEmpty(&dll)) {
                printf("The list is empty.\n");
                break;  // Avoids asking user for input if list is empty
            } 

            printf("Enter user key: ");
            scanf("%hd", &key);

            MyDLLRemove(&dll, key);
            printf("\n");
            break;

        case 3:             /* Find data */
            if (MyDLLisEmpty(&dll)) {
                printf("The list is empty.\n");
                break;   // Avoids asking user for input if list is empty
            }

            printf("Enter user key: ");
            scanf("%hd", &key);

            MyDLLFind(&dll, key);
            printf("\n");
            break;

        case 4:             /* Find next data */
            if (MyDLLisEmpty(&dll)) {
                printf("The list is empty.\n");
                break;   // Avoids asking user for input if list is empty
            }

            printf("Enter user key: ");
            scanf("%hd", &key);
            
            MyDLLFindNext(&dll, key);
            printf("\n");
            break;

        case 5:             /* Find previous data */
            if (MyDLLisEmpty(&dll)) {
                printf("The list is empty.\n");
                break;   // Avoids asking user for input if list is empty
            }

            printf("Enter user key: ");
            scanf("%hd", &key);

            MyDLLFindPrev(&dll, key);
            printf("\n");
            break;

        case 6:             /* Random Fill */
            if (dll.num_elements >= MAX_ELEMENTS) {
                printf("The list is full.\n");
                break;
            }
            
            MyDLLRandomFill(&dll);
            printf("\n");
            break;

        case 7:             /* Sort list */
            if (MyDLLisEmpty(&dll)) {
                printf("The list is empty.\n");
                break;
            }

            MyDLLAscendingOrder(&dll);
            printf("\n");
            break;

        case 8:             /* Show list */
            MyDLLShowElements(&dll);
            printf("\n");
            break;
            
        case 9:             /* Clear list */
            if (MyDLLisEmpty(&dll)) {
                printf("The list is empty.\n");
                break;
            }

            MyDLLClear(&dll);
            printf("\n");
            break;

        case 0:
            printf("Goodbye!\n");
            break;

        default:
            printf("ERROR!\n");
            break;
        }

    } while (option != 0);

    return 0;
}