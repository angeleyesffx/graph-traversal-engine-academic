#ifndef GRAPH_H
#define GRAPH_H

#include <limits.h>

/* Vertex color states (Cormen Ch. 22) */
#define COLOR_WHITE 0
#define COLOR_GRAY  1
#define COLOR_BLACK 2

#define PRED_NONE  -1
#define DIST_INF   INT_MAX
#define TIME_NONE   0

typedef struct edge {
    int dest;
    struct edge *next;
} Edge;

typedef struct {
    int   id;
    int   color;
    int   predecessor;
    int   dist;     /* BFS: shortest-path distance from source */
    int   d_time;   /* DFS: discovery timestamp               */
    int   f_time;   /* DFS: finish timestamp                  */
    Edge *head;
} Vertex;

/* --- Lifecycle ------------------------------------------------ */
Vertex *graph_create   (int order);
int     graph_add_edge (Vertex *g, int order, int v1, int v2);
void    graph_destroy  (Vertex *g, int order);

/* --- Metrics -------------------------------------------------- */
int graph_edge_count (const Vertex *g, int order);
int graph_degree     (const Vertex *g, int v);

/* --- Traversal (Cormen Ch. 22.2 / 22.3) ---------------------- */
void graph_bfs (Vertex *g, int order, int source);
void graph_dfs (Vertex *g, int order);

/* --- Properties ---------------------------------------------- */
int graph_is_connected (Vertex *g, int order);
int graph_is_eulerian  (Vertex *g, int order);

/* --- Output --------------------------------------------------- */
void graph_print             (const Vertex *g, int order);
void graph_print_bfs_result  (const Vertex *g, int order);
void graph_print_dfs_result  (const Vertex *g, int order);

#endif /* GRAPH_H */
