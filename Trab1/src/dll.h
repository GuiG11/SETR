#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


#define MAX_DATA_SIZE 50
#define MAX_ELEMENTS 7

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

int MyDLLInsert(DLL *dll, uint16_t key, uint8_t data[]);

int MyDLLRemove(DLL *dll, uint16_t key);

uint8_t* MyDLLFind(DLL *dll, uint16_t key);

uint8_t* MyDLLFindNext(DLL *dll, uint16_t key);

uint8_t* MyDLLFindPrev(DLL *dll, uint16_t key);

void MyDLLRandomFill(DLL *dll);

uint8_t* MyDLLShowElements(DLL *dll);

void MyDLLClear(DLL *dll);