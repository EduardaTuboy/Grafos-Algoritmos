#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct graph_ *Graph;

// a
Graph MyGraph(int N);
// b
bool exist_edge(Graph G, int v1, int v2);
// c
int *get_adj_vertex(Graph G, int v);
// d
bool remove_edge(Graph G, int v1, int v2);
// e
bool print_info(Graph G);
// f
int number_of_vertexs(Graph G);
// g
bool remove_graph(Graph *G);
// h
bool add_edge(Graph G, int v1, int v2, int weight);
// i
int remove_with_least_weight(Graph G);
// j
int **adjacency_matrix(Graph G);
