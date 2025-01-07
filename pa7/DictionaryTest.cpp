/***
* Catherine Bronte
* cebronte 1969208
* 2024 Fall CSE101 PA7
* DictionaryTest.cpp
*  this is where I set up my functions to be tested with GDB, there might not be much here
***/

#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){

    Dictionary A = Dictionary();
    A.setValue("a", 1);
    A.setValue("b", 5);
    A.setValue("c", 16);
    A.setValue("d", 176);
    A.setValue("e", 3214);
    A.begin();
    A.currentKey();
    A.next();
    A.currentKey();
    A.next();
    A.currentKey();


    if (A.currentKey() != "c" || A.currentVal() != 16)
      return 1;
    A.next();
    A.next();
    A.next();
    if (A.hasCurrent())
      return 2;

    return 0;

   cout << endl;  

   return( EXIT_SUCCESS );
}
