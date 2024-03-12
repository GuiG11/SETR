/**
 * \defgroup dll Doubly Linked List (dll)
 *
 * \details 
 *   This module implements a Doubly Linked List (DLL) in C. The DLL is statically allocated,
 *   with the maximum number of elements and element size passed as arguments to the initialization function.
 *   Each element in the DLL consists of a key (uint_16t) that uniquely identifies the element,
 *   and an array of unsigned chars that contains the element's data.
 *   
 *   The following functions are provided by this module:
 *   - MyDLLInit(): Initializes the DLL data structure.
 *   - MyDLLInsert(): Inserts a new element into the DLL.
 *   - MyDLLRemove(): Removes an element from the DLL identified by its key.
 *   - MyDLLFind(): Finds and returns the data associated with an element in the DLL given its key.
 *   - MyDLLFindNext(): Finds and returns the data associated with the element after the specified key in the DLL.
 *   - MyDLLFindPrev(): Finds and returns the data associated with the element before the specified key in the DLL.
 *   - MyDLLShowElements(): Displays all elements in the DLL.
 *   - MyDLLRandomFill(): Randomly fills the DLL with elements until it is full.
 *   - MyDLLClear(): Clears all elements from the DLL.
 *   
 *   The DLL supports the following operations:
 *   - Insertion of new elements.
 *   - Removal of elements by their keys.
 *   - Searching for elements by their keys.
 *   - Sorting the elements of the DLL in ascending order based on their keys.
 *   - Randomly filling the DLL with elements.
 *   - Clearing all elements from the DLL.
 *   - Displaying all elements in the DLL.
 *
 *  \authors Guilherme Guarino 104154, Simão Pinto 102776 - 03/2024
 */


#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/** @{ */

// ================================================================================== //

/**
 * \brief Defines the maximum size of the data array in each node.
 */
#define MAX_DATA_SIZE 50

/**
 * \brief Defines the maximum number of elements the list can hold.
 */
#define MAX_ELEMENTS 4


/**
 * \brief DLL node structure
 * \details Defines a node in the doubly linked list.
 */
typedef struct 
{
    uint16_t key; /**< Identification of the node */
    uint8_t data[MAX_DATA_SIZE]; /**< Data associated with the node */
    struct Node *next; /**< Pointer to the next node */
    struct Node *prev; /**< Pointer to the previous node */

}Node;


/**
 * \brief DLL structure
 * \details Defines the doubly linked list.
 */
typedef struct 
{
    Node elements[MAX_ELEMENTS]; /**< Array of nodes */
    Node *head; /**< Pointer to the head of the list */
    Node *tail; /**< Pointer to the tail of the list */
    int num_elements; /**< Number of elements in the list */
    
}DLL;

/**
 * \brief Initializes the DLL data structure.
 * \details This function initializes the DLL data structure, setting the head, tail, and number of elements to NULL or 0.
 * 
 * \param dll Pointer to the DLL structure.
 */
void MyDLLInit(DLL *dll);


/**
 * \brief Checks if the DLL is empty.
 * \details This function checks if the DLL is empty by verifying if the head pointer is NULL.
 * 
 * \param dll Pointer to the DLL structure.
 * \return \c true if the DLL is empty, \c false otherwise.
 */
bool MyDLLisEmpty(DLL *dll);


/**
 * \brief Inserts a new node into the DLL.
 * \details This function inserts a new node with the specified key and data into the DLL.
 *          If the list is full or if a node with the same key already exists, insertion fails.
 * 
 * \param dll Pointer to the DLL structure.
 * \param key ID of the node in the DLL.
 * \param data Pointer to the data array.
 * \return \c EXIT_SUCCESS if insertion was successful, \c EXIT_FAILURE otherwise.
 */
int MyDLLInsert(DLL *dll, uint16_t key, uint8_t data[]);


/**
 * \brief Removes a node from the DLL.
 * \details This function removes the node with the specified key from the DLL.
 *          If the node is found, it is removed from the list. If the node does not exist, removal fails.
 * 
 * \param dll Pointer to the DLL structure.
 * \param key ID of the node to be removed.
 * \return \c EXIT_SUCCESS if node removal was successful, \c EXIT_FAILURE otherwise.
 */
int MyDLLRemove(DLL *dll, uint16_t key);


/**
 * \brief Finds a node in the DLL by key.
 * \details This function searches the DLL for a node with the given key.
 *          If the node is found, its data is printed and a pointer to the data is returned.
 *          If the node is not found, NULL is returned.
 * 
 * \param dll Pointer to the DLL structure.
 * \param key ID of the node to be found.
 * \return Pointer to the data associated with the node if found, NULL otherwise.
 */
uint8_t* MyDLLFind(DLL *dll, uint16_t key);


/**
 * \brief Finds the next node in the DLL after the node with the specified key.
 * \details This function searches the DLL for the node with the given key.
 *          If the node is found and has a next node, its data is printed and a pointer to the data of the next node is returned.
 *          If the node is not found or if it is the last node, NULL is returned.
 * 
 * \param dll Pointer to the DLL structure.
 * \param key ID of the node whose next node is to be found.
 * \return Pointer to the data associated with the next node if found, NULL otherwise.
 */
uint8_t* MyDLLFindNext(DLL *dll, uint16_t key);


/**
 * \brief Finds the previous node in the DLL before the node with the specified key.
 * \details This function searches the DLL for the node with the given key.
 *          If the node is found and has a previous node, its data is printed and a pointer to the data of the previous node is returned.
 *          If the node is not found or if it is the first node, NULL is returned.
 * 
 * \param dll Pointer to the DLL structure.
 * \param key ID of the node whose previous node is to be found.
 * \return Pointer to the data associated with the previous node if found, NULL otherwise.
 */
uint8_t* MyDLLFindPrev(DLL *dll, uint16_t key);


/**
 * \brief Randomly fills the DLL with nodes.
 * \details This function randomly generates keys and data arrays for nodes and inserts them into the DLL until it is full.
 *          The keys are generated randomly, and the data arrays contain random alphanumeric characters.
 *          If the DLL is already full, no new nodes are inserted.
 * 
 * \param dll Pointer to the DLL structure.
 */
void MyDLLRandomFill(DLL *dll);


/**
 * \brief Sorts the elements of the DLL in ascending order based on their keys.
 * \details This function sorts the elements of the DLL in ascending order based on their keys
 *          using the Bubble Sort algorithm. If the DLL is empty, the function returns without
 *          performing any operation.
 * 
 * \param dll Pointer to the DLL structure.
 * 
 * \note The Bubble Sort algorithm has a time complexity of O(n^2). 
 *       Consider using more efficient sorting algorithms for larger lists.
 */
void MyDLLAscendingOrder(DLL *dll);


/**
 * \brief Displays all nodes in the DLL.
 * \details This function prints all nodes in the DLL along with their keys and data.
 * 
 * \param dll Pointer to the DLL structure.
 * \return Pointer to the data associated with the first node in the list.
 */
uint8_t* MyDLLShowElements(DLL *dll);


/**
 * \brief Clears all nodes from the DLL.
 * \details This function removes all nodes from the DLL, effectively clearing the entire list.
 * 
 * \param dll Pointer to the DLL structure.
 */
void MyDLLClear(DLL *dll);