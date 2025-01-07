/***
* Catherine Bronte
* cebronte 1969208
* 2024 Fall CSE101 PA7
* Order.cpp
*  this is the main program for this assignment
***/

#include<iostream>
#include<fstream>
#include<string>
#include"Dictionary.h"

using namespace std;

int main(int argc, char * argv[]) {
    ifstream in_file;
    ofstream out_file;
    // check command line for correct number of arguments
    if( argc != 3 ){
        cerr << "You have the wrong number of file inputs, BAD!" << endl;
        return(EXIT_FAILURE);
    }

    // open files for reading and writing 

    // in file case
    in_file.open(argv[1]);
    if( in_file.is_open() == false){
        cerr << "Could not open your FIRST file, womp womp" << endl;
        return(EXIT_FAILURE);
    }

    // out file case
    out_file.open(argv[2]);
    if( out_file.is_open() == false ){
        cerr << "Could not open your SECOND file, womp womp" << endl;
        return(EXIT_FAILURE);
    }
    
    Dictionary A;
    std::string key;
    int val = 1;

    // inserting into the dictionasy sequentially
    while (getline(in_file, key)) {
        A.setValue(key, val);
        val += 1;
    }

    out_file << A << endl;
    out_file << A.pre_string() << endl;
    
    in_file.close();
    out_file.close();

}