/***
* Catherine Bronte
* cebronte 1969208
* 2024 Fall CSE101 PA6
* BigInteger.cpp
*  this is where the Big Integer classes and functions get filled out
***/
#include <stdexcept>
#include <regex>
#include <string>
#include <math.h>
#include"BigInteger.h"


const ListElement base = 1000000000; // a billion
const int power = 9; // max power, not sure why we need constants but hwatever

/////////////////////////////////////////////// my little helpers :3 ////////////////////////////////////////////////////////

// BigInteger constructor
BigInteger::BigInteger(){
   signum = 0;
   digits = List();
}


// BigInteger constructor in the case a number is provided
BigInteger::BigInteger(long x){
    // its also backwards
    digits.moveFront();
    if (x == 0) {
        signum = 0;
        digits.insertAfter(0);
    } else {
        if (x < 0) {
            signum = -1;
            x = abs(x); // make it positive cause we dont want to input a negative number
        }
        else {
            signum = 1;
        }
        int temp = 0;
        while (x > 0) {
            temp = x % base;
            digits.insertBefore(temp);
            x = x / base; // truncate
        }
    }
}

// BigInteger constructor in the case a string is provided, watch out for this guy
BigInteger::BigInteger(std::string s) { // dir
// stores it backwards
    if (s == "") {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    if ((s[0] != '+' && s[0] != '-') && (isdigit(s[0]) == false)) {
        throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
    }
    //if front character in string is + or -
    if (s[0] == '+') {
        signum = 1;
        s = s.substr(1);
    } else if (s[0] == '-') {
        signum = -1;
        s = s.substr(1);
    } else {
        signum = 1;
    }
    for (int i = 0; i < s.length(); i += 1) {
        if (isdigit(s[i]) == false) {
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
    } 
    //start from back of list and if reach the power, add everything to list
    long l = s.length() - 1;
    std::string tmp = "";
    while (l >= 0) {
        if (tmp.length() == power) {
            digits.insertAfter(std::stol(tmp));
            tmp = "";
        }
        tmp = s[l] + tmp;
        l -= 1;
    }
    //if string does not evenly divided by power
    if (tmp != "") {
        while (tmp.length() < power) {
            tmp = "0" + tmp;
        }
        digits.insertAfter(std::stol(tmp));
    }
}

// BigInteger constructor in the case a number is provided
BigInteger::BigInteger(const BigInteger& N){
    this->signum = N.signum;
    this->digits = N.digits;
}


///////////////////////////////////////////////// no more confounded constructors!!! //////////////////////////////////////////////
// Acsess functions

int BigInteger::sign() const{ // will it work if I dont do the this->signum???
    return signum;
}

int BigInteger::compare(const BigInteger& N) const {
    // gimmies
    if (signum < N.signum) {
        return -1;
    }
    if (signum > N.signum) {
        return 1;
    }
    if ((signum == 0) & (N.signum == 0)) {
        return 0;
    }

    if ( digits.length() < N.digits.length()) {
        return -1;
    }
    if ( digits.length() > N.digits.length()) {
        return 1;
    }

    List A = digits; // you have to make copies because you cant change the origionals. Did my origional copy function work? who knows??
    List B = N.digits;
    A.moveFront();
    B.moveFront();

    for (int i = 0; i < digits.length(); i++) { // at this point both of the lengths are equal so we need to check each value
        if (A.peekNext() < B.peekNext()) {
            return -1;
        } else if (A.peekNext() > B.peekNext()) {
            return 1;
        }
    }

    // if it makes it to the end, it checks out
    return 0;

}


///////////////////////////////////////////// Manipulation Time ////////////////////////////////////////////////////////

void BigInteger::makeZero() {
    signum = 0;
    digits.clear();
}

void BigInteger::negate() {
    signum = -1 * signum;
}

////////////////////////////////////// MATH ////////////////////////////////////////////////////////////////////

// the way I see this you can do this is that you only need to make add of subtract but not both
// what is subtracting but adding negative numbers?
BigInteger BigInteger::add(const BigInteger& N) const {
    List A = digits;
    List B = N.digits;
    List C = List();
    long intermediate = 0;
    int carry = 0;
    long normalizedChunk = 0;
    // list is stored backwards

    // Adjust for sign differences
    if (signum == -1) {
        A.moveBack();
        // makes the list negative
        for (int c = 0; c < digits.length(); c++) {
            intermediate = -1 * (A.peekPrev());
            A.setBefore(intermediate);
            A.movePrev();
        }
        A.reverse();

    }

    if (N.signum == -1) {
        B.moveBack();
        // makes the list negative
        for (int c = 0; c < digits.length(); c++) {
            intermediate = -1 * (B.peekPrev());
            B.setBefore(intermediate);
            B.movePrev();
        }
        B.reverse();
    }

    // Traverse lists from least significant chunk to most significant
    A.moveFront();
    B.moveFront();

    while (A.position() != A.length() && B.position() != B.length()) {
        long chunkA = A.peekNext();
        long chunkB = B.peekNext();

        // Add chunks and carry
        long sum = chunkA + chunkB + carry;

        // Normalize the chunk
        if (sum > 1000000000 || sum < 0) { // might have issues here
            carry = sum / power;  // Carry forward
            normalizedChunk = sum % power;
        }
        else {
            carry = 0;
            normalizedChunk = sum;
        }

        // Insert the normalized chunk into the result
        C.moveFront();
        C.insertAfter(normalizedChunk);

        // Move to the previous chunk
        A.moveNext();
        B.moveNext();
    }

    if (A.position() != A.length()) {
        while(A.position() != A.length()) {
            long chunkA = A.peekNext();
            // Add chunks and carry
            long sum = chunkA + carry;
            // Normalize the chunk
            if (sum > 1000000000 || sum < 0) { // might have issues here
                carry = sum / power;  // Carry forward
                normalizedChunk = sum % power;
            }
            else {
                carry = 0;
                normalizedChunk = sum;
            }

            // Insert the normalized chunk into the result
            C.moveFront();
            C.insertAfter(normalizedChunk);

            // Move to the previous chunk
            A.moveNext();

        }
    }

    if (B.position() != B.length()) {
        while(B.position() != B.length()) {
            long chunkB = B.peekNext();
            // Add chunks and carry
            long sum = chunkB + carry;
            // Normalize the chunk
            if (sum > 1000000000 || sum < 0) { // might have issues here
                carry = sum / power;  // Carry forward
                normalizedChunk = sum % power;
            }
            else {
                carry = 0;
                normalizedChunk = sum;
            }
            // Insert the normalized chunk into the result
            C.moveFront();
            C.insertAfter(normalizedChunk);

            // Move to the previous chunk
            B.moveNext();

        }
    }

    // Handle final carry
    if (carry > 0) {
        C.moveFront();
        C.insertAfter(carry);
    }
    else if (carry < 0) {
        // do it all again??
        throw std::invalid_argument("Add: there was actually a negative cary at the end, you need to impliment stuff for that");  
    }

    // Assemble the result, add zeros if necissary to the front
    C.moveBack();
    int zero_list = 0;
    std::string resultStr = "";
    while (C.position() != 0) {
        std::string r = std::to_string(C.peekPrev());
        if ((r.size() == 1 && r == "0") || r.size() == 0) {
            zero_list += 1;
        }
        while ( r.size() != power) {
            r = std::to_string(0) + r;
        }
        resultStr =  r + resultStr;
        C.movePrev();
    }

    if (zero_list == C.length()) {
        return BigInteger();
    }

    // Return the new BigInteger
    return BigInteger(resultStr);
}


BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger B = N;
    B.negate();
    return add(B);
}


void shiftList(List& L, int p){ 
    std::string s = "";
    for(int i = 0; i < power; i++){
        s += '0';
    }
    long l = atol(s.c_str());
    L.moveBack();
    for(int j = 0; j< p; j++){
        L.insertBefore(l);
    }
}

void scalarMultList(List& L, ListElement p){ 
  L.moveBack();
  while(L.position() != 0){
    L.setBefore(L.peekPrev() * p);
    L.movePrev();
  }
}

void sumList(List& S, List A, List B, int sgn) { // dir
    S.clear(); // Clear the result list
    scalarMultList(B, sgn); // Apply scalar multiplication to B
    A.moveBack();
    B.moveBack();

    // Add corresponding elements from A and B
    while (A.position() != -1 && B.position() != -1) {
        S.insertAfter(A.peekPrev() + B.peekPrev());
        A.movePrev();
        B.movePrev();
    }

    // Append remaining elements from A
    while (A.position() != -1) {
        S.insertAfter(A.peekPrev());
        A.movePrev();
    }

    // Append remaining elements from B
    while (B.position() != -1) {
        S.insertAfter(B.peekPrev());
        B.movePrev();
    }

    // Normalize the result to remove leading zeros
    S.moveFront();
    while (S.length() > 1 && S.peekNext() == 0) {
        S.eraseAfter(); // Remove the leading zero
    }
}


BigInteger BigInteger::mult(const BigInteger& N) const {
    // Handle zero case
    if (digits.length() == 0 || N.digits.length() == 0) {
        return BigInteger(); // Return a zero BigInteger
    }

    BigInteger result; // Result of multiplication
    List M = N.digits; // Copy of N's digits
    // Reverse to handle least significant digits first
    M.moveFront();

    int counter = 0; // Track the power of 10 (digit position)
    while (M.position() < M.length() ) {
        BigInteger temp = *this; // Copy of `this` BigInteger
        long scalar = M.peekNext(); // Get current digit from N
        M.moveNext();

        // Shift and scale the digits of `temp`
        shiftList(temp.digits, counter); // Append `counter` zeroes
        scalarMultList(temp.digits, scalar); // Multiply by the scalar

        // Add the shifted and scaled value to the result
        sumList(result.digits, temp.digits, result.digits, 1);

        counter++; // Move to the next power of 10
    }

    // Determine the sign of the result
    result.signum = (signum == N.signum) ? 1 : -1;

    return result;
}



/////////////////////////////////////// leftovers ///////////////////////////////////////////////////////////////

std::string BigInteger::to_string() {
    // do I need to normalize flip if signum == -1??
    std::string ret = "";
    if (signum == 0) {
        return "0";
    }

    if (signum == -1) {
        ret += "-";
    }

    digits.moveBack();
    for (int i = 0; i < digits.length(); i++) {
        if (digits.position() != digits.length()) { // Skip for the most significant block
            int numPadding = power - (std::to_string(digits.peekPrev())).size();
            ret += std::string(numPadding, '0'); // Add 'numPadding' zeroes
        }
        ret += std::to_string(digits.peekPrev());
        ret += ",";
        digits.movePrev();
    }

    return ret;
}


////////////////////////////////////////////// Overloards //////////////////////////////////////////

std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    return stream << N.BigInteger::to_string();
}


bool operator==( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    if (i == 0) {
        return true;
    } 
    return false;
}

bool operator<( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    if (i == -1) {
        return true;
    } 
    return false;
}

bool operator<=( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    if (i == 0 || i == -1) {
        return true;
    } 
    return false;
}

bool operator>( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    if (i == 1) {
        return true;
    } 
    return false;
}

bool operator>=( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    if (i == 0 || i == 1) {
        return true;
    } 
    return false;
}

BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    return A.add(B);
}

BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    BigInteger I = A.add(B);
    A.digits = I.digits;
    A.signum = I.signum;
    return A; 
}

BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    return A.sub(B);
}

BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    BigInteger S = A.sub(B);
    A.digits = S.digits;
    A.signum = S.signum;
    return A; 
}

BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
    return A.mult(B);
}

BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
    BigInteger M = A.mult(B);
    A.digits = M.digits;
    A.signum = M.signum;
    return A; 
}
