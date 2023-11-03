#include "Queue.h"
#include <stdlib.h>
#include <string.h>

PipelineQueue* new_PipelineQueue() {
    PipelineQueue* queue = (PipelineQueue*) malloc(sizeof(PipelineQueue));
    queue->head = NULL;
    queue->tail = NULL;
    pthread_mutex_init(&queue->lock, NULL);
    pthread_cond_init(&queue->not_empty, NULL);
    return queue;
}

void PipelineQueue_enqueue(PipelineQueue* queue, void* data, size_t size) {
    PipelineQueueNode* node = (PipelineQueueNode*) malloc(sizeof(PipelineQueueNode));
    node->data = malloc(size);
    memcpy(node->data, data, size);
    node->size = size;
    node->next = NULL;

    pthread_mutex_lock(&queue->lock);
    if (queue->tail) {
        queue->tail->next = node;
        queue->tail = node;
    } else {
        queue->head = node;
        queue->tail = node;
    }
    pthread_cond_signal(&queue->not_empty);
    pthread_mutex_unlock(&queue->lock);
}

bool PipelineQueue_dequeue(PipelineQueue* queue, void* data, size_t size) {
    pthread_mutex_lock(&queue->lock);
    while (!queue->head) {
        pthread_cond_wait(&queue->not_empty, &queue->lock);
    }
    PipelineQueueNode* node = queue->head;
    if (node->size > size) {
        pthread_mutex_unlock(&queue->lock);
        return false;
    }
    memcpy(data, node->data, node->size);
    queue->head = node->next;
    if (!queue->head) {
        queue->tail = NULL;
    }
    free(node->data);
    free(node);
    pthread_mutex_unlock(&queue->lock);
    return true;
}