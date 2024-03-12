/**
* \file main.c
* \brief Main function.
* \details This module provides a menu where
* user can choose if he wants add, remove or
* search for data.
*
* \authors Guilherme Guarino 104154, Simão Pinto 102776 - 2024
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

    char node[] = "info";  // Choose data type

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
            MyDLLInsert(&dll, key, data);
            printf("\n");
            break;
        case 2:             /* Remove data */
            MyDLLRemove(&dll, key);
            printf("\n");
            break;
        case 3:             /* Find data */
            MyDLLFind(&dll, key);
            printf("\n");
            break;
        case 4:             /* Find next data */
            MyDLLFindNext(&dll, key);
            printf("\n");
            break;
        case 5:             /* Find previous data */
            MyDLLFindPrev(&dll, key);
            printf("\n");
            break;
        case 6:             /* Random Fill */
            MyDLLRandomFill(&dll);
            printf("\n");
            break;
        case 7:             /* Sort list */
            MyDLLAscendingOrder(&dll);
            printf("\n");
            break;
        case 8:             /* Show list */
            MyDLLShowElements(&dll);
            printf("\n");
            break;
        case 9:             /* Clear list */
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
