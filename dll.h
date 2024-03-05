#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


typedef struct 
{
    uint16_t nmec;  
    char firstName[20];
    char lastName[20];
    uint16_t age;
    float grade;
    struct Student *next;
    struct Student *previous;

}Student;

typedef struct 
{
    Student *head;
    Student *tail;
    uint16_tsize;

}DoublyLinkedList;



void MyDLLInit();

int MyDLLInsert(uint16_t nmec, char *firsName, char *lastName, uint16_t age, float grade);

int MyDLLRemove(uint16_t nmec);

void MyDLLFind(uint16_t nemc);

void MyDLLFindNext();

void MyDLLFindPrevious();
