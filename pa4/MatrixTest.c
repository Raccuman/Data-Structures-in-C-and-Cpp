/***
* Catherine Bronte
* cebronte 1969208
* 2024 Fall CSE101 PA4
* MatrixTest.c
* this is where I test my matrix functions
***/

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"

int main(){
   int n=100000;
   Matrix A = newMatrix(n);

    changeEntry(A, 1, 1, 4);
    changeEntry(A, 1, 2, 2);
    changeEntry(A, 1, 3, 3);
    changeEntry(A, 2, 1, 2);
    changeEntry(A, 3, 1, 0);
    changeEntry(A, 2, 2, 2);
    changeEntry(A, 3, 3, 4);

   printMatrix(stdout, A);
   
   printf("%d\n", NNZ(A));
   printf("\n");

   Matrix C = sum(A, A);
   printMatrix(stdout, C);
   printf("%d\n", NNZ(C));
   printf("\n");



   freeMatrix(&A);
   freeMatrix(&C);


   return EXIT_SUCCESS;
}

/*
Output of this program:

1: (1, 1.0)  nul  (3, 1.0)
2:   nul  (2, 1.0)  nul
3: (1, 1.0) (2, 1.0) (3, 1.0)
6
1: (1, 1.0)   nul   (3, 1.0)
2:   nul   (2, 1.0) (3, 1.0)
3: (1, 1.0)   nul   (3, 1.0)


*/