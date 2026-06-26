# Graph Traversal Engine

[![CI](https://github.com/angeleyesffx/graph-traversal-engine-academic/actions/workflows/ci.yml/badge.svg)](https://github.com/angeleyesffx/graph-traversal-engine-academic/actions/workflows/ci.yml)

Pure C implementation of **BFS** and **DFS** following Cormen et al., *Introduction to Algorithms* (4th ed.), Chapters 22.2–22.3. Includes Eulerian graph verification and a full unit test suite.

---

## Algorithms

| Algorithm | Time     | Space | Reference         |
|-----------|----------|-------|-------------------|
| BFS       | O(V + E) | O(V)  | Cormen Ch. 22.2   |
| DFS       | O(V + E) | O(V)  | Cormen Ch. 22.3   |

**Graph representation:** adjacency list — O(V + E) space, O(deg(v)) edge iteration.

Vertices carry the full Cormen color scheme (`WHITE → GRAY → BLACK`) plus BFS distances, DFS timestamps (`d[v]`, `f[v]`), and predecessors.

---

## Project Structure

```
src/
  queue.h / queue.c   — circular FIFO queue (BFS backbone)
  graph.h / graph.c   — graph ADT, BFS, DFS, Eulerian check
  main.c              — demonstration driver
tests/
  test_queue.c        — queue unit tests  (TC-Q01..TC-Q07)
  test_graph.c        — graph ADT tests   (TC-G01..TC-G06)
  test_bfs.c          — BFS tests         (TC-BFS01..TC-BFS05)
  test_dfs.c          — DFS + Eulerian    (TC-DFS01..TC-E03)
lib/
  testrunner.h        — minimal assertion framework (no dependencies)
archive/
  BuscaLarguraProfundidade.c  — original single-file version
```

---

## Build & Run

```bash
make              # build graph_search
make test         # compile and run all test suites
make valgrind     # memory leak check (requires valgrind, Linux/WSL)
make clean        # remove binaries
```

---

## Sample Graph

The demo driver (`src/main.c`) builds this graph on 10 vertices (V0, V1, V6, V8, V9 are isolated):

```
    V7
    |
V5--V4--V2--V3
        |___|
```

Edges: {2-3, 2-4, 3-4, 3-7, 4-5}

---

## Sample Output

```
Vertices: 10  |  Edges: 5  |  Size |V|+|E|: 15

=== DFS Result (timestamps) ===
Vertex   Color      d      f   Pred
V0           2      1      2     -1
V1           2      3      4     -1
V2           2      5     18     -1
V3           2      6     17      2
V4           2     11     16      3
V5           2     12     13      4
V7           2      7      8      3
...

=== BFS Result (source: V2) ===
Vertex   Color     Dist   Pred
V0           0      INF     -1
V2           2        0     -1
V3           2        1      2
V4           2        1      2
V5           2        2      4
V7           2        2      3

=== Eulerian Check ===
The graph is NOT Eulerian.
```

---

## Eulerian Property

An undirected graph is **Eulerian** iff:
1. Every vertex with non-zero degree belongs to a single connected component.
2. Every vertex has even degree.

V3 has degree 3 (odd) in the demo graph → **not Eulerian**.

---

## Test Suite Design (ISTQB)

Tests apply **Equivalence Partitioning (EP)** and **Boundary Value Analysis (BVA)**. Each test suite is a standalone executable. Exit code `0` = all pass, `1` = at least one failure.

```
$ make test

--- Running tests/test_queue ---
=== Queue Tests ===
  [PASS] TC-Q01: initialized queue is empty
  [PASS] TC-Q06: circular wrap — fill to capacity
  ...
8 tests, 0 failures

--- Running tests/test_dfs ---
=== DFS + Eulerian Tests ===
  [PASS] TC-DFS02: parenthesis theorem V0 contains V1
  [PASS] TC-E01: C4 (cycle of 4) is Eulerian
  ...
All test suites passed.
```

---

## References

- Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2022). *Introduction to Algorithms* (4th ed.). MIT Press.
- ISTQB. (2023). *Certified Tester Foundation Level Syllabus v4.0*.
