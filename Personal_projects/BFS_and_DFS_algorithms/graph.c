#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "queue.h"
#include "stack.h"

/* init */
 void init_graph()
 {
    for (int i = 0; i < GRAPHSIZE; ++i)
	{
		Vertex * g_node = (Vertex*) malloc(sizeof(Vertex));
		graph[i] = g_node;
		graph[i]->name = i;
		graph[i]->neighbors = NULL;
        	graph[i]->visited = 0;
	}
 }

/* add edge to vertices */
void insert_direct_edge (int name, int node)
{
    insert_to_list(&(graph[name]->neighbors), node);
}

void insert_non_direct_edge (int name, int node)
{
    insert_to_list(&(graph[name]->neighbors), node);
    insert_to_list(&(graph[node]->neighbors), name);
}


/* remove edge from vertices */
void remove_direct_edge (int name, int node)
{
    remove_from_list(&(graph[name]->neighbors), node);
}

void remove_non_direct_edge (int name, int node)
{
    remove_from_list(&(graph[name]->neighbors), node);
    remove_from_list(&(graph[node]->neighbors), name);
}


/* BFS algorithm */
void print_graph_by_bfs()
{
    reset_visits();
    Queue queue_graph;
    init(&queue_graph);

    printf("BFS algorithm:\n");
    for (int i = 0; i < GRAPHSIZE; ++i)
    {
        if (graph[i]->visited == 0)
        {
            enqueue(&queue_graph, i);
            while(!isEmpty(&queue_graph))
            {
                int father = dequeue(&queue_graph);
                if (graph[father]->visited == 0)
                {
                    printf("%d, ", father);
                    graph[father]->visited = 1;
                
                    struct Node* neighbor = graph[father]->neighbors;
                    while (neighbor)
                    {
                        if(graph[neighbor->name]->visited == 0)
                            enqueue(&queue_graph, neighbor->name);
                        
                        neighbor = neighbor->next;
                    }
                }
            }
            printf("\n");            
        }
    }
}

/* DFS algorithm */
void print_graph_by_dfs()
{
    reset_visits();
    Stack stack_graph;
    stack_init(&stack_graph);
    
    printf("DFS algorithm:\n");
    for (int i = 0; i < GRAPHSIZE; ++i)
    {
        if (graph[i]->visited == 0)
        {
            push(&stack_graph, i);
            while(!stack_isEmpty(&stack_graph))
            {
                int father = pop(&stack_graph);
                if (graph[father]->visited == 0)
                {
                    printf("%d, ", father);
                    graph[father]->visited = 1;
                
                    struct Node* neighbor = graph[father]->neighbors;
                    while (neighbor)
                    {
                        if(graph[neighbor->name]->visited == 0)
                            push(&stack_graph, neighbor->name);

                        neighbor = neighbor->next;
                    }
                }
            }
            printf("\n");
        }
    }
}


void reset_visits()
{
    for (int i = 0; i < GRAPHSIZE; ++i)
        graph[i]->visited = 0;
}


void free_graph()
{
    for (int i = 0; i < GRAPHSIZE; ++i)
    {
        struct Node* temp = graph[i]->neighbors, * to_free;

        while (temp != NULL)
        {
            to_free = temp;
            temp = temp->next;
            free(to_free);
        }
        free(graph[i]);
    }
}
