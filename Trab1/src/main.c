#include <stdlib.h>
#include <stdio.h>

#include "dll.h"


int main(void) {

    DLL dll;
    MyDLLInit(&dll);

    int option;
    uint16_t id;
    char name[MAX_DATA_SIZE];

    do {
        printf("------------------MENU-------------------\n"
               "01: Insert a new student\n"
               "02: Remove a student\n"
               "03: Find a student\n"
               "04: Find the next student in the list\n"
               "05: Find the previous student in the list\n"
               "06: Randomly fill the list\n"
               "07: Show Doubly Linked List elements\n"
               "08: Clear elements from the list\n"
               "00: Exit\n"
               "\nPlease choose an option: ");
    
        do{
            scanf("%d", &option);
            if (option < 0 || option > 8)
                printf("Invalid option, try again: ");
        } while (option < 0 || option > 8);
        
        printf("\n");

        switch (option) {

        case 1:
            printf("Insert ID: ");
            scanf("%hd", &id);
            printf("Enter a name: ");
            scanf("%s", name);
            MyDLLInsert(&dll, id, name);
            printf("\n");
            break;
        case 2:
            printf("Insert ID: ");
            scanf("%hd", &id);
            MyDLLRemove(&dll, id);
            printf("\n");
            break;
        case 3:
            printf("Insert ID: ");
            scanf("%hd", &id);
            MyDLLFind(&dll, id);
            printf("\n");
            break;
        case 4:
            printf("Insert ID: ");
            scanf("%hd", &id);
            MyDLLFindNext(&dll, id);
            printf("\n");
            break;
        case 5:
            printf("Insert ID: ");
            scanf("%hd", &id);
            MyDLLFindPrev(&dll, id);
            printf("\n");
            break;
        case 6:
            MyDLLRandomFill(&dll);
            printf("\n");
            break;
        case 7:
            MyDLLShowElements(&dll);
            printf("\n");
            break;
        case 8:
            MyDLLClear(&dll);
            printf("\n");
            break;
        case 0:
            printf("Goodbye!\n");
            break;
        default:
            printf("Invalid option!\n");
            break;
        }

    } while (option != 0);

    return 0;
}
