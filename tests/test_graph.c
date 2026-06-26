#include <stdio.h>
#include "graph.h"
#include "testrunner.h"

int main(void) {
    printf("=== Graph ADT Tests ===\n");

    /* TC-G01: create minimal graph (BVA: order = 1) */
    Vertex *g = graph_create(1);
    ASSERT("TC-G01: graph_create returns non-NULL",   g != NULL);
    ASSERT("TC-G01: vertex color is WHITE",           g[0].color       == COLOR_WHITE);
    ASSERT("TC-G01: vertex predecessor is PRED_NONE", g[0].predecessor == PRED_NONE);
    ASSERT("TC-G01: vertex dist is DIST_INF",         g[0].dist        == DIST_INF);
    ASSERT("TC-G01: no adjacency list",               g[0].head        == NULL);
    graph_destroy(g, 1);

    /* TC-G02: add valid edge and verify both directions */
    g = graph_create(5);
    ASSERT("TC-G02: add_edge(2,4) returns 1",            graph_add_edge(g, 5, 2, 4) == 1);
    ASSERT("TC-G02: forward edge 2->4 in list",          g[2].head != NULL && g[2].head->dest == 4);
    ASSERT("TC-G02: backward edge 4->2 in list",         g[4].head != NULL && g[4].head->dest == 2);
    ASSERT("TC-G02: edge count is 1",                    graph_edge_count(g, 5) == 1);

    /* TC-G03: invalid edges — equivalence partitioning */
    ASSERT("TC-G03: v1 < 0 rejected",                   graph_add_edge(g, 5, -1,  2) == 0);
    ASSERT("TC-G03: v2 >= order rejected",               graph_add_edge(g, 5,  2,  5) == 0);
    ASSERT("TC-G03: v1 >= order rejected",               graph_add_edge(g, 5,  5,  2) == 0);
    ASSERT("TC-G03: self-loop rejected",                 graph_add_edge(g, 5,  2,  2) == 0);

    /* TC-G04: boundary values — first and last valid vertices */
    ASSERT("TC-G04: add_edge(0, 4) returns 1",           graph_add_edge(g, 5, 0, 4) == 1);
    ASSERT("TC-G04: edge count updated to 2",            graph_edge_count(g, 5) == 2);

    /* TC-G05: degree computation */
    ASSERT("TC-G05: degree of V2 is 1",                  graph_degree(g, 2) == 1);
    ASSERT("TC-G05: degree of isolated V1 is 0",         graph_degree(g, 1) == 0);
    ASSERT("TC-G05: degree of V4 is 2 (edges 2-4, 0-4)", graph_degree(g, 4) == 2);
    graph_destroy(g, 5);

    /* TC-G06: graph_destroy frees without crash (run under valgrind) */
    g = graph_create(3);
    graph_add_edge(g, 3, 0, 1);
    graph_add_edge(g, 3, 1, 2);
    graph_destroy(g, 3);
    ASSERT("TC-G06: destroy completes without crash", 1);

    SUITE_RESULTS();
}
