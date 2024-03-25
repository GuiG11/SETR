/**
* \file dll.c
* \brief Implementation of a Doubly Linked List (DLL) module.
* \details This module provides functionalities to manipulate a Doubly Linked List (DLL).
* It includes functions for initialization, insertion, removal, searching,
* displaying elements, sorting elements, random filling, and clearing the DLL.
*
* \authors Guilherme Guarino 104154, Simão Pinto 102776 - 03/2024
*/

#include "dll.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>


void MyDLLInit(DLL *dll) 
{    
    // Initialize the DLL structure
    dll->head = NULL;
    dll->tail = NULL;
    dll->num_elements = 0;
}

bool MyDLLisEmpty(DLL *dll)
{
    if (dll->head == NULL) {
        return true;
    } else {
        return false;
    }
}

int MyDLLInsert(DLL *dll, uint16_t key, uint8_t data[]) 
{
    // Check if list is full
    if (dll->num_elements >= MAX_ELEMENTS) {
        return EXIT_FAILURE;
    }
    
    // Checks if the key already exists in the list
    Node* current = dll->head;
    while(current != NULL) {
        if (current->key == key) {
            printf("Key already exists.\n");
            return EXIT_FAILURE;
        }
        current = (Node*)current->next;
    }

    // We tried using static allocation, but there was a bug when removing an element followed by inserting another one
    // That bug aside, the program ran smoothly for every test performed even with static allocation
    // Node* newNode = &dll->elements[dll->num_elements];  
    
    // Allocates memory for the new node and fills its data, fixing the bug mentioned above
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    for (int i = 0; i < MAX_DATA_SIZE; i++) {
        newNode->data[i] = data[i];
    }

    newNode->next = NULL;
    newNode->prev = NULL;
    
    // If list is empty the node is both the head and tail 
    if (MyDLLisEmpty(dll)) {   
        dll->head = newNode;
        dll->tail = newNode;  
    } else {
        // Otherwise, the new node is added to the end of the list
        dll->tail->next = (struct Node*)newNode;  
        newNode->prev = (struct Node*)dll->tail;  
        dll->tail = (Node*)newNode;        
    }

    dll->num_elements++; 
    return EXIT_SUCCESS;
}

int MyDLLRemove(DLL *dll, uint16_t key) 
{
    Node* current = dll->head;
    while (current != NULL) {
        if (current->key == key) {
            // If node to be removed is the head
            if (current == dll->head) {
                dll->head = (Node*)current->next;
                if (!MyDLLisEmpty(dll)) {
                    dll->head->prev = NULL; // If the list isn't empty, set the new head's prev pointer to NULL
                }
            // If node to be removed is the tail
            } else if (current == dll->tail) { 
                dll->tail = (Node*)current->prev;
                if (dll->tail != NULL) {
                    dll->tail->next = NULL; // Set the new tail's next pointer to NULL
                }
            } else {
                // Update the next and prev pointers
                ((Node *)current->prev)->next = current->next;
                ((Node *)current->next)->prev = current->prev;
            }
            dll->num_elements--;
            printf("Element with key number %d successfully removed.\n", key);
            return EXIT_SUCCESS;
        }
        current = (Node*)current->next;
    }
    printf("Element with key number %d not found.\n", key);
    return EXIT_FAILURE;
}

uint8_t* MyDLLFind(DLL *dll, uint16_t key) 
{
    Node* current = dll->head;
    while (current != NULL) {
        if (current->key == key) {
            printf("Key: %d, Data: %s\n", current->key, current->data);
            return current->data;
        }
        current = (Node*)current->next;
    }
    printf("Key not found.\n");
    return NULL;
}

uint8_t* MyDLLFindNext(DLL *dll, uint16_t key) 
{ 
    Node* current = dll->head;

    printf("Current user:\n");
        if (MyDLLFind(dll,key) == NULL){
            return NULL;
    }

    while (current != NULL) {
        if (current->key == key && current->next != NULL) {
            current = (Node*)current->next;
            printf("Next user:\n");
            printf("Key: %d, Data: %s\n", current->key, current->data);
            return current->data;
        }
        current = (Node*)current->next;
    }
    printf("There is no data after this one.\n");
    return NULL;
}

uint8_t* MyDLLFindPrev(DLL *dll, uint16_t key) 
{ 
    Node* current = dll->head;

    printf("Current user:\n");
        if (MyDLLFind(dll,key) == NULL){
            return NULL;
    }

    while (current != NULL) {
        if (current->key == key && current->prev != NULL) {
            current = (Node*)current->prev;
            printf("Previous user:\n");
            printf("Key: %d, Data: %s\n", current->key, current->data);
            return current->data;
        }
        current = (Node*)current->next;
    }
    printf("There is no data before this one.\n");
    return NULL;
}

uint8_t* MyDLLShowElements(DLL *dll) 
{
    int n = 1;

    if (MyDLLisEmpty(dll)) {
        printf("The list is empty.\n");
        return NULL;
    }

    Node* current = dll->head;
    printf("All data in the list: \n");
    while(current != NULL) {
        printf("User #%d - Key: %d\t Data: %s\n", n++, current->key, current->data);
        current = (Node*)current->next;
    }
}

void MyDLLRandomFill(DLL *dll) 
{
    srand(time(NULL)); // Seed

    if (dll->num_elements >= MAX_ELEMENTS) {
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
            break;
        }
    }
    printf("The list has been randomly filled.\n");
}

void MyDLLAscendingOrder(DLL *dll) {

    if (MyDLLisEmpty(dll)) {
        printf("The list is empty.\n");
        return;
    }

    int swapped;
    Node* current;
    Node* last = NULL;

    // Bubble Sort algorithm using some AI (swapped lines)
    do {
        swapped = 0;
        current = dll->head;

        while ((Node*)current->next != last) {
            Node* nextNode = (Node*)current->next;
            if (current->key > nextNode->key) {
                uint16_t temp_key = current->key;
                current->key = nextNode->key;
                nextNode->key = temp_key;

                uint8_t temp_data[MAX_DATA_SIZE];
                for (int i = 0; i < MAX_DATA_SIZE; i++) {
                    temp_data[i] = current->data[i];
                    current->data[i] = nextNode->data[i];
                    nextNode->data[i] = temp_data[i];
                }

                swapped = 1;
            }
            current = (Node*)current->next;
        }
        last = current;
    } while (swapped);

    printf("The list has been sorted.\n");
}

void MyDLLClear(DLL *dll) 
{
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
