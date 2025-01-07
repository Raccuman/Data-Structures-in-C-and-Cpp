/***
* Catherine Bronte
* cebronte 1969208
* 2024 Fall CSE101 PA4
* Sparse.c
* finds the shortest path, functions as the main
***/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include <string.h>
#include "Matrix.h"

/////////////////////////////////// This is all of my junk from FIND PATH //////////////////////////////////////////////////////

int main (int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Bad! you didnt input an in file AND an out file");
        exit(1);
    }

    FILE* in_file = fopen(argv[1], "r");
    if (in_file == NULL) {
        fprintf(stderr, "your input file didnt open correctly, that sounds like a you problem, BAD!");
        exit(1);
    }

    FILE* out_file = fopen(argv[2], "w");
    if (out_file == NULL) {
        fprintf(stderr, "your output file didnt open correctly, that sounds like a you problem, BAD!");
        exit(1);
    }


/////////////////////// this reads in and fills out the matricies  ///////////////////////////////////////

    int size;
    fscanf(in_file, "%d", &size);  // Read the number of vertices
    Matrix A = newMatrix(size);
    Matrix B = newMatrix(size);

    int a_elements; // the number of elements in matrix A
    fscanf(in_file, " %d", &a_elements);

    int b_elements; // the number of elements in matrix B
    fscanf(in_file, " %d", &b_elements);

    int row;
    int col;
    float val;
    for (int i = 0; i < a_elements; i++) {
        fscanf(in_file, "%d %d %f", &row, &col, &val);
        changeEntry(A, row, col, val); 
    }

    for (int i = 0; i < b_elements; i++) {
        fscanf(in_file, "%d %d %f", &row, &col, &val);
        changeEntry(B, row, col, val); 
    }


    ////////////////////////// this prints all of the matrix operations  //////////////////////////////////////////////
    fprintf(out_file, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(out_file, A);

    fprintf(out_file, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(out_file, B);


    fprintf(out_file, "(1.5)*A =\n");
    Matrix C = scalarMult(1.5, A);
    printMatrix(out_file, C);
    freeMatrix(&C);


    fprintf(out_file, "A+B =\n");
    Matrix D = sum(A, B);
    printMatrix(out_file, D);
    freeMatrix(&D);


    fprintf(out_file, "A+A =\n");
    Matrix E = sum(A, A);
    printMatrix(out_file, E);
    freeMatrix(&E);


    fprintf(out_file, "B-A =\n");
    Matrix F = diff(B, A);
    printMatrix(out_file, F);
    freeMatrix(&F);


    fprintf(out_file, "A-A =\n");
    Matrix G = diff(A, A);
    printMatrix(out_file, G);
    freeMatrix(&G);


    fprintf(out_file, "Transpose(A) =\n");
    Matrix H = transpose(A);
    printMatrix(out_file, H);
    freeMatrix(&H);


    fprintf(out_file, "A*B =\n");
    Matrix I = product(A, B);
    printMatrix(out_file, I);
    freeMatrix(&I);


    fprintf(out_file, "B*B =\n");
    Matrix J = product(B, B); 
    printMatrix(out_file, J);
    freeMatrix(&J);


////////////////////////////// closing up shop ///////////////////////////////////////////

    fclose(in_file);
    fclose(out_file);

    freeMatrix(&A);
    freeMatrix(&B);
    return 0;


}

/////////////////////////////////////////// end of find path junk . . . //////////////////////////////////////////////////
