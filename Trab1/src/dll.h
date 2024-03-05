#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


#define MAX_DATA_SIZE 100
#define MAX_ELEMENTS 4

typedef struct 
{
    uint16_t nmec;  
    char data[MAX_DATA_SIZE];
    struct Student *next;
    struct Student *previous;

}Student;


typedef struct 
{
    Student *head;
    Student *tail;
    int num_elements;
    int max_elements;
    
}DoublyLinkedList;


void MyDLLInit(DoublyLinkedList *dll);

int MyDLLInsert(DoublyLinkedList *dll, uint16_t nmec, char *data);

int MyDLLRemove(DoublyLinkedList *dll, uint16_t nmec);

void MyDLLFind(DoublyLinkedList *dll, uint16_t nemc);

void MyDLLFindNext(DoublyLinkedList *dll);

void MyDLLFindPrevious(DoublyLinkedList *dll);
