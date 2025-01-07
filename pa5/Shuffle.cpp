/***
* Catherine Bronte
* cebronte 1969208
* 2024 Fall CSE101 PA5
* Shuffle.cpp
*  this is where the main program happens, things get shuffled around
***/


#include <cstdlib>   // for rand() and srand()
#include <ctime>     // for time()
#include "List.h"    // assuming the List class is defined in List.h
#include <iostream>  // for cout, endl
#include <math.h>    // for log2()
#include<string>
#include<stdexcept>

int shuffle(List& deck) {
    int bridge = 0;
    List left;
    List right;
    List merge;
    int flag = 0;
    int counter = 0;
        
    while (flag == 0) {
        for (int i = 0; i < deck.length()/2; i++) { // might work for both ways actually? only if it floor divides though
        left.insertAfter(i);
        bridge = i;
        }
        for (int j = bridge; j < deck.length(); j++) {
            right.insertAfter(j);
        }

        left.moveFront();
        right.moveFront();
        for (int c = 0; c < left.length(); c++) { // merging them together, right then left
            merge.insertAfter(right.peekNext());
            merge.insertAfter(left.peekNext()); // might be causing problem
            left.moveNext();
            right.moveNext();
        }

        if (left.length() < right.length()) { // if it wasnt even then the right deck should have an extra card that needs to be added
            merge.insertAfter(right.peekNext());
        }

        merge.moveFront();
        flag = 1;
        for (int g = 0; g < merge.length(); g++) {
            if (merge.peekPrev() > merge.peekNext()) {
                flag = 0;
            }
            merge.moveNext();
        }
        counter += 1;
    }
    return counter;
    // stuff
}


// Main function that tests the shuffle function for various deck sizes
int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "You do not have the correct number of inputs, BAD! Should just be one number" << std::endl;
        return 1;
    }

    int size = std::stoi(argv[1]); // getting the one command line input

    std::cout << "deck size       shuffle count" << std::endl; // printing to the screen the top bit
    std::cout << "------------------------------" << std::endl;
    for (int i = 1; i <= size; i++) { // checking all of the deck sizes
        List deck;
        for (int j = 0; j < i; j++) {
            deck.insertBefore(j); // making a deck of the appropriate size
        }
        int shuf = shuffle(deck);
        if (shuf < 10){
            if (i < 10){
                std::cout << " " << i << "               " << shuf << std::endl; //for spaces purposes
            }
            else{
                std::cout << " " << i << "              " << shuf << std::endl;
            }
        }
        else if (shuf < 100) {
            std::cout << " " << i << "              " << shuf << std::endl;
        }
        else {
            std::cout << " " << i << "             " << shuf << std::endl;
        }


    }

    return 0;
}
