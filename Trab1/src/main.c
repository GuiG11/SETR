#include <stdlib.h>
#include <stdio.h>

#include "dll.h"

int main(void) {

    DLL dll;
    MyDLLInit(&dll);

    int option;
    uint16_t number;
    char location[MAX_DATA_SIZE];

    do {
        printf("------------------MENU-------------------\n"
               "01: Insert a new locker\n"
               "02: Remove a locker\n"
               "03: Find a locker\n"
               "04: Find the next locker in the list\n"
               "05: Find the previous locker in the list\n"
               "06: Randomly fill the list\n"
               "07: Show all lockers in the list\n"
               "08: Clear lockers from the list\n"
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
            printf("Enter your locker number: ");
            scanf("%hd", &number);
            printf("Enter your locker location: ");
            while (getchar() != '\n');
            fgets(location, MAX_DATA_SIZE, stdin);
            MyDLLInsert(&dll, number, location);
            printf("\n");
            break;
        case 2:
            printf("Enter locker number: ");
            scanf("%hd", &number);
            MyDLLRemove(&dll, number);
            printf("\n");
            break;
        case 3:
            printf("Enter locker number: ");
            scanf("%hd", &number);
            MyDLLFind(&dll, number);
            printf("\n");
            break;
        case 4:
            printf("Enter locker number: ");
            scanf("%hd", &number);
            MyDLLFindNext(&dll, number);
            printf("\n");
            break;
        case 5:
            printf("Enter locker number: ");
            scanf("%hd", &number);
            MyDLLFindPrev(&dll, number);
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
            printf("ERROR!\n");
            break;
        }

    } while (option != 0);

    return 0;
}
