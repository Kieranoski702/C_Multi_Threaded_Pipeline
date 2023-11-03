#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <assert.h>
#include <unistd.h>

#include "../src/Pipe_version/PipelinePipe.h"

#define TEST_QUEUE_CAPACITY 10
#define TEST_BUFFER_SIZE 10

// Thread function that tries to receive a value using unix pipe
void* dequeue_thread(void* arg) {
    PipelineChannel* channel = (PipelineChannel*) arg;
    void* buffer = malloc(sizeof(int));
    *((int*) buffer) = 42;
    size_t size = sizeof(int);
    Pipeline_receive(channel, buffer, size);
    return NULL;
}

// Test that Pipeline_receive() blocks when the queue is empty using unix pipe
void test_pipeline_receive_blockingPipe() {
    PipelineChannel* channel = (PipelineChannel*) malloc(sizeof(PipelineChannel));
    void* buffer = malloc(sizeof(int));
    *((int*) buffer) = 42;
    pthread_t thread;

    // Attempt to receive a value from the empty queue
    pthread_create(&thread, NULL, dequeue_thread, channel);

    usleep(10000); // Sleep for 10 milliseconds

    // Check that the dequeue thread is still blocked on the empty queue
    pthread_cancel(thread);
    void* result;
    pthread_join(thread, &result);
    assert(result == PTHREAD_CANCELED);

    // Clean up
    free(buffer);
    close(channel->fd[0]);
    close(channel->fd[1]);
    free(channel);
    printf("test_pipeline_receive_blockingPipe() passed\n");
}

void SendAndReceiveTestsPipe() {
    test_pipeline_receive_blockingPipe();
}
