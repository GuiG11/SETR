#include <stdlib.h>
#include <stdio.h>

#include "dll.h"

int main(void) {

    DLL dll;
    MyDLLInit(&dll);

    int option;
    uint16_t key;
    char data[MAX_DATA_SIZE];

    do {
        printf("----------------MENU------------------\n"
               "01: Insert a new information\n"
               "02: Remove a info\n"
               "03: Find a info\n"
               "04: Find the next info in the list\n"
               "05: Find the previous info in the list\n"
               "06: Randomly fill the list\n"
               "07: Show all info in the list\n"
               "08: Clear the list\n"
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
            printf("Enter your user key: ");
            scanf("%hd", &key);
            printf("Enter a information: ");
            while (getchar() != '\n');
            fgets(data, MAX_DATA_SIZE, stdin);
            MyDLLInsert(&dll, key, data);
            printf("\n");
            break;
        case 2:
            printf("Enter the key to remove info: ");
            scanf("%hd", &key);
            MyDLLRemove(&dll, key);
            printf("\n");
            break;
        case 3:
            printf("Enter the key to find the info: ");
            scanf("%hd", &key);
            MyDLLFind(&dll, key);
            printf("\n");
            break;
        case 4:
            printf("Enter the key to find the info: ");
            scanf("%hd", &key);
            MyDLLFindNext(&dll, key);
            printf("\n");
            break;
        case 5:
            printf("Enter the key to find the info: ");
            scanf("%hd", &key);
            MyDLLFindPrev(&dll, key);
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
