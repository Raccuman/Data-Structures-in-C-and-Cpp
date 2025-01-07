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
#define NIL -1// this is like -1 or something

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
