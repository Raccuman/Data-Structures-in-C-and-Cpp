/***
* Catherine Bronte
* cebronte 1969208
* 2024 Fall CSE101 PA8
* WordFrequency.cpp
*  this is the main program for this assignment
***/

#include "Dictionary.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;
const string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

int main(int argc, char *argv[]) {
    if (argc != 3)
    {
        cerr << "Ypu have the incorrect number of files, BAD! there should be 2, one in and one out" << endl;
        return EXIT_FAILURE;
    }

    ifstream in;
    ofstream out;
    string line = "";
    string key = "";

    in.open(argv[1]);
    if (in.is_open() == false) {
        cerr << "Unable to open your in file, BAD!" << endl; 
        return EXIT_FAILURE;
    }

    out.open(argv[2]);
    if (out.is_open() == false) {
        cerr << "Unable to open file outfile, BAD!" << endl; 
        return EXIT_FAILURE;
    }

    /////////////////////////////// time to begin ///////////////////////////////////////////

    size_t start;
    size_t end;
    size_t count;
    Dictionary A; 

    while (getline(in, line))
    { 
        // first word of line case
        count = line.length();

        end = min(line.find_first_of(delim, start), count);
        key = line.substr(start, end - start);         

        transform(key.begin(), key.end(), key.begin(), ::tolower); 

        while (key != "")
        {
            // the rest of the words on the line case
            if (A.contains(key) == false) {
                A.setValue(key,1);
            } else {
                A.getValue(key)++;
            }

            start = min(line.find_first_not_of(delim, end + 1), count); 
            end = min(line.find_first_of(delim, start), count);         
            key = line.substr(start, end - start);                      
            transform(key.begin(), key.end(), key.begin(), ::tolower);  
        }
    }

    out << A << endl;

    in.close();  
    out.close(); 
    return EXIT_SUCCESS;
}