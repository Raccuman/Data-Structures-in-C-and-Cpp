/***
* Catherine Bronte
* cebronte 1969208
* 2024 Fall CSE101 PA2
* Graph.h
* this is where all of the graph functions are declared
***/
#include "List.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define INF 999999899// this is infinity
#define NIL 0// this is like -1 or something
#define UNDEF -2

// Exported types -------------------------------------------------------------

typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);

void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);

int getSize(Graph G);

int getSource(Graph G);

int getParent(Graph G, int u);

int getDist(Graph G, int u);

void getPath(List L, Graph G, int u);

/*** Manipulation procedures ***/
void makeNull(Graph G);

void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

void BFS(Graph G, int s);

/*** Other operations ***/
void printGraph(FILE* out, Graph G);

void myPrint(FILE* out, Graph G, int source, int destination);


////////////////////////////////// PA3 additions ///////////////////////////////

int getDiscover(Graph G, int u); // is this figuring out discovery time or is it figuring out whether it has been discovered or not??

int getFinish(Graph G, int u); // same as above

void DFS(Graph G, List S); // there is psudo code for this in the docs, you have to come up with visit

Graph transpose(Graph G); // all graph directions are flipped

Graph copyGraph(Graph G);

void tackPrint(FILE* out, Graph G, List L);
