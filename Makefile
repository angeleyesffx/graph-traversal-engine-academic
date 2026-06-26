CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -Isrc -Ilib
TARGET  = graph_search
SRC     = src/queue.c src/graph.c
MAIN    = src/main.c

TESTS   = tests/test_queue \
          tests/test_graph  \
          tests/test_bfs    \
          tests/test_dfs

.PHONY: all test valgrind clean

all: $(TARGET)

$(TARGET): $(SRC) $(MAIN)
	$(CC) $(CFLAGS) -o $@ $^

tests/%: tests/%.c $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

test: $(TESTS)
	@echo ""
	@failed=0; \
	for t in $(TESTS); do \
		echo "--- Running $$t ---"; \
		./$$t || failed=$$((failed + 1)); \
	done; \
	echo ""; \
	if [ $$failed -eq 0 ]; then \
		echo "All test suites passed."; \
	else \
		echo "$$failed suite(s) FAILED."; \
		exit 1; \
	fi

valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes --error-exitcode=1 ./$(TARGET)

clean:
	rm -f $(TARGET) $(TESTS)
