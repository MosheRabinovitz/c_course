#include "graph.h"


int main()
{
    /* initialize the graph */
    init_graph();

    /* 1st tree:
              0
            /   \
           2     1
          /     / \
         7     4   5
        / \
       6   3    
    */
    insert_non_direct_edge(0, 1);
    insert_non_direct_edge(0, 2);
    insert_non_direct_edge(1, 5);
    insert_non_direct_edge(1, 4);
    insert_non_direct_edge(2, 7);
    insert_non_direct_edge(7, 3);
    insert_non_direct_edge(7, 6);

    /* 2nd tree 
              8
            /   \
           10    12
          /   \     \
         14    16    18
       / | \
      9  15 19    
    */
    insert_non_direct_edge(8, 10);
    insert_non_direct_edge(8, 12);
    insert_non_direct_edge(10, 14);
    insert_non_direct_edge(10, 16);
    insert_non_direct_edge(12, 18);
    insert_non_direct_edge(14, 19);
    insert_non_direct_edge(14, 15);
    insert_non_direct_edge(14, 9);

    /* 3rd tree 
            11
           /
         17
        /
      13
    */
    insert_direct_edge(11, 17);
    insert_direct_edge(17, 13);
    
    /* Run the BFS algorithem and DFS algorithem */
    print_graph_by_bfs();
    print_graph_by_dfs();

    /* free the graph */
    free_graph();

}