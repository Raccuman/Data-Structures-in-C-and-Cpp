/***
* Catherine Bronte
* cebronte 1969208
* 2024 Fall CSE101 PA4
* Matrix.c
* this is where I wrote all of my matrix functions
***/

#include "List.h"
#include "Matrix.h"
#include "stdlib.h"
#include <stdio.h>

typedef struct EntryObj* Entry;

typedef struct EntryObj{
    double val;
    int col;
} EntryObj;

Entry newEntry(double d, int i){
    Entry E = malloc(sizeof(EntryObj));
    E->val = d;
    E->col = i;
    return E;
}

void freeEntry(Entry* pE){
    if(pE != NULL && *pE != NULL){
        free(*pE);
        *pE = NULL;
        pE = NULL;
    }
}

typedef struct MatrixObj{
    List* row;
    int size;
    int nnz;        
} MatrixObj;

Matrix newMatrix(int n){
    Matrix M = malloc(sizeof(MatrixObj));
    M->row = calloc(n + 1, sizeof(List));
    for(int i = 0; i <= n; i++){
        M->row[i] = newList();
    }
    M->size = n;
    M->nnz = 0;
    return M;
}


void freeMatrix(Matrix* pM){
    if(pM != NULL && *pM != NULL){
        for(int i = 0; i <= size(*pM); i++){
            List row = (*pM)->row[i];
            for(moveFront(row); index(row) >= 0; moveNext(row)){
                Entry E = get(row);
                freeEntry(&E);
            }
            freeList(&((*pM)->row[i]));
        }
        free((*pM)->row);
        free((*pM));
        *pM = NULL;
        pM = NULL;
    }
}

////////////////////////////////////// Return functions ///////////////////////////////////////////////////////////

Entry getEntry(Matrix M ,int i, int j){
    List row = M->row[i];
    moveFront(row);
    while (index(row) >= 0 ){
        Entry E = get(row);
        if(E->col == j){
            return E;
        }
        moveNext(row);
    }
    return NULL;
}


int size(Matrix M){
    return M->size;
}

int NNZ(Matrix M){
    return M->nnz;
}


int equals(Matrix A, Matrix B){
    if(A->size != B->size || A->nnz != B->nnz){
        return 0;
    }
    for(int i = 0; i <= size(A); i++){
        List c = A->row[i];
        List d = B->row[i];
        moveFront(c);
        moveFront(d);
        while ( index(c) >=0 && index(d) >= 0) {
            Entry a = get(c);
            Entry b = get(d);
            if(!(a->val == b->val && a->col == b->col)){
                return false;
            }
            moveNext(c);
            moveNext(d);
        }
    }
    return 1;
}


////////////////////////////////////////// Actually Changes Things /////////////////////////////////////////////////////

void makeZero(Matrix M){
    for(int i = 0; i < M->size; i++){
        List row = M->row[i];
        while(length(row) > 0){
            deleteFront(row);
        }
    }
    M->nnz = 0;
}

void changeEntry(Matrix M, int i, int j, double x){ // takes a while
    Entry E = getEntry(M, i, j);
    if(E == NULL){
        if(x == 0){
            return;
        }
        List row = M->row[i];
        moveFront(row);
        while(index(row) >= 0){
            if(((Entry)get(row))->col > j){
                break;
            }
            moveNext(row);
        }
        if(index(row) >= 0){
            insertBefore(row, newEntry(x, j));
        }else{
            append(M->row[i], newEntry(x, j));
        }
        M->nnz += 1;
    }else{
        if(x == 0){
                while(((Entry)get(M->row[i]))->col != j){
                    if(index(M->row[i]) == -1) {
                        moveFront(M->row[i]);
                    }
                    if(((Entry)get(M->row[i]))->col > j) {
                        movePrev(M->row[i]);
                    }
                    if(((Entry)get(M->row[i]))->col < j) {
                        moveNext(M->row[i]);
                    } 
                }
            freeEntry(&E);
            delete(M->row[i]);
            M->nnz -= 1;
            return;
        }
        E->val = x;
    }
}

Matrix copy(Matrix A){ // something was wrong with my origional copy
    Matrix copyA = newMatrix(A->size);
    copyA->nnz = NNZ(A);
    for(int i = 0; i <= size(A); i++){
        List row = A->row[i];
        for(moveFront(row); index(row) >= 0; moveNext(row)){
            Entry E = get(row);
            append(copyA->row[i], newEntry(E->val, E->col));
        }
    }
    return copyA;
}

Matrix transpose(Matrix A) {
    Matrix N = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        moveFront(A->row[i]);
        
        while (index(A->row[i]) >= 0) { 
            Entry cur = get(A->row[i]);
            // you swap em
            changeEntry(N, cur->col, i, cur->val);
            moveNext(A->row[i]);
        }
    }
    return N; 
}


Matrix scalarMult(double x, Matrix A) {
    Matrix N = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        moveFront(A->row[i]);
        for (int k = 0; k < length(A->row[i]); k++) {
            Entry temp = get(A->row[i]);
            changeEntry(N, i, temp->col, temp->val * x);
            moveNext(A->row[i]);
        }
    }
    return N;
}
 


Matrix diff(Matrix A, Matrix B) { // short for DIFFICULT!!!!!
    if (A->size != B->size) {
        fprintf(stderr, "The diff function had matrices passed in that were not the same size, BAD!");
        exit(1);
    }
    Matrix N = newMatrix(A->size);

    for (int i = 1; i <= A->size; i++) {
        if (A->row[i] != NULL) {
            moveFront(A->row[i]);
        }
        if (B->row[i] != NULL) {
            moveFront(B->row[i]);
        }

        while (index(A->row[i]) >= 0 && index(B->row[i]) >= 0) { // no accidents here
            Entry a = get(A->row[i]);
            Entry b = get(B->row[i]);

            if (a->col != b->col) {
                if (a->col < b->col) {
                    changeEntry(N, i, a->col, a->val);
                    moveNext(A->row[i]);
                } else {
                    changeEntry(N, i, b->col, -b->val);
                    moveNext(B->row[i]);
                }
            } else {
                changeEntry(N, i, a->col, a->val - b->val);
                moveNext(A->row[i]);
                moveNext(B->row[i]);
            }
        }

        while (index(A->row[i]) >= 0) {
            Entry a = get(A->row[i]);
            changeEntry(N, i, a->col, a->val);
            moveNext(A->row[i]);
        }

        while (index(B->row[i]) >= 0) {
            Entry b = get(B->row[i]);
            changeEntry(N, i, b->col, -b->val);
            moveNext(B->row[i]);
        }
    }

    return N;
}


Matrix sum(Matrix A, Matrix B){
    B = copy(B);
    Matrix sumAB = newMatrix(size(A));
    for(int i = 0; i <= size(A); i++){
        List rowA = A->row[i];
        List rowB = B->row[i];
        for(moveFront(rowA), moveFront(rowB); index(rowA) >= 0 && index(rowB) >= 0; ){
            Entry E_A = get(rowA);
            Entry E_B = get(rowB);
            if(E_A->col == E_B->col){
                append(sumAB->row[i], newEntry(E_A->val + E_B->val, E_A->col));
                if(E_A->val + E_B->val == 0){
                    deleteBack(sumAB->row[i]);
                    sumAB->nnz -= 1;
                }
                moveNext(rowA);
                moveNext(rowB);
            }else if (E_A->col < E_B->col){
                append(sumAB->row[i], newEntry(E_A->val, E_A->col));
                moveNext(rowA);
            }else if (E_A->col > E_B->col){
                append(sumAB->row[i], newEntry(E_B->val, E_B->col));
                moveNext(rowB);
            }
            sumAB->nnz += 1;
        }
        while (index(rowA) >= 0){
            Entry E_A = get(rowA);
            append(sumAB->row[i], newEntry(E_A->val, E_A->col));
            sumAB->nnz += 1;
            moveNext(rowA);
        }
        while (index(rowB) >= 0){
            Entry E_B = get(rowB);
            append(sumAB->row[i], newEntry(E_B->val, E_B->col));
            sumAB->nnz += 1;
            moveNext(rowB);
        }
    }
    freeMatrix(&B);
    return sumAB;
}



Matrix product(Matrix A, Matrix B) { // something is wrong with the product, probs not outputting right number
    if (A->size != B->size) {
        fprintf(stderr, "The product function had matrices passed in that were not the same size, BAD!");
        exit(1);
    }
    
    Matrix N = newMatrix(A->size);
    Matrix T = transpose(B);

    for (int i = 1; i <= A->size; i++) {
        for (int j = 1; j <= A->size; j++) {
            moveFront(A->row[i]);
            moveFront(T->row[j]); 

            int sum = 0;
            if(length(A->row[i]) == 0) {
                break;
            }
            if(length(T->row[j]) == 0) {
                continue;
            }


            while (index(A->row[i]) >= 0 && index(T->row[j]) >= 0) {
                Entry a = get(A->row[i]);
                Entry b = get(T->row[j]);
                
                if (a->col < b->col) {
                    moveNext(A->row[i]);
                } else if (a->col > b->col) {
                    moveNext(T->row[j]);
                } else {
                    sum += a->val * b->val;
                    moveNext(A->row[i]);
                    moveNext(T->row[j]);
                }
            }
            
            if (sum != 0) {  // Only store non-zero values, we dont like seeing them do we
                changeEntry(N, i, j, sum);
            }
        }
    }
    
    freeMatrix(&T);  // Clean up time
    return N;
}

//////////////////////////////////////////////////////////// bonus fry /////////////////////////////////////

void printMatrix(FILE* out, Matrix M) {
    for (int i = 1; i <= M->size; i++) {
        if (length(M->row[i]) == 0) {
            continue;
        }
        moveFront(M->row[i]);
        fprintf(out, "%d: ", i);

        for (int k = 0; k < length(M->row[i]); k++) {
            Entry new = get(M->row[i]);           
            fprintf(out, "(%d, %.1f) ", new->col, new->val);
            moveNext(M->row[i]);
        }
        fprintf(out, "\n");
    } 
}

