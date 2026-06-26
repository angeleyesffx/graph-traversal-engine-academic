#include <stdio.h>
#include "graph.h"
#include "testrunner.h"

int main(void) {
    printf("=== BFS Tests ===\n");

    /* TC-BFS01: single vertex (BVA minimum) */
    Vertex *g = graph_create(1);
    graph_bfs(g, 1, 0);
    ASSERT("TC-BFS01: source dist = 0",          g[0].dist        == 0);
    ASSERT("TC-BFS01: source color = BLACK",     g[0].color       == COLOR_BLACK);
    ASSERT("TC-BFS01: source predecessor = NONE",g[0].predecessor == PRED_NONE);
    graph_destroy(g, 1);

    /* TC-BFS02: linear path 0-1-2-3, source = 0
       Expected distances: V0=0, V1=1, V2=2, V3=3 */
    g = graph_create(4);
    graph_add_edge(g, 4, 0, 1);
    graph_add_edge(g, 4, 1, 2);
    graph_add_edge(g, 4, 2, 3);
    graph_bfs(g, 4, 0);
    ASSERT("TC-BFS02: V0 dist = 0",  g[0].dist == 0);
    ASSERT("TC-BFS02: V1 dist = 1",  g[1].dist == 1);
    ASSERT("TC-BFS02: V2 dist = 2",  g[2].dist == 2);
    ASSERT("TC-BFS02: V3 dist = 3",  g[3].dist == 3);
    ASSERT("TC-BFS02: V1 pred = V0", g[1].predecessor == 0);
    ASSERT("TC-BFS02: V2 pred = V1", g[2].predecessor == 1);
    ASSERT("TC-BFS02: V3 pred = V2", g[3].predecessor == 2);
    ASSERT("TC-BFS02: all vertices BLACK",
           g[0].color == COLOR_BLACK && g[1].color == COLOR_BLACK &&
           g[2].color == COLOR_BLACK && g[3].color == COLOR_BLACK);
    graph_destroy(g, 4);

    /* TC-BFS03: disconnected graph {0,1} and {2,3}, source = 0
       Unreachable component must remain WHITE with dist = INF */
    g = graph_create(4);
    graph_add_edge(g, 4, 0, 1);
    graph_add_edge(g, 4, 2, 3);
    graph_bfs(g, 4, 0);
    ASSERT("TC-BFS03: V0 reached (BLACK)",   g[0].color == COLOR_BLACK);
    ASSERT("TC-BFS03: V1 reached (BLACK)",   g[1].color == COLOR_BLACK);
    ASSERT("TC-BFS03: V2 not reached (WHITE)", g[2].color == COLOR_WHITE);
    ASSERT("TC-BFS03: V3 not reached (WHITE)", g[3].color == COLOR_WHITE);
    ASSERT("TC-BFS03: V2 dist = INF",         g[2].dist == DIST_INF);
    ASSERT("TC-BFS03: V3 dist = INF",         g[3].dist == DIST_INF);
    graph_destroy(g, 4);

    /* TC-BFS04: BFS from last vertex (BVA — source = order - 1) */
    g = graph_create(3);
    graph_add_edge(g, 3, 0, 1);
    graph_add_edge(g, 3, 1, 2);
    graph_bfs(g, 3, 2);
    ASSERT("TC-BFS04: V2 (source) dist = 0", g[2].dist == 0);
    ASSERT("TC-BFS04: V1 dist = 1",          g[1].dist == 1);
    ASSERT("TC-BFS04: V0 dist = 2",          g[0].dist == 2);
    graph_destroy(g, 3);

    /* TC-BFS05: BFS reinitializes state on repeated calls */
    g = graph_create(3);
    graph_add_edge(g, 3, 0, 1);
    graph_add_edge(g, 3, 1, 2);
    graph_bfs(g, 3, 0);
    graph_bfs(g, 3, 2);  /* second call, different source */
    ASSERT("TC-BFS05: re-run resets V0 dist to 2", g[0].dist == 2);
    ASSERT("TC-BFS05: re-run source (V2) dist = 0", g[2].dist == 0);
    graph_destroy(g, 3);

    SUITE_RESULTS();
}
