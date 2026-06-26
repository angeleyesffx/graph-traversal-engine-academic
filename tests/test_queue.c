#include <stdio.h>
#include "queue.h"
#include "testrunner.h"

int main(void) {
    printf("=== Queue Tests ===\n");

    Queue q;

    /* TC-Q01: init */
    queue_init(&q);
    ASSERT("TC-Q01: initialized queue is empty",    queue_is_empty(&q));
    ASSERT("TC-Q01: initialized queue is not full", !queue_is_full(&q));

    /* TC-Q02: enqueue one element */
    ASSERT("TC-Q02: enqueue returns QUEUE_OK",           queue_enqueue(&q, 42) == QUEUE_OK);
    ASSERT("TC-Q02: queue is not empty after enqueue",   !queue_is_empty(&q));

    /* TC-Q03: dequeue — correct value, queue empties */
    int out = -1;
    ASSERT("TC-Q03: dequeue returns QUEUE_OK",           queue_dequeue(&q, &out) == QUEUE_OK);
    ASSERT("TC-Q03: dequeued value is correct",          out == 42);
    ASSERT("TC-Q03: queue is empty after dequeue",       queue_is_empty(&q));

    /* TC-Q04: dequeue from empty queue — must not crash */
    ASSERT("TC-Q04: dequeue from empty returns QUEUE_EMPTY",
           queue_dequeue(&q, &out) == QUEUE_EMPTY);

    /* TC-Q05: FIFO order preserved */
    queue_enqueue(&q, 10);
    queue_enqueue(&q, 20);
    queue_enqueue(&q, 30);
    queue_dequeue(&q, &out); ASSERT("TC-Q05: FIFO first  element is 10", out == 10);
    queue_dequeue(&q, &out); ASSERT("TC-Q05: FIFO second element is 20", out == 20);
    queue_dequeue(&q, &out); ASSERT("TC-Q05: FIFO third  element is 30", out == 30);

    /* TC-Q06: circular wrap — fill to capacity */
    queue_init(&q);
    for (int i = 0; i < QUEUE_CAPACITY - 1; i++)
        queue_enqueue(&q, i);
    ASSERT("TC-Q06: queue is full at capacity - 1",      queue_is_full(&q));
    ASSERT("TC-Q06: enqueue on full returns QUEUE_FULL", queue_enqueue(&q, 99) == QUEUE_FULL);

    /* TC-Q07: circular wrap — dequeue after wrap */
    queue_dequeue(&q, &out);
    ASSERT("TC-Q07: can enqueue after freeing one slot", queue_enqueue(&q, 99) == QUEUE_OK);
    ASSERT("TC-Q07: queue is full again",                queue_is_full(&q));

    SUITE_RESULTS();
}
