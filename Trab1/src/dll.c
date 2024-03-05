#include <stdlib.h>
#include <stdio.h>

#include "dll.h"


void MyDLLInit(DoublyLinkedList *dll) {
    
    dll->head = NULL;
    dll->tail = NULL;
    dll->num_elements = 0;
    dll->max_elements = MAX_ELEMENTS;
}

int MyDLLInsert(DoublyLinkedList *dll, uint16_t nmec, char *data) {

}

int MyDLLRemove(DoublyLinkedList *dll, uint16_t nmec) {

}

void MyDLLFind(DoublyLinkedList *dll, uint16_t nemc) {

}

void MyDLLFindNext(DoublyLinkedList *dll) {  

}

void MyDLLFindPrevious(DoublyLinkedList *dll) {

}