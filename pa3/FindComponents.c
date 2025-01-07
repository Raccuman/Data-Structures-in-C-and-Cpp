/***
* Catherine Bronte
* cebronte 1969208
* 2024 Fall CSE101 PA3
* FindComponents.c
* finds the shortest path, functions as the main
***/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include <string.h>
#include "Graph.h"

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


/////////////////////// this reads in and prints all of the edges ///////////////////////////////////////

    int ordering;
    fscanf(in_file, "%d", &ordering);  // Read the number of vertices
    Graph G = newGraph(ordering);

    int a;
    int c;
    while (fscanf(in_file, "%d %d", &a, &c) == 2 && a != 0 && c != 0) {
        addArc(G, a, c); 
    }

    printGraph(out_file, G);


    ////////////////////////// this does all of the source to destination stuff ////////////////////////////////////////
    List enter = newList();
    tackPrint(out_file, G, enter);

    fclose(in_file);
    fclose(out_file);

////////////////////////////// closing up shop ///////////////////////////////////////////

    freeList(&enter);
    freeGraph(&G);
    return 0;


}

/////////////////////////////////////////// end of find path junk . . . //////////////////////////////////////////////////