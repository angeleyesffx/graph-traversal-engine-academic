#include <stdio.h>
#include "graph.h"

int main(void) {
    const int ORDER = 10;
    Vertex *g = graph_create(ORDER);

    graph_add_edge(g, ORDER, 3, 4);
    graph_add_edge(g, ORDER, 4, 2);
    graph_add_edge(g, ORDER, 5, 4);
    graph_add_edge(g, ORDER, 2, 3);
    graph_add_edge(g, ORDER, 3, 7);

    printf("Vertices: %d  |  Edges: %d  |  Size |V|+|E|: %d\n",
           ORDER, graph_edge_count(g, ORDER), ORDER + graph_edge_count(g, ORDER));

    graph_print(g, ORDER);

    printf("\n=== Depth-First Search ===\n");
    graph_dfs(g, ORDER);
    graph_print_dfs_result(g, ORDER);

    printf("\n=== Breadth-First Search (source: V2) ===\n");
    graph_bfs(g, ORDER, 2);
    graph_print_bfs_result(g, ORDER);

    printf("\n=== Eulerian Check ===\n");
    if (graph_is_eulerian(g, ORDER))
        printf("The graph IS Eulerian (connected + all degrees even).\n");
    else
        printf("The graph is NOT Eulerian.\n");

    graph_destroy(g, ORDER);
    return 0;
}
