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

    Node* current = dll->head;
    while(current != NULL) {
        if (current->key == key) {
            printf("Id already exists!\n");
            return EXIT_FAILURE;
        }
        current = current->next;
    }

    Node* newNode = &dll->elements[dll->num_elements];  // Atribui o endereço de memória do próximo nó disponível no array de elementos
    newNode->key = key;
    for (int i = 0; i < MAX_DATA_SIZE; i++) {
        newNode->data[i] = data[i];
    }

    newNode->next = NULL;
    newNode->prev = NULL;
    
    if (dll->head == NULL) {  // Se a lista estiver vazia o novo nó torna-se tanto o head como o tail da DLL
        dll->head = newNode;
        dll->tail = newNode;
    } else {
        dll->tail->next = newNode;  // O ponteiro next do último nó (tail) aponta para o novo nó
        newNode->prev = dll->tail;  // O ponteiro prev do novo nó aponta para o último nó
        dll->tail = newNode;        // O último nó aponta para o novo nó
    }

    dll->num_elements++;
}

int MyDLLRemove(DLL *dll, uint16_t key) {

}

void MyDLLFind(DLL *dll, uint16_t key) {

}

void MyDLLFindNextPrev(DLL *dll) {  

}

void MyDLLShowElements(DLL *dll) {

    Node* current = dll->head;
    printf("Doubly Linked List elements: \n");
    while(current != NULL) {
        printf("ID: %d, Name: %s\n", current->key, current->data);
        current = current->next;
    }
}