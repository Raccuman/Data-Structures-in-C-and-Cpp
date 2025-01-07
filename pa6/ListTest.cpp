/***
* Catherine Bronte
* cebronte 1969208
* 2024 Fall CSE101 PA6
* ListTest.cpp
*  this is hwere the List classes and functions get tested
***/
#include <cstdlib>   // for rand() and srand()
#include <ctime>     // for time()
#include "List.h"    // assuming the List class is defined in List.h
#include <iostream>  // for cout, endl
#include <math.h>    // for log2()
#include<string>
#include<stdexcept>

using namespace std;

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
                merge.insertAfter(left.peekNext());
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

    }



int main(){

   List A;
   for (int i = 0; i <=10; i++) {
        A.insertAfter(i);
   }
   shuffle(A);

}

    