/**
* \file dll.c
* \brief Implementation of a Doubly Linked List (DLL) module.
* \details This module provides functionalities to manipulate a Doubly Linked List (DLL).
* It includes functions for initialization, insertion, removal, searching,
* displaying elements, random filling, and clearing the DLL.
*/

#include "dll.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

char node[] = "info";

void MyDLLInit(DLL *dll) {
    dll->head = NULL;
    dll->tail = NULL;
    dll->num_elements = 0;
}

int MyDLLInsert(DLL *dll, uint16_t key, uint8_t data[]) {

    if (dll->num_elements >= MAX_ELEMENTS)
    {
        printf("Failed to insert more information. The list is full.\n");
        return EXIT_FAILURE;
    }

    printf("Enter key: ");
    scanf("%hd", &key);

    Node* current = dll->head;
    while(current != NULL) {
        if (current->key == key) {
            printf("Key already exists.\n");
            return EXIT_FAILURE;
        }
        current = (Node*)current->next;
    }

    printf("Enter %s: ",node);
    while (getchar() != '\n');
    fgets(data, MAX_DATA_SIZE, stdin);

    // Gives the memory address of the next available node in the array 
    Node* newNode = &dll->elements[dll->num_elements];  
    newNode->key = key;
    for (int i = 0; i < MAX_DATA_SIZE; i++) {
        newNode->data[i] = data[i];
    }

    newNode->next = NULL;
    newNode->prev = NULL;
    
    // If list is empty the node is both the head and tail 
    if (dll->head == NULL) {  
        dll->head = newNode;
        dll->tail = newNode;  
    } else {
        dll->tail->next = (struct Node*)newNode;  
        newNode->prev = (struct Node*)dll->tail;  
        dll->tail = (Node*)newNode;        
    }

    dll->num_elements++;

    return EXIT_SUCCESS;
}

int MyDLLRemove(DLL *dll, uint16_t key) {
    if (dll->head == NULL) {
        printf("The list is empty.\n");
        return EXIT_FAILURE;
    }

    printf("Enter %s's key: ",node);
    scanf("%hd", &key);

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
            printf("%s with key number %d successfully removed.\n", node, key);
            return EXIT_SUCCESS;
        }
        current = (Node*)current->next;
    }
    printf("%s with key number %d not found.\n", node, key);
    return EXIT_FAILURE;

}

uint8_t* MyDLLFind(DLL *dll, uint16_t key) {
    if (dll->head == NULL) {
        printf("The list is empty.\n");
        return NULL;
    }

    printf("Enter %s's key: ",node);
    scanf("%hd", &key);

    Node* current = dll->head;
    while (current != NULL) {
        if (current->key == key) {
            printf("User found - key: %d, %s: %s\n", current->key, node, current->data);
            return current->data;
        }
        current = (Node*)current->next;
    }
    printf("Key not found.\n");
    return NULL;
}

uint8_t* MyDLLFindNext(DLL *dll, uint16_t key) { 

    if (dll->head == NULL) {
        printf("The list is empty.\n");
        return NULL;
    }

    printf("Enter %s's key: ",node);
    scanf("%hd", &key);

    Node* current = dll->head;
    while (current != NULL) {
        if (current->key == key && current->next != NULL) {
            current = (Node*)current->next;
            printf("User found - key: %d, %s: %s\n", current->key, node, current->data);
            return current->data;
        }
        current = (Node*)current->next;
    }
    printf("There is no %s after this one.\n", node);
    return NULL;
}

uint8_t* MyDLLFindPrev(DLL *dll, uint16_t key) { 

    if (dll->head == NULL) {
        printf("The list is empty.\n");
        return NULL;
    }

    printf("Enter %s's key: ",node);
    scanf("%hd", &key);

    Node* current = dll->head;
    while (current != NULL) {
        if (current->key == key && current->prev != NULL) {
            current = (Node*)current->prev;
            printf("User found - key: %d, %s: %s\n", current->key, node, current->data);
            return current->data;
        }
        current = (Node*)current->next;
    }
    printf("There is no %s before this one.\n", node);
    return NULL;
}

uint8_t* MyDLLShowElements(DLL *dll) {

    int n = 1;

    if (dll->head == NULL) {
        printf("The list is empty.\n");
        return NULL;
    }

    Node* current = dll->head;
    printf("All %s in the list: \n", node);
    while(current != NULL) {
        printf("User #%d - key: %d,\t %s: %s\n", n++, current->key, node, current->data);
        current = (Node*)current->next;
    }
}

void MyDLLRandomFill(DLL *dll) {
    srand(time(NULL)); // Seed

    // Check if list is full
    if (dll->num_elements >= MAX_ELEMENTS) {
        printf("The list is already full. Cannot add more information.\n");
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
        data[datasize] = '\0'; // Null terminate the string

        if (MyDLLInsert(dll, key, data) == EXIT_FAILURE) {
            printf("Failed to insert more information. The list is full.\n");
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

    printf("List cleared.\n");
}