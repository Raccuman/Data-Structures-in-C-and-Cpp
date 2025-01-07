/***
* Catherine Bronte 
* cebronte 1969208
* 2024 Fall CSE101 PA2
* Graph.c
* this is where all of the graph functions are written out
***/
#include "Graph.h"

/////////////////////////////////////////// defining all of our structs and formats fro graph /////////////////////////////

typedef struct GraphObj* Graph; // makes the graph pointer

struct GraphObj{
   List* array_of_lists; // An array of Lists whose 𝑖th element contains the neighbors of vertex 
   int* vertex_colors; // An array of ints (or chars, or strings) whose 𝑖th element is the color (white, gray, black) of vertex 
   int* parent_of_vertex;// An array of ints whose 𝑖th element is the parent of vertex 
   int* distance; // An array of ints whose 𝑖th element is the distance from the (most recent) source to vertex 

   // all of the above should be pointers to the named array???
   int order; // # of vertices in graph
   int size; // # of edges in graph
   int recent_source; //  the label of the vertex that was most recently used as source for BFS
} GraphObj;

typedef struct GraphObj* Graph;

/////////////////////////////////////// Constructors - Destructors ///////////////////////////////////////////////////////

Graph newGraph(int n){
   Graph G = malloc(sizeof(struct GraphObj));
   assert( G!=NULL );
   G->order = n;
   G->size = 0;
   G->recent_source = NIL;

   G->array_of_lists = malloc(sizeof(List)*(n+1));
   G->vertex_colors = malloc(sizeof(int)*(n+1));
   G->parent_of_vertex = malloc(sizeof(int)*(n+1));
   G->distance = malloc(sizeof(int)*(n+1));

   for(int i = 1; i <= n; i += 1) {
      G->array_of_lists[i] = newList();
      G->vertex_colors[i] = 0;
      G->parent_of_vertex[i] = NIL;
      G->distance[i] = INF;
   }
   return(G);
}

void freeGraph(Graph* pG) {
   if(pG!=NULL && *pG!=NULL) { 
      //this is the only complex free
      for (int i = 1; i <= (*pG)->order; i++) { // might need to set i to 0, if i do it says double error
        freeList(&((*pG)->array_of_lists[i]));
      }

        free((*pG)->array_of_lists);

        free((*pG)->vertex_colors);
        free((*pG)->parent_of_vertex);
        free((*pG)->distance);

        free(*pG);
        *pG = NULL;
   }
}

/////////////////////////////////////////// Access Functions and Whatnot /////////////////////////////////////

int getOrder(Graph G) {
   return G->order;
}

int getSize(Graph G) {
   return G->size;
}

int getSource(Graph G) {
   return G->recent_source;
}


// Array ones, might have issues
int getParent(Graph G, int u) {
   if (1 <= u && u <= getOrder(G)) {
      return G->parent_of_vertex[u];
   }
   return NIL;
}

int getDist(Graph G, int u) {
   if (1 <= u && u <= getOrder(G)) {
      return G->distance[u];
   }
   return INF;
}

// something is wrong here, it only prints the path in ascending vertices. It gets the distance correct, but not the path. BFS???
void getPath(List L, Graph G, int u) {
    if (u < 1 || u > getOrder(G)) {
        printf("getPath error: Vertex is out of range, BAAAD!!");
        return; 
    }

    if (getSource(G) == NIL) {
        printf("BFS has not been run yet\n");
        return; // Exit with an error
    }

   // base case
    if (u == getSource(G)) {
        append(L, getSource(G));  // end case????
        return;
    } else if (getParent(G, u) == NIL) {
      append(L, NIL);
    } else {
      getPath(L, G, getParent(G,u));
      append(L,u);
    }
}


//////////////////////////////////////// Manipulation Procedures (The Difficult ones) ///////////////////////////////////////

void makeNull(Graph G) {
   for (int i = G->order +1; i > 0; i--) {
      clear(G->array_of_lists[i-1]);
   }
   return;
}

void addEdge(Graph G, int u, int v) {
   // sort of base case
   // do arrays not start at 0??
   if (u < 1 || v < 1 || u > G->order || v > G->order) { // nodes must start at value one, but can be indexed starting at 0
      printf("the variable is not within a valid range");
      return;
   }
   G->size += 1;
   int insertedu = 0;
   int insertedv = 0;
   if (isEmpty(G->array_of_lists[u])) {
      append(G->array_of_lists[u], v);
      insertedu += 1;
   }
   if (isEmpty(G->array_of_lists[v])) {
      append(G->array_of_lists[v], u);
      insertedv += 1;
   }
   

   // list iteration time
   moveFront(G->array_of_lists[u]);
   moveFront(G->array_of_lists[v]);

   if (insertedu == 0){
      for (int k = 0; k < length(G->array_of_lists[u]); k++) {
         if (get(G->array_of_lists[u]) >= v) {
            insertBefore(G->array_of_lists[u], v);
            insertedu += 1;
            break;
         }
         moveNext(G->array_of_lists[u]);
      }
      if (insertedu == 0) {
         append(G->array_of_lists[u], v);
      }
   }

if (insertedv == 0) {
      for (int j = 0; j < length(G->array_of_lists[v]); j++) {
         if (get(G->array_of_lists[v]) >= u) {
            insertBefore(G->array_of_lists[v], u);
            insertedv += 1;
            break;
         }
         moveNext(G->array_of_lists[v]);
      }
      if (insertedv == 0) {
         append(G->array_of_lists[v], u);
      }
   }
   return;
}



void addArc(Graph G, int u, int v) {
   if (u < 1 || v < 1 || u > G->order || v > G->order) {
      printf("the variable is not within range\n");
      return;
   }

   int inserted = 0;
   moveFront(G->array_of_lists[u]);

   for (int j = 0; j < length(G->array_of_lists[u]); j++) {
      // ypu already have it silly
      if (get(G->array_of_lists[u]) == v) {
         return;
      }
      if (get(G->array_of_lists[u]) > v) {
         insertBefore(G->array_of_lists[u], v);
         inserted = 1;
         break;
      }
      moveNext(G->array_of_lists[u]);
   }
   G->size += 1;

   // no inserting, tack it on
   if (!inserted) {
      append(G->array_of_lists[u], v);
   }

   return;
}


void BFS(Graph G, int s) {
   for (int i = 1; i <= G->order; i++) {
      G->vertex_colors[i] = 0; // set all colors to white
      G->distance[i] = INF; // all distances are infinity
      G->parent_of_vertex[i] = NIL; // no one has parents, shame
   }
   
   G->recent_source = s;
   G->vertex_colors[s] = 1; // set source s to grey
   G->distance[s] = 0; // source distance to its self is 0
   G->parent_of_vertex[s] = NIL; // the source has no parent

   List theway = newList();
   List partner = NULL;
   append(theway, s);
   int x = 0;
   int y = 0;
   while (!isEmpty(theway)) {
      x = front(theway);
      deleteFront(theway);
      partner = G->array_of_lists[x];
      moveFront(partner);
      for (int j = 0; j < length(G->array_of_lists[x]); j++) {
         y = get(partner);
         if (G->vertex_colors[y] == 0) {
            G->vertex_colors[y] = 1;
            G->distance[y] = G->distance[x] + 1;
            G->parent_of_vertex[y] = x;
            append(theway, y);
         }
         moveNext(partner);
      }
      G->vertex_colors[x] = 2;
   }
   freeList(&theway);
   return;
}



void printGraph(FILE* out, Graph G) {
   if( G==NULL ){
   printf("Graph Error: calling printGraph() on NULL Graph reference\n");
   exit(EXIT_FAILURE);
   }

   for (int i = 1; i <= G->order; i++) {
      fprintf(out, "%d: ", i);
      moveFront(G->array_of_lists[i]);
      for (int j = 0; j < length(G->array_of_lists[i]); j++) {
         fprintf(out, "%d ", get(G->array_of_lists[i]));
         moveNext(G->array_of_lists[i]);
      }
      fprintf(out, "\n");

   }
   fprintf(out, "\n");
   return; 
}

void myPrint(FILE* out, Graph G, int source, int destination) {
   if( G==NULL ){
      printf("Graph Error: calling printGraph() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   BFS(G, source);
   List path = newList();
   getPath(path, G, destination);

   int d_destination = getDist(G, destination);

   if (d_destination  != INF) {
      fprintf(out, "The distance from %d to %d is %d\nA shortest %d-%d path is: ", source, destination, d_destination, source, destination);
      moveFront(path);
      for( int i = 0; i < length(path); i++) {
         fprintf(out, "%d ", get(path));
         moveNext(path);
      }
      fprintf(out, "\n\n");
   }
   else {
      fprintf(out, "The distance from %d to %d is infinity\nNo %d-%d path exists\n\n", source, destination, source, destination);
   }
   freeList(&path);
      return;
   }

 



 


