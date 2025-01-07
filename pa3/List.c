/***
* Catherine Bronte
* cebronte 1969208
* 2024 Fall CSE101 PA3
* List.c
* this is where all of the list functions are written out
***/
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"
#include "stdio.h"


// structs --------------------------------------------------------------------

//////////////////////////////////// To Do for Catie Bronte //////////////////////////////

 // figure out how arrays go into the data section of the node objects. Char arrays are supposed to go there, each item
 // in a node object data section should be a line of the file. # of lines in a file = number of node objects. The
 // cursor is how you sort. you compare different lines at different cursor positions  and remember the cursor number

 // das it :3


// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
   ListElement data;
   Node next;
   // we need a node for previous because Node types point to node objects, and we need the location
   // of the previous node cause doubly linked list
   Node previous;
} NodeObj;



// private QueueObj type
typedef struct ListObj{
   Node front;
   Node cursor;
   Node back;
   int index;
   int length;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(ListElement data){
   Node N = malloc(sizeof(NodeObj));
   assert( N!=NULL );
   N->data = data;
   N->next = NULL;
   // not sure what to set it to, so I just made it NULL
   N->previous = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newQueue()
// Returns reference to new empty List object.
List newList(){
   List Q;
   Q = malloc(sizeof(ListObj));
   assert( Q!=NULL );
   Q->front = Q->back = NULL;
   Q->cursor = NULL;
   Q->length = 0;
   Q->index = -1;
   return(Q);
}

// freeQueue()
// Frees all heap memory associated with Queue *pQ, and sets *pQ to NULL.
void freeList(List* pQ){
   if(pQ!=NULL && *pQ!=NULL) {
      while( !isEmpty(*pQ) ) {
         Dequeue(*pQ);
      }
      free(*pQ);
      *pQ = NULL;
   }
}


// Access functions -----------------------------------------------------------

// getLength()
// Returns the length of Q.
int length(List Q){
   if( Q==NULL ){
      printf("List Error: calling Length() on NULL Queue reference\n");
      exit(EXIT_FAILURE);
   }
   return(Q->length);
}


int index(List L) {
   if( L == NULL ){
      printf("List Error: calling index() on NULL Queue reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->index);
}

// getFront()
// Returns the value at the front of Q.
// Pre: !isEmpty(Q)
ListElement front(List Q){
   if( Q==NULL ){
      printf("List Error: calling Front() on NULL Queue reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(Q) ){
      printf("List Error: calling Front() on an empty Queue\n");
      exit(EXIT_FAILURE);
   }
   return(Q->front->data);
}


ListElement back(List Q){
   if( Q==NULL ){
      printf("List Error: calling back() on NULL Queue reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(Q) ){
      printf("List Error: calling back() on an empty Queue\n");
      exit(EXIT_FAILURE);
   }
   return(Q->back->data);
}


int get(List L) {
   if( isEmpty(L) ){
      printf("List Error: calling get() on an empty Queue\n");
      exit(EXIT_FAILURE);
   }
   if (L->index == -1) {
      printf("tried getting al element at cursor position -1");
      exit(EXIT_FAILURE);
   }

   return L->cursor->data;
}


// equals()
// Returns true if A is same int sequence as B, false otherwise.
bool equals(List A, List B){
   if( A==NULL || B==NULL ){
      printf("List Error: calling equals() on NULL Queue reference\n");
      exit(EXIT_FAILURE);
   }

   bool eq;
   Node N, M;

   eq = ( A->length == B->length );
   N = A->front;
   M = B->front;
   while( eq && N!=NULL){
      eq = ( N->data==M->data );
      N = N->next;
      M = M->next;
   }
   return eq;
}


// isEmpty()
// Returns true if Q is empty, otherwise returns false.
bool isEmpty(List Q){
   if( Q==NULL ) {
      printf("List Error: calling isEmpty() on NULL Queue reference\n");
      exit(EXIT_FAILURE);
   }
   if (Q->length == 0) {
      return true;
   }
   return false;
}


// Manipulation procedures ---------------------------------------------------- Might Have Issues Here ----

// Dequeue()
// Deletes data at front of Q.
// Pre: !isEmpty(Q)
int Dequeue(List Q){
   Node N = NULL;
   int returner = 0;
   returner = Q->front->data;
   if( Q==NULL ){
      printf("List Error: calling Dequeue() on NULL Queue reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(Q) ){
      printf("list Error: calling Dequeue on an empty Queue\n");
      exit(EXIT_FAILURE);
   }

   N = Q->front;
   if( length(Q)>1 ) {
      Q->front = Q->front->next;
   }else{
      Q->front = Q->back = NULL;
   }
   Q->length--;
   freeNode(&N);
   return returner;

}

void Enqueue(List Q, ListElement data)
{
   Node N = newNode(data);

   if( Q==NULL ){
      printf("Queue Error: calling Enqueue() on NULL Queue reference\n");
      exit(EXIT_FAILURE);
   }

   if( isEmpty(Q) ) {
      Q->front = Q->back = N;
   }else{
      Q->back->next = N;
      Q->back = N;
   }
   Q->length++;
}


void clear(List L) {
   int counter = length(L);
   for (int j = 0; j < counter; j++) {
      Dequeue(L);
   }
   L->length = 0;
   L->index = -1;
   L->cursor = NULL;
   L->front = NULL;
   L->back = NULL;

}


void set(List L, int x) {
   if( isEmpty(L) ){
      printf("List Error: calling get() on an empty Queue\n");
      exit(EXIT_FAILURE);
   }
   if (L->index == -1) {
      printf("tried getting al element at cursor position -1");
      exit(EXIT_FAILURE);
   }

   L->cursor->data = x;
}

// might have issues with the !
void moveFront(List L) {
   if (!isEmpty(L)) {
      L->index = 0;
      L->cursor = L->front;
   }
}


void moveBack(List L) {
   if (!isEmpty(L)) {
      L->index = length(L) -1;
      L->cursor = L->back;
   }
}


void movePrev(List L) {
   if (L->index != -1) {
      if (L->index == 0) {
         L->index = -1;
         L->cursor = NULL;
      } else {
         L->index = (L->index) - 1;
         L->cursor = L->cursor->previous;
      }
   }
}


void moveNext(List L) {
   if (L->index != -1) {
      if (L->index < (length(L)-1)) {
            L->index = L->index + 1;
            L->cursor = L->cursor->next;
      }
      else {
         L->index = -1;
         L->cursor = NULL;
      }

   }
}


void prepend(List L, int x) {
      Node N = newNode(x);

      if( L==NULL ){
         printf("Queue Error: calling prepend() on NULL Queue reference\n");
         exit(EXIT_FAILURE);
      }

      if( isEmpty(L) ) {
         L->front = L->back = N;
      } else {
         N->next = L->front;
         L->front->previous = N;
         L->front = N;
      }
      L->length += 1;
      if (L->index != -1) {
         L->index += 1;
      }

}


void append(List L, int x) {
   Node N = newNode(x);
   if( L==NULL ){
      printf("Queue Error: calling Enqueue() on NULL Queue reference\n");
      exit(EXIT_FAILURE);
   }

   if( isEmpty(L) ) {
      L->front = L->back = N;
   }else{
      N->previous = L->back;
      L->back->next = N;
      L->back = N;
   }
   L->length += 1;
}


/// ///////////////////////////////////////////////stopped working here, insertBefore might not work ///////////////////////
void insertBefore(List L, int x) {
   if( isEmpty(L) ){
      printf("List Error: tried insert before on an empty queue\n");
      exit(EXIT_FAILURE);
   }
   if (L->index == -1) {
      printf("tried getting al element at cursor position -1");
      exit(EXIT_FAILURE);
   }

   Node newbie = newNode(x);

   // inserting in the first position :3
   if (L->cursor == L->front) {
      newbie->next = L->front;
      L->front->previous = newbie;
      L->front = newbie;
   }
   else {
      Node prev = L->cursor->previous;
      newbie->next = L->cursor;
      newbie->previous = prev;
      prev->next = newbie;
      L->cursor->previous = newbie;
   }

   L->length++;
   L->index++;
}


void insertAfter(List L, int x) {
   if( isEmpty(L) ){
      printf("List Error: calling get() on an empty Queue\n");
      exit(EXIT_FAILURE);
   }
   if (L->index == -1) {
      printf("tried getting al element at cursor position -1");
      exit(EXIT_FAILURE);
   }

   // our new little guy
   Node newbie = newNode(x);

   // at the back
   if (L->cursor == L->back) {
      L->back->next = newbie;
      newbie->previous = L->back;
      L->back = newbie;
      newbie->next = NULL;
   }
   else {
      Node nextNode = L->cursor->next;
      newbie->next = nextNode;
      newbie->previous = L->cursor;
      L->cursor->next = newbie;
      if (nextNode != NULL) {
         nextNode->previous = newbie;
      }
   }

   L->length++;
}


// why you so friggin compliicated
void delete(List L) {
   Node exterminate = L->cursor;

   if (L->cursor == L->front) { // if we are at the start
      L->front = L->front->next;
      if (L->front != NULL) {
         L->front->previous = NULL;
      } else {
         L->back = NULL;
      }
   } else if (L->cursor == L->back) { //if we areat the end
      L->back = L->back->previous;
      if (L->back != NULL) {
         L->back->next = NULL;
      }
   } else {
      Node prev = exterminate->previous;
      Node next = exterminate->next;
      prev->next = next;
      next->previous = prev;
   }

   // free node needs a double pointer??
   freeNode(&exterminate);
   L->index = -1;
   L->cursor = NULL;
   L->length -= 1;
}

// might not work in the case that the pre-existing cursor is already at the front
void deleteFront(List L) {
   if (!isEmpty(L)) {
      Node temp_curs = L->cursor;
      int temp_index = L->index;
      if (L->index == 0) {
        moveFront(L);
         delete(L);
         L->cursor = NULL;
         L->index = -1;
      }
      else {
         moveFront(L);
         delete(L);
         L->cursor = temp_curs;
         L->index = temp_index;
      }

   }
}

// might not work in the case that the pre-existing cursor is already at the back
void deleteBack(List L) {
   if (!isEmpty(L)) {
      Node temp_curs = L->cursor;
      int temp_index = L->index;
      if (L->index == (length(L)-1)) {
         moveBack(L);
         delete(L);
         L->cursor = NULL;
         L->index = -1;
      }
      else {
         moveBack(L);
         delete(L);
         L->cursor = temp_curs;
         L->index = temp_index;
      }
   }

}



// Other Functions ------------------------------------------------------------

// printQueue()
// Prints a string representation of Q consisting of a space separated list
// of ints to stdout.
void printList(FILE* out, List Q){
   if( Q==NULL ){
      printf("List Error: calling printQueue() on NULL Queue reference\n");
      exit(EXIT_FAILURE);
   }
   int temp_index = Q->index;
   Node temp_curs = Q->cursor;

   moveFront(Q);
   for (int q = 0; q < length(Q); q++) {
      fprintf(out, "%d ", get(Q));
      moveNext(Q);
   }
   fprintf(out, "\n");
   Q->cursor = temp_curs;
   Q->index = temp_index;
}



List copyList(List L) {
   List new_list = newList();
   if (L == NULL) {
      printf("List Error: calling copyList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   // complex loop, looks like ListClient . . .
   for (moveFront(L); index(L) >= 0; moveNext(L)) {
      append(new_list, get(L));
   }

   return new_list;
}



//////////////////////// end of queue code ////////////////////////////