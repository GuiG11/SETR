#include <stdlib.h>
#include <stdio.h>

#include "dll.h"

void MyDLLInit(DLL *dll) {
    dll->head = NULL;
    dll->tail = NULL;
    dll->num_elements = 0;
}

int MyDLLInsert(DLL *dll, uint16_t key, uint8_t data[]) {

    if (dll->num_elements >= MAX_ELEMENTS)
    {
        printf("Doubly Linked List is full!\n");
        return EXIT_FAILURE;
    }

    Node* newNode = &dll->elements[dll->num_elements]; 
    newNode->key = key;
    for (int i = 0; i < MAX_DATA_SIZE; i++) {
        newNode->data[i] = data[i];
    }

    newNode->next = NULL;
    newNode->prev = NULL;
    
    if (dll->head == NULL) {  
        dll->head = newNode;
        dll->tail = newNode;  
    } else {
        dll->tail->next = newNode;  
        newNode->prev = dll->tail; 
        dll->tail = newNode;        
    }

    dll->num_elements++;
    return EXIT_SUCCESS;
}

int MyDLLRemove(DLL *dll, uint16_t key) {
    // Implementation for removal function
    return 0;
}

uint8_t* MyDLLFind(DLL *dll, uint16_t key) {
    if (dll->head == NULL) {
        printf("The list is empty.\n");
        return NULL;
    }

    Node* current = dll->head;
    while (current != NULL) {
        if (current->key == key) {
            printf("Student found - ID: %d, Name: %s\n", current->key, current->data);
            return current->data;
        }
        current = current->next;
    }
    printf("Student not found.\n");
    return NULL;
}

void MyDLLFindNextPrev(DLL *dll) {  
    // Implementation for find next/prev function
}

void MyDLLShowElements(DLL *dll) {
    Node* current = dll->head;
    printf("Doubly Linked List elements: \n");
    while(current != NULL) {
        printf("Id: %d, Name: %s\n", current->key, current->data);
        current = current->next;
    }
}
