/***
* Catherine Bronte
* cebronte 1969208
* 2024 Fall CSE101 PA5
* List.cpp
*  this is hwere the List classes and functions get filled out
***/

#include<iostream>
#include<string>
#include<stdexcept>
#include<utility>
#include"List.h"


// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x){
   data = x;
   next = nullptr;
   prev = nullptr;
}


//////////////////////////////////// Class Constructors & Destructors //////////////////////////////////////////////////////////////

// Creates a new List in the empty state.
List::List(){
   frontDummy = new Node(0); // might have issues here, if so just set everything to nullptr again
   backDummy = new Node(0);
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy; // the other feilds are still blank here cause they are sentinals
   num_elements = 0;
   pos_cursor = 0;
}

// Copy Constructor
List::List(const List& L) {
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    num_elements = 0;
    pos_cursor = 0;

    // Copy elements from L to this list in the correct order
    Node* N = L.frontDummy->next;
    while (N != L.backDummy) {
        insertAfter(N->data);
        N = N->next;
    }

    // Reset cursor position to the start
    moveFront();
}


// Destructor
List::~List() {
    Node* current = frontDummy;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}



//////////////////////////////////////////////// Access functions /////////////////////////////////////////////////////////////

// getFront()
// Returns the value at the front of List.
// Pre: !isEmpty()
ListElement List::front() const {
    if (length() == 0) {
        throw std::length_error("List: front(): empty List");
    }
    return frontDummy->next->data;  // Accessing the first real node
}

ListElement List::back() const {
    if (length() == 0) {
        throw std::length_error("List: back(): empty List");
    }
    return backDummy->prev->data;  // Accessing the last real node
}


int List::position() const{ // removed an error check here, was cheching if the len was zero
   return(pos_cursor);
}

ListElement List::peekNext() const{ // needs more work
   if( !(position()<length())){
      throw std::length_error("List: peekNext(): position exceeds length of list");
   }
   
   return(afterCursor->data);
}

ListElement List::peekPrev() const{ // needs more work
   if( !(position()> 0)){
      throw std::length_error("List: peekNext(): position exceeds length of list");
   }
   
   return(beforeCursor->data);
}

// getLength()
// Returns the length of List.
int List::length() const{
   return(num_elements);
}


///////////////////////////////////////// Manipulation procedures /////////////////////////////////////////////////

void List::clear() {
    // Start from the first real node (after frontDummy)
    Node* current = frontDummy->next;

    // Traverse the list and delete each node
    while (current != backDummy) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }

    // Reset the sentinels to be in an empty list state
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;

    // Reset cursor and properties
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}



void List::moveFront() { // cant be a constant cause the whole point of this function is to change its self
   pos_cursor = 0;
   beforeCursor = frontDummy;
   afterCursor = frontDummy->next;
}

void List::moveBack() { // cant be a constant cause the whole point of this function is to change its self
   pos_cursor = length();
   afterCursor = backDummy;
   beforeCursor = backDummy->prev;
}

ListElement List::moveNext() {
    if (afterCursor == backDummy) {
        throw std::range_error("List: moveNext(): already at the end of the list");
    }
    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;
    pos_cursor++;
    return beforeCursor->data;
}

ListElement List::movePrev() {
    if (beforeCursor == frontDummy) {
        throw std::range_error("List: movePrev(): already at the start of the list");
    }
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;
    pos_cursor--;
    return afterCursor->data;
}


void List::insertAfter(ListElement x) { // cant be a constant cause the whole point of this function is to change its self
   Node* S = new Node(x);
   S->prev = beforeCursor;
   S->next = beforeCursor->next;
   beforeCursor->next = S;
   S->next->prev = S;
   afterCursor = S;
   num_elements += 1;

}

void List::insertBefore(ListElement x)
{
    Node *N = new Node(x);
    N->prev = afterCursor->prev;
    N->next = afterCursor;
    afterCursor->prev->next = N;
    afterCursor->prev = N;
    beforeCursor = N;
    num_elements++;
    pos_cursor++;
}

void List::setBefore(ListElement x) { 
   if(!(position()<length())){
      throw std::length_error("List: setBefore(): position is too far");
   }
   beforeCursor->data = x;
}

void List::setAfter(ListElement x) { 
   if( !(position()>0)){
      throw std::length_error("List: setAfter(): position is already at 0");
   }
   afterCursor->data = x;
}

