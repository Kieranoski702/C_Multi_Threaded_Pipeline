#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <assert.h>
#include <unistd.h>

#include "../src/Pipeline.h"
#include "../src/Queue.h"

#define TEST_QUEUE_CAPACITY 10
#define TEST_BUFFER_SIZE 10

// Thread function that tries to receive a value from the queue
void* dequeue_thread(void* arg) {
    PipelineQueue* queue = (PipelineQueue*) arg;
    void* buffer = malloc(sizeof(int));
    *((int*) buffer) = 42;
    size_t size = sizeof(int);
    Pipeline_receive(queue, buffer, size);
    return NULL;
}

// Test that Pipeline_receive() blocks when the queue is empty
void test_pipeline_receive_blocking() {
    PipelineQueue* queue = new_PipelineQueue();
    void* buffer = malloc(sizeof(int));
    *((int*) buffer) = 42;
    pthread_t thread;

    // Attempt to receive a value from the empty queue
    pthread_create(&thread, NULL, dequeue_thread, queue);

    usleep(10000); // Sleep for 10 milliseconds

    // Check that the dequeue thread is still blocked on the empty queue
    pthread_cancel(thread);
    void* result;
    pthread_join(thread, &result);
    assert(result == PTHREAD_CANCELED);

    // Clean up
    free(buffer);
    free(queue);
    printf("test_pipeline_receive_blocking() passed\n");
}

// Test that Pipeline_send() and Pipeline_receive() work together
void test_pipeline_send_receive() {
    PipelineQueue* channel = new_PipelineQueue();
    int data = 42;
    size_t data_size = sizeof(data);
    assert(Pipeline_send(channel, &data, data_size) == true);
    int received_data = 0;
    assert(Pipeline_receive(channel, &received_data, data_size) == true);
    assert(received_data == data);
    free(channel);
    printf("test_pipeline_send_receive() passed\n");
}


void SendAndReceiveTests() {
    test_pipeline_send_receive();
    test_pipeline_receive_blocking();
}