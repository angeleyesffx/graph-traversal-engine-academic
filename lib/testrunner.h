#ifndef TESTRUNNER_H
#define TESTRUNNER_H

#include <stdio.h>

static int _tr_run    = 0;
static int _tr_failed = 0;

#define ASSERT(desc, cond) do {                                            \
    _tr_run++;                                                              \
    if (cond) {                                                             \
        printf("  [PASS] %s\n", (desc));                                   \
    } else {                                                                \
        printf("  [FAIL] %s  (%s:%d)\n", (desc), __FILE__, __LINE__);     \
        _tr_failed++;                                                       \
    }                                                                       \
} while (0)

#define SUITE_RESULTS() do {                                               \
    printf("\n%d tests, %d failures\n\n", _tr_run, _tr_failed);           \
    return _tr_failed > 0 ? 1 : 0;                                        \
} while (0)

#endif /* TESTRUNNER_H */
