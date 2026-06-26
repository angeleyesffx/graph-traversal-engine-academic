#include <stdio.h>
#include "graph.h"
#include "testrunner.h"

int main(void) {
    printf("=== DFS + Eulerian Tests ===\n");

    /* TC-DFS01: single vertex (BVA minimum) */
    Vertex *g = graph_create(1);
    graph_dfs(g, 1);
    ASSERT("TC-DFS01: single vertex is BLACK",     g[0].color == COLOR_BLACK);
    ASSERT("TC-DFS01: d_time < f_time",            g[0].d_time < g[0].f_time);
    ASSERT("TC-DFS01: predecessor = PRED_NONE",    g[0].predecessor == PRED_NONE);
    graph_destroy(g, 1);

    /* TC-DFS02: linear path 0-1-2
       Expected traversal: 0 discovers 1 discovers 2.
       Parenthesis theorem (Cormen Thm. 22.7):
         d[V0] < d[V1] < f[V1] < f[V0] (V0 is proper ancestor of V1) */
    g = graph_create(3);
    graph_add_edge(g, 3, 0, 1);
    graph_add_edge(g, 3, 1, 2);
    graph_dfs(g, 3);
    ASSERT("TC-DFS02: all vertices BLACK",
           g[0].color == COLOR_BLACK && g[1].color == COLOR_BLACK &&
           g[2].color == COLOR_BLACK);
    ASSERT("TC-DFS02: V1 predecessor = V0",        g[1].predecessor == 0);
    ASSERT("TC-DFS02: V2 predecessor = V1",        g[2].predecessor == 1);
    ASSERT("TC-DFS02: discovery order d0 < d1 < d2",
           g[0].d_time < g[1].d_time && g[1].d_time < g[2].d_time);
    ASSERT("TC-DFS02: parenthesis theorem V0 contains V1",
           g[0].d_time < g[1].d_time && g[1].f_time < g[0].f_time);
    ASSERT("TC-DFS02: parenthesis theorem V1 contains V2",
           g[1].d_time < g[2].d_time && g[2].f_time < g[1].f_time);
    ASSERT("TC-DFS02: timestamps are unique and positive",
           g[0].d_time > 0 && g[0].f_time > g[0].d_time);
    graph_destroy(g, 3);

    /* TC-DFS03: graph with cycle — no infinite recursion */
    g = graph_create(3);
    graph_add_edge(g, 3, 0, 1);
    graph_add_edge(g, 3, 1, 2);
    graph_add_edge(g, 3, 2, 0);
    graph_dfs(g, 3);
    ASSERT("TC-DFS03: all vertices BLACK despite cycle",
           g[0].color == COLOR_BLACK && g[1].color == COLOR_BLACK &&
           g[2].color == COLOR_BLACK);
    graph_destroy(g, 3);

    /* TC-DFS04: disconnected graph — DFS must visit all components */
    g = graph_create(4);
    graph_add_edge(g, 4, 0, 1);
    graph_add_edge(g, 4, 2, 3);
    graph_dfs(g, 4);
    ASSERT("TC-DFS04: all 4 vertices visited (BLACK)",
           g[0].color == COLOR_BLACK && g[1].color == COLOR_BLACK &&
           g[2].color == COLOR_BLACK && g[3].color == COLOR_BLACK);
    ASSERT("TC-DFS04: V2 and V3 have valid timestamps",
           g[2].d_time > 0 && g[3].d_time > 0);
    graph_destroy(g, 4);

    /* TC-E01: cycle C4 (all even degrees, connected) — IS Eulerian */
    g = graph_create(4);
    graph_add_edge(g, 4, 0, 1);
    graph_add_edge(g, 4, 1, 2);
    graph_add_edge(g, 4, 2, 3);
    graph_add_edge(g, 4, 3, 0);
    ASSERT("TC-E01: C4 (cycle of 4) is Eulerian",   graph_is_eulerian(g, 4) == 1);
    graph_destroy(g, 4);

    /* TC-E02: path P3 (0-1-2) — odd-degree vertices, NOT Eulerian */
    g = graph_create(3);
    graph_add_edge(g, 3, 0, 1);
    graph_add_edge(g, 3, 1, 2);
    ASSERT("TC-E02: path P3 is not Eulerian (odd degrees at V0,V2)",
           graph_is_eulerian(g, 3) == 0);
    graph_destroy(g, 3);

    /* TC-E03: disconnected graph — NOT Eulerian regardless of degrees */
    g = graph_create(4);
    graph_add_edge(g, 4, 0, 1);
    graph_add_edge(g, 4, 2, 3);
    ASSERT("TC-E03: disconnected graph is not Eulerian",
           graph_is_eulerian(g, 4) == 0);
    graph_destroy(g, 4);

    SUITE_RESULTS();
}
