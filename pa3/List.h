/***
* Catherine Bronte
* cebronte 1969208
* 2024 Fall CSE101 PA3
* List.c
* list function definitions
***/

#ifndef QUEUE_H_INCLUDE_
#define QUEUE_H_INCLUDE_
#include<stdbool.h>
#include "stdio.h"


#define FORMAT "%d"  // format string for QueueElement


// Exported types -------------------------------------------------------------
typedef int ListElement;
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

int get(List L);

// equals()
// Returns true if A is same int sequence as B, false otherwise.
bool equals(List A, List B);

// isEmpty()
// Returns true if Q is empty, otherwise returns false.
bool isEmpty(List Q);



// Manipulation procedures ----------------------------------------------------


// Dequeue()
// Deletes data at front of Q.
// Pre: !isEmpty(Q)


int Dequeue(List Q);

void Enqueue(List Q, ListElement data);

void clear(List L);

void set(List L, int x);

void moveFront(List L);

void moveBack(List L);

void movePrev(List L);

void moveNext(List L);

void prepend(List L, int x);

void append(List L, int x);

void insertBefore(List L, int x);

void insertAfter(List L, int x);

void deleteFront(List L);

void delete(List L);


// Other Functions ------------------------------------------------------------

// printQueue()
// Prints a string representation of Q consisting of a space separated list
// of ints to stdout.
void printList(FILE* out, List Q);

List copyList(List L);


#endif


//////////////////////////////////end of queue stuff //////////////////////////////////////////////////p