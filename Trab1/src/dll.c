#include "dll.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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
            printf("ID already exists!\n");
            return EXIT_FAILURE;
        }
        current = (Node*)current->next;
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
        dll->tail->next = (struct Node*)newNode;  // O ponteiro next do último nó (tail) aponta para o novo nó
        newNode->prev = (struct Node*)dll->tail;  // O ponteiro prev do novo nó aponta para o último nó
        dll->tail = (Node*)newNode;        // O último nó aponta para o novo nó
    }

    dll->num_elements++;
}

int MyDLLRemove(DLL *dll, uint16_t key) {
    if (dll->head == NULL) {
        printf("The list is empty.\n");
        return EXIT_FAILURE;
    }

    Node* current = dll->head;
    while (current != NULL) {
        if (current->key == key) {
            // If node to be removed is the head
            if (current == dll->head) {
                dll->head = (Node*)current->next;
                if (dll->head != NULL) {
                    dll->head->prev = NULL;
                }
            // If node to be removed is the tail
            } else if (current == dll->tail) { 
                dll->tail = (Node*)current->prev;
                if (dll->tail != NULL) {
                    dll->tail->next = NULL;
                }
            } else {
                ((Node *)current->prev)->next = current->next;
                ((Node *)current->next)->prev = current->prev;
            }
            dll->num_elements--;
            printf("Element with key %d removed from the list.\n", key);
            return EXIT_SUCCESS;
        }
        current = (Node*)current->next;
    }
    printf("Element with key %d not found in the list.\n", key);
    return EXIT_FAILURE;

}

uint8_t* MyDLLFind(DLL *dll, uint16_t key) {
    if (dll->head == NULL) {
        printf("The list is empty.\n");
        return NULL;
    }

    Node* current = dll->head;
    while (current != NULL) {
        if (current->key == key) {
            printf("Match found - ID: %d, Data: %s\n", current->key, current->data);
            return current->data;
        }
        current = (Node*)current->next;
    }
    printf("Match not found.\n");
    return NULL;
}

uint8_t* MyDLLFindNext(DLL *dll, uint16_t key) { 

    if (dll->head == NULL) {
        printf("The list is empty.\n");
        return NULL;
    }

    Node* current = dll->head;
    while (current != NULL) {
        if (current->key == key && current->next != NULL) {
            current = (Node*)current->next;
            printf("Match found - ID: %d, Data: %s\n", current->key, current->data);
            return current->data;
        }
        current = (Node*)current->next;
    }
    printf("Element not found or it is last on the list.\n");
    return NULL;
}

uint8_t* MyDLLFindPrev(DLL *dll, uint16_t key) { 

    if (dll->head == NULL) {
        printf("The list is empty.\n");
        return NULL;
    }

    Node* current = dll->head;
    while (current != NULL) {
        if (current->key == key && current->prev != NULL) {
            current = (Node*)current->prev;
            printf("Match found - ID: %d, Data: %s\n", current->key, current->data);
            return current->data;
        }
        current = (Node*)current->next;
    }
    printf("Element not found or it is first on the list.\n");
    return NULL;
}

uint8_t* MyDLLShowElements(DLL *dll) {

    int n = 1;

    if (dll->head == NULL) {
        printf("The list is empty.\n");
        return NULL;
    }

    Node* current = dll->head;
    printf("Doubly Linked List elements: \n");
    while(current != NULL) {
        printf("Element #%d - ID: %d,\t Data: %s\n", n++, current->key, current->data);
        current = (Node*)current->next;
    }
}

void MyDLLRandomFill(DLL *dll) {
    srand(time(NULL)); // Seed

    // Check if list is full
    if (dll->num_elements >= MAX_ELEMENTS) {
        printf("The list is already full. Cannot add more elements.\n");
        return;
    }

    for (int i = 0; i < MAX_ELEMENTS; i++) {
        uint16_t key = rand() % UINT16_MAX; // Generate key
        int datasize = rand() % MAX_DATA_SIZE;
        uint8_t data[datasize]; // Data array
        
        for (int j = 0; j < datasize; j++) {
            //data[j] = rand() % 128; // ascii chars
            int randValue = rand() % 62; // alphanumeric only
            if (randValue < 10) {
                data[j] = randValue + '0'; // Digit (0-9)
            } else if (randValue < 36) {
                data[j] = randValue - 10 + 'A'; // Uppercase letter (A-Z)
            } else {
                data[j] = randValue - 36 + 'a'; // Lowercase letter (a-z)
            }
        }

        if (MyDLLInsert(dll, key, data) == EXIT_FAILURE) {
            printf("Failed to insert more elements. The list is full.\n");
            break;
        }
    }
}

void MyDLLClear(DLL *dll) {
    Node *current = dll->head;
    while (current != NULL) {
        Node *temp = current;
        current = (Node*)current->next;
        temp->next = NULL;
        temp->prev = NULL;
    }

    dll->head = NULL;
    dll->tail = NULL;
    dll->num_elements = 0;

    printf("Doubly linked list cleared.\n");
}