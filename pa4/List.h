/***
* Catherine Bronte
* cebronte 1969208
* 2024 Fall CSE101 PA4
* List.c
* list function definitions
***/
 
#ifndef QUEUE_H_INCLUDE_
#define QUEUE_H_INCLUDE_
#include<stdbool.h>
#include "stdio.h"


#define FORMAT "%d"  // format string for QueueElement

#ifdef index
#undef index
#endif



// Exported types -------------------------------------------------------------
typedef void* ListElement; // this was the first change
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------

// newQueue()
// Returns reference to new empty Queue object.
List newList();

// freeQueue()
// Frees all heap memory associated with Queue *pQ, and sets *pQ to NULL.
void freeList(List* pQ);


// Access functions -----------------------------------------------------------

// getLength()
// Returns the length of Q.
int length(List Q);

int index(List L);

// getFront()
// Returns the value at the front of Q.
// Pre: !isEmpty(Q)
ListElement front(List Q);

ListElement back(List Q);

ListElement get(List L);

// isEmpty()
// Returns true if Q is empty, otherwise returns false.
bool isEmpty(List Q);



// Manipulation procedures ----------------------------------------------------


// Dequeue()
// Deletes data at front of Q.
// Pre: !isEmpty(Q)


void* Dequeue(List Q);

void clear(List L);

void set(List L, ListElement x); // change to listElement

void moveFront(List L);

void moveBack(List L);

void movePrev(List L);

void moveNext(List L);

void prepend(List L, ListElement x);

void append(List L, ListElement x);

void insertBefore(List L, ListElement x);

void insertAfter(List L, ListElement x);

void deleteFront(List L);

void deleteBack(List L);

void delete(List L);


// Other Functions ------------------------------------------------------------

// printQueue()
// Prints a string representation of Q consisting of a space separated list
// of ints to stdout.
// void printList(FILE* out, List Q);


#endif


//////////////////////////////////end of queue stuff //////////////////////////////////////////////////p
