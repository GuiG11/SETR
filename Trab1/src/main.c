#include <stdlib.h>
#include <stdio.h>

#include "dll.h"

int main(void) {

    DLL dll;
    MyDLLInit(&dll);

    int option;
    uint16_t key;
    char data[MAX_DATA_SIZE];

    char node[] = "info";

    do {
        printf("\n------------------ MENU ------------------\n"
               "01: Insert new %s in the list\n"
               "02: Remove %s from the list\n"
               "03: Find %s in the list\n"
               "04: Find the next %s in the list\n"
               "05: Find the previous %s in the list\n"
               "06: Randomly fill the list\n"
               "07: Show entire list\n"
               "08: Clear list\n"
               "00: Exit\n\n"
               "Please choose an option: ",node,node,node,node,node);
    
        do{
            scanf("%d", &option);
            if (option < 0 || option > 8)
                printf("Invalid option, try again: ");
        } while (option < 0 || option > 8);
        
        printf("\n");

        switch (option) {

        case 1:
            printf("Enter key: ");
            scanf("%hd", &key);
            printf("Enter %s: ",node);
            while (getchar() != '\n');
            fgets(data, MAX_DATA_SIZE, stdin);
            MyDLLInsert(&dll, key, data);
            printf("\n");
            break;
        case 2:
            printf("Enter %s's key: ",node);
            scanf("%hd", &key);
            MyDLLRemove(&dll, key);
            printf("\n");
            break;
        case 3:
            printf("Enter %s's key: ",node);
            scanf("%hd", &key);
            MyDLLFind(&dll, key);
            printf("\n");
            break;
        case 4:
            printf("Enter %s's key: ",node);
            scanf("%hd", &key);
            MyDLLFindNext(&dll, key);
            printf("\n");
            break;
        case 5:
            printf("Enter %s's key: ",node);
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
