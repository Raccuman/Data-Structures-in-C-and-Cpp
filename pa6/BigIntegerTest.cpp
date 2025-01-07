//-----------------------------------------------------------------------------
//  BigIntegerClient.cpp 
//  A test client for the BigInteger ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){

   string s1 = "91287346670000043892345634563400005619187236478";
   //string s2 = "-330293847502398475";
   string s3 = "9876545439000000345634560000000002000034565430000000006543654365346534";
   //string s4 = "9876545439000000000000000100000000000006543654365346534";
   string s5 = "98765454390000034563456191872363456345619187236000456456345756780000065436543";
   //string s6 = "9876545439000000000000000000000000000006543";
   //BigInteger N;
   string s6 = "1";
   //string s6 = "9876545439000000000000000000000000000006543";
   //BigInteger N;
   BigInteger A = BigInteger(s1);
   BigInteger B = BigInteger(s3);
   BigInteger C = BigInteger(s5);
   BigInteger D = BigInteger(s6);
   
   cout << endl;

   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << "C = " << C << endl;
   cout << "D = " << D << endl;
   cout << endl;

   D = A+B;
   BigInteger E = B+A;
   

   return EXIT_SUCCESS;
}