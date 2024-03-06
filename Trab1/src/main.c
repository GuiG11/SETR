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
        printf("----------------MENU----------------\n"
               "01: Insert a new student\n"
               "02: Remove a student\n"
               "03: Find a student\n"
               "04: Search for a student in the list\n"
               "05: Show Doubly Linked List elements\n"
               "00: Exit\n"
               "Please choose an option: \n");
    
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            printf("Insert id: \n");
            scanf("%hd", &id);
            printf("Enter a name: \n");
            scanf("%s", name);
            MyDLLInsert(&dll, id, name);
            printf("\n");
            break;
        case 2:
            MyDLLRemove(&dll, id);
            break;
        case 3:
            MyDLLFind(&dll, id);
            break;
        case 4:
            MyDLLFindNextPrev(&dll);
        case 5:
            MyDLLShowElements(&dll);
            printf("\n");
        default:
            break;
        }
    } while (option >= 1 && option <= 5);

    return 0;
}
