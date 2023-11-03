#ifndef PIPELINEQUEUE_H_
#define PIPELINEQUEUE_H_

#include <stdbool.h>
#include <pthread.h>

typedef struct PipelineQueueNode {
    void* data;
    size_t size;
    struct PipelineQueueNode* next;
} PipelineQueueNode;

typedef struct PipelineQueue {
    PipelineQueueNode* head;
    PipelineQueueNode* tail;
    pthread_mutex_t lock;
    pthread_cond_t not_empty;
} PipelineQueue;

PipelineQueue* new_PipelineQueue();
void PipelineQueue_enqueue(PipelineQueue* queue, void* data, size_t size);
bool PipelineQueue_dequeue(PipelineQueue* queue, void* data, size_t size);

#endif /* PIPELINEQUEUE_H_ */