void List::eraseAfter() {
    if (afterCursor == backDummy) {
        throw std::length_error("List: eraseAfter(): no element to erase after");
    }
    Node* S = afterCursor;
    afterCursor = afterCursor->next;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;

    delete S;  // Delete the node that was after the cursor
    num_elements--;
}

void List::eraseBefore() {
    if (beforeCursor == frontDummy) {
        throw std::length_error("List: eraseBefore(): no element to erase before");
    }
    Node* S = beforeCursor;
    beforeCursor = beforeCursor->prev;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;

    delete S;  // Delete the node that was before the cursor
    num_elements--;
    pos_cursor--;
}



/////////////////////////////// Other Functions / the messy ones ///////////////////////////////////////////////////////////////////

int List::findNext(ListElement x) {
   while (position() < length()) {
      if (peekNext() == x) {
         moveNext();
         return position();
      }
      moveNext();
   }
   pos_cursor = length();
   return -1;
}

int List::findPrev(ListElement x) {
   while (position() > 0) {
      if (peekPrev() == x) {
         movePrev();
         return position();
      }
      movePrev();
   }
   pos_cursor = 0;
   return -1;
}

void List::cleanup() {
    if (length() == 0) {
        return;
    }

    Node* outer = frontDummy->next;
    while (outer != backDummy) {
        ListElement valueToCheck = outer->data;
        Node* inner = outer->next;

        while (inner != backDummy) {
            Node* nextNode = inner->next;

            if (inner->data == valueToCheck) {
                if (inner == beforeCursor) {
                    beforeCursor = beforeCursor->prev;
                }
                if (inner == afterCursor) {
                    afterCursor = afterCursor->next;
                }

                inner->prev->next = inner->next;
                inner->next->prev = inner->prev;
                delete inner;
                num_elements--;
            }

            inner = nextNode;
        }

        outer = outer->next;
    }

    // Reset position to 0
    moveFront();
}


// concat()
// Returns a new List consisting of the elements of this List, followed
// the elements of Q.
List List::concat(const List& L) const {
    List J;

    // Add elements from the current list
    Node* N = this->frontDummy->next;
    while (N != this->backDummy) {
        J.insertBefore(N->data);
        N = N->next;
    }

    // Add elements from list L
    Node* M = L.frontDummy->next;
    while (M != L.backDummy) {
        J.insertBefore(M->data);
        M = M->next;
    }

    // Reset position to 0 for the newly concatenated list
    J.moveFront();

    return J;
}



// to_string()
// Returns a string representation of List consisting of a space separated 
// list of data values.
std::string List::to_string() const{
   Node* N = nullptr;
   std::string s = "(";

   for(N = frontDummy->next; N!=backDummy->prev; N=N->next){
      s += std::to_string(N->data)+", ";
   }
   s += std::to_string(backDummy->prev->data)+"";
   s += ")";
   
   return s;
}

// equals()
// Returns true if and only if this is the same sequence as Q.
bool List::equals(const List& L) const {
    if (this->num_elements != L.num_elements) {
        return false;
    }

    Node* N = this->frontDummy->next;
    Node* M = L.frontDummy->next;

    while (N != this->backDummy) {
        if (N->data != M->data) {
            return false;
        }
        N = N->next;
        M = M->next;
    }

    return true;
}



// Overloaded Operators --------------------------------------------------------

// operator<<()
// Inserts string representation of Q, as defined by member function 
// to_string(), into stream.
std::ostream& operator<<( std::ostream& stream,  const List& Q ) {
   return stream << Q.to_string();
}

// operator==()
// Returns true if and only if List A equals List B, as defined by member
// member function equals().
bool operator==(const List& A, const List& B){
   return A.equals(B);
}

// operator=()
// Overwrites the state of this List with state of L, then returns a reference
// to this List.
List& List::operator=(const List& L) {
    // Check for self-assignment
    if (this == &L) {
        return *this; // Handle self-assignment
    }

    // Clear existing elements
    clear();

    // Copy elements from L to this list in the correct order
    Node* current = L.frontDummy->next;
    while (current != L.backDummy) {
        insertAfter(current->data);
        current = current->next;
    }

    // Set the cursor to match L's cursor position
    pos_cursor = L.pos_cursor;
    moveFront();
    for (int i = 0; i < pos_cursor; ++i) {
        moveNext();
    }

    return *this;
}

