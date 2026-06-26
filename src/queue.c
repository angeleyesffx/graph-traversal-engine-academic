#include "queue.h"

void queue_init(Queue *q) {
    q->front = q->back = 0;
}

int queue_is_empty(const Queue *q) {
    return q->front == q->back;
}

int queue_is_full(const Queue *q) {
    return ((q->back + 1) % QUEUE_CAPACITY) == q->front;
}

QueueStatus queue_enqueue(Queue *q, int elem) {
    if (queue_is_full(q))
        return QUEUE_FULL;
    q->data[q->back] = elem;
    q->back = (q->back + 1) % QUEUE_CAPACITY;
    return QUEUE_OK;
}

QueueStatus queue_dequeue(Queue *q, int *out) {
    if (queue_is_empty(q))
        return QUEUE_EMPTY;
    *out = q->data[q->front];
    q->front = (q->front + 1) % QUEUE_CAPACITY;
    return QUEUE_OK;
}
