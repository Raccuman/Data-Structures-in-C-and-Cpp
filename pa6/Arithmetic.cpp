/***
* Catherine Bronte
* cebronte 1969208
* 2024 Fall CSE101 PA6
* Arithmetic.cpp
* Main file for the project, this is where the computation is called
***/
#include"BigInteger.h"
#include<string>
#include<fstream>
#include<stdexcept>
#include <iostream>

using namespace std;


int main(int argc, char* argv[]) {
    ifstream in;
    ofstream out;
    if (argc != 3) {
        std::cerr << "You do not have the incorrect number of inputs, BAD! Needs to be 2" << std::endl;
        return 1;
    }

    in.open(argv[1]);
    if( in.is_open() == false){
        cerr << "Cannot open the given in-file, BAD!" << endl;
        return 1;
    }

    out.open(argv[2]);
    if( in.is_open() == false){
        cerr << "Cannot open the given out-file, BAD!" << endl;
        return 1;
    }


    std::string line = "";
    std::getline(in, line);
    BigInteger A = BigInteger(line);
    std::getline(in, line); // the next line is blank, so it clears the line anyways
    std::getline(in, line);
    BigInteger B = BigInteger(line);

    // kind of nce to just have a file made of 3 lines

/////////////////////////// the operations ///////////////////////////////////////////////////////////////////////////////

    out << A << endl;
    out << endl;

    out << B << endl;
    out << endl;

    BigInteger C = A+B;
    out << C << endl;
    out << endl;

    C = A-B;
    out << C << endl;
    out << endl;

    C = A-A;
    out << C << endl;
    out << endl;

    BigInteger three = BigInteger("3");
    BigInteger two = BigInteger("2");
    C = (three*A)-(two*B);
    out << C << endl;
    out << endl;

    C = A*B;
    out << C << endl;
    out << endl;

    C = A*A;
    out << C << endl;
    out << endl;

    C = B*B;
    out << C << endl;
    out << endl;


    BigInteger nine = BigInteger("9");
    BigInteger sixteen = BigInteger("16");
    BigInteger J = (nine * (A * A * A * A)) + (sixteen * (B * B * B * B * B));
    out << J << endl;
    out << endl;

}
