#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_CAPACITY 256

typedef enum {
    QUEUE_OK = 0,
    QUEUE_EMPTY,
    QUEUE_FULL
} QueueStatus;

typedef struct {
    int data[QUEUE_CAPACITY];
    int front;
    int back;
} Queue;

void        queue_init    (Queue *q);
int         queue_is_empty(const Queue *q);
int         queue_is_full (const Queue *q);
QueueStatus queue_enqueue (Queue *q, int elem);
QueueStatus queue_dequeue (Queue *q, int *out);

#endif /* QUEUE_H */
