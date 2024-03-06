#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


#define MAX_DATA_SIZE 100
#define MAX_ELEMENTS 3

typedef struct 
{
    uint16_t key;  
    uint8_t data[MAX_DATA_SIZE];
    struct Node *next;
    struct Node *prev;

}Node;


typedef struct 
{
    Node elements[MAX_ELEMENTS];
    Node *head;
    Node *tail;
    int num_elements;
    
}DLL;


void MyDLLInit(DLL *dll);

int MyDLLInsert(DLL *dll, uint16_t nmec, uint8_t name[]);

int MyDLLRemove(DLL *dll, uint16_t nmec);

void MyDLLFind(DLL *dll, uint16_t nemc);

uint8_t* MyDLLFindNext(DLL *dll, uint16_t key);

uint8_t* MyDLLFindPrev(DLL *dll, uint16_t key);

uint8_t* MyDLLShowElements(DLL *dll);