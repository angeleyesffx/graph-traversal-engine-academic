#include "graph.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

/* ── Lifecycle ─────────────────────────────────────────────────────── */

Vertex *graph_create(int order) {
    Vertex *g = malloc(sizeof(Vertex) * (size_t)order);
    if (!g) return NULL;
    for (int i = 0; i < order; i++) {
        g[i].id          = i;
        g[i].color       = COLOR_WHITE;
        g[i].predecessor = PRED_NONE;
        g[i].dist        = DIST_INF;
        g[i].d_time      = TIME_NONE;
        g[i].f_time      = TIME_NONE;
        g[i].head        = NULL;
    }
    return g;
}

/* Allocates both edges before mutating the graph so a failed malloc
   leaves the graph unmodified. Returns 1 on success, 0 on failure. */
int graph_add_edge(Vertex *g, int order, int v1, int v2) {
    if (!g || v1 < 0 || v1 >= order || v2 < 0 || v2 >= order || v1 == v2)
        return 0;

    Edge *e1 = malloc(sizeof(Edge));
    Edge *e2 = malloc(sizeof(Edge));
    if (!e1 || !e2) { free(e1); free(e2); return 0; }

    e1->dest  = v2; e1->next = g[v1].head; g[v1].head = e1;
    e2->dest  = v1; e2->next = g[v2].head; g[v2].head = e2;
    return 1;
}

void graph_destroy(Vertex *g, int order) {
    if (!g) return;
    for (int i = 0; i < order; i++) {
        Edge *cur = g[i].head;
        while (cur) {
            Edge *nxt = cur->next;
            free(cur);
            cur = nxt;
        }
    }
    free(g);
}

/* ── Metrics ───────────────────────────────────────────────────────── */

int graph_edge_count(const Vertex *g, int order) {
    int total = 0;
    for (int i = 0; i < order; i++)
        for (Edge *e = g[i].head; e; e = e->next)
            total++;
    return total / 2;
}

int graph_degree(const Vertex *g, int v) {
    int deg = 0;
    for (Edge *e = g[v].head; e; e = e->next)
        deg++;
    return deg;
}

/* ── BFS — Cormen Ch. 22.2, p. 594 ────────────────────────────────── */

void graph_bfs(Vertex *g, int order, int source) {
    for (int i = 0; i < order; i++) {
        g[i].color       = COLOR_WHITE;
        g[i].dist        = DIST_INF;
        g[i].predecessor = PRED_NONE;
    }

    Queue q;
    queue_init(&q);

    g[source].color = COLOR_GRAY;
    g[source].dist  = 0;
    queue_enqueue(&q, source);

    while (!queue_is_empty(&q)) {
        int u;
        queue_dequeue(&q, &u);
        for (Edge *e = g[u].head; e; e = e->next) {
            int v = e->dest;
            if (g[v].color == COLOR_WHITE) {
                g[v].color       = COLOR_GRAY;
                g[v].dist        = g[u].dist + 1;
                g[v].predecessor = u;
                queue_enqueue(&q, v);
            }
        }
        g[u].color = COLOR_BLACK;
    }
}

/* ── DFS — Cormen Ch. 22.3, p. 604 ────────────────────────────────── */

static int _dfs_time;

static void _dfs_visit(Vertex *g, int u) {
    g[u].color  = COLOR_GRAY;
    g[u].d_time = ++_dfs_time;
    for (Edge *e = g[u].head; e; e = e->next) {
        int v = e->dest;
        if (g[v].color == COLOR_WHITE) {
            g[v].predecessor = u;
            _dfs_visit(g, v);
        }
    }
    g[u].color  = COLOR_BLACK;
    g[u].f_time = ++_dfs_time;
}

void graph_dfs(Vertex *g, int order) {
    for (int i = 0; i < order; i++) {
        g[i].color       = COLOR_WHITE;
        g[i].predecessor = PRED_NONE;
        g[i].d_time      = TIME_NONE;
        g[i].f_time      = TIME_NONE;
    }
    _dfs_time = 0;
    for (int i = 0; i < order; i++)
        if (g[i].color == COLOR_WHITE)
            _dfs_visit(g, i);
}

/* ── Properties ────────────────────────────────────────────────────── */

/* Runs BFS from the first vertex with edges and checks whether every
   vertex with edges was reached. Isolated vertices are excluded per
   the standard definition of Eulerian connectivity.
   NOTE: modifies color/dist/predecessor as a side effect of BFS. */
int graph_is_connected(Vertex *g, int order) {
    int start = -1;
    for (int i = 0; i < order; i++)
        if (g[i].head) { start = i; break; }
    if (start == -1) return 1;  /* no edges: trivially "connected" */

    graph_bfs(g, order, start);

    for (int i = 0; i < order; i++)
        if (g[i].head && g[i].color != COLOR_BLACK)
            return 0;
    return 1;
}

int graph_is_eulerian(Vertex *g, int order) {
    if (!graph_is_connected(g, order))
        return 0;
    for (int i = 0; i < order; i++)
        if (graph_degree(g, i) % 2 != 0)
            return 0;
    return 1;
}

/* ── Output ────────────────────────────────────────────────────────── */

void graph_print(const Vertex *g, int order) {
    printf("\n=== Adjacency List ===\n");
    for (int i = 0; i < order; i++) {
        printf("V%d:", i);
        for (Edge *e = g[i].head; e; e = e->next)
            printf(" -> %d", e->dest);
        printf("\n");
    }
}

void graph_print_bfs_result(const Vertex *g, int order) {
    printf("\n=== BFS Result ===\n");
    printf("%-8s %6s %8s %6s\n", "Vertex", "Color", "Dist", "Pred");
    for (int i = 0; i < order; i++) {
        char dist_buf[16];
        if (g[i].dist == DIST_INF)
            snprintf(dist_buf, sizeof(dist_buf), "INF");
        else
            snprintf(dist_buf, sizeof(dist_buf), "%d", g[i].dist);
        printf("V%-7d %6d %8s %6d\n",
               i, g[i].color, dist_buf, g[i].predecessor);
    }
}

void graph_print_dfs_result(const Vertex *g, int order) {
    printf("\n=== DFS Result (timestamps) ===\n");
    printf("%-8s %6s %6s %6s %6s\n", "Vertex", "Color", "d", "f", "Pred");
    for (int i = 0; i < order; i++)
        printf("V%-7d %6d %6d %6d %6d\n",
               i, g[i].color, g[i].d_time, g[i].f_time, g[i].predecessor);
}
