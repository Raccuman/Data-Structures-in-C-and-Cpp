/***
* Catherine Bronte 
* cebronte 1969208
* 2024 Fall CSE101 PA2
* GraphTest.c
* my tests for Graph functions
***/
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char *argv[])
{

    int n = 7;

    Graph G = NULL;

    // Build graph G
    G = newGraph(n);


    //

    addEdge(G, 6, 1);
    addEdge(G, 6, 3);
    addEdge(G, 6, 2);
    addEdge(G, 4, 2);
    addEdge(G, 2, 5);
    addArc(G, 3, 1);

    // Print adjacency list representation of G
    printGraph(stdout, G);

    BFS(G, 3);

    fprintf(stdout, "%d\n", getDist(G, 4));
    fprintf(stdout, "%d\n", getOrder(G));

    // Determine the Radius and Diameter of G, as well as the Central and
    // Peripheral vertices.
 

    freeGraph(&G);

    printf("yay!\n");
    return (0);

}
