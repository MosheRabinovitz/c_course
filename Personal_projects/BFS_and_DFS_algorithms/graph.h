#include "linked_list.h"

#define GRAPHSIZE 20

/* Graph vertex */
typedef struct graphNode {
    int name; /* name of the vertex */
    struct Node* neighbors; /* linked list of the neighbors */
    int visited; /* mark if the vertex visited (for BFS / DFS) */
}Vertex;


/* Define the type of the graph */
static Vertex *graph[GRAPHSIZE];


/* Prototypes */
void init_graph();
void insert_direct_edge (int name, int node);
void insert_non_direct_edge (int name, int node);
void remove_direct_edge (int name, int node);
void remove_non_direct_edge (int name, int node);
void print_graph_by_bfs();
void print_graph_by_dfs();
void reset_visits();
void free_graph();
