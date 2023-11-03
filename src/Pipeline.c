/*
 * Pipeline.c
 *
 *  Created on: 26 Mar 2021
 *      Author: jonl
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <semaphore.h>

#include "Pipeline.h"
#include "Queue.h"

static sem_t thread_pool_semaphore;
static int num_threads_in_use = 0;

static void* PipelineStage_run(void* arg) {
    PipelineStage* stage = (PipelineStage*) arg;
    stage->function(stage->input_channel, stage->output_channel);
    sem_post(&thread_pool_semaphore);
    num_threads_in_use--;
    return NULL;
}

/*
 * Creates a new thread for the specified stage, with a backoff strategy if the system is low on memory.
 */
static void create_thread_with_backoff(PipelineStage* stage) {
    int backoff_time = INITIAL_BACKOFF_TIME;
    int num_attempts = 0;
    while (true) {
        if (pthread_create(&stage->thread, NULL, PipelineStage_run, stage) == 0) {
            return; // thread created successfully
        }
        perror("pthread_create");
        usleep(backoff_time);
        backoff_time *= 2;
        if (backoff_time > MAX_BACKOFF_TIME) {
            backoff_time = MAX_BACKOFF_TIME;
            num_attempts++;
            if (num_attempts > 5) {
                fprintf(stderr, "Unable to create thread after 10 attempts. Exiting.\n");
                exit(1);
            }
        }
    }
}


/*
 * Creates a new empty processing pipeline.
 * @return a pointer to a new empty pipeline (with no stages) upon success and otherwise NULL.
 */
Pipeline* new_Pipeline() {
    Pipeline* pipeline = (Pipeline*) malloc(sizeof(Pipeline));
    pipeline->head_stage = NULL;
    pipeline->tail_stage = NULL;
    sem_init(&thread_pool_semaphore, 0, MAX_THREADS_IN_POOL);
    return pipeline;
}

/*
 * Adds a new stage to the pipeline with the specified pipeline function.
 * @param this the pipeline to use.
 * @param f pointer to pipeline function to use.
 * @return true on success and false if unable to add the new stage.
 *
 */
bool Pipeline_add(Pipeline* this, Function f) {
    PipelineStage* stage = (PipelineStage*) malloc(sizeof(PipelineStage));
    if (!stage) return false;
    stage->function = f;
    stage->next_stage = NULL;
    if (this->tail_stage) {
        this->tail_stage->next_stage = stage;
        this->tail_stage = stage;
    } else {
        this->head_stage = stage;
        this->tail_stage = stage;
    }
    return true;
}

/*
 * Executes the specified pipeline. Do not assume input channel is null for first stage or output channel is null for last stage.
 * @param this the pipeline to use.
 */
void Pipeline_execute(Pipeline* this) {
    PipelineStage* stage = this->head_stage;
    PipelineQueue* prev_channel = NULL;
    while (stage) {
        // Create a new channel for this stage
        PipelineQueue* channel = new_PipelineQueue();
        // Set up the input channel for this stage
        if (prev_channel) {
            stage->input_channel = prev_channel;
        } else {
            stage->input_channel = NULL;
        }
        // Set up the output channel for this stage
        if (stage->next_stage) {
            stage->output_channel = channel;
        } else {
            stage->output_channel = NULL;
        }
        // Check if there are any threads available
        sem_wait(&thread_pool_semaphore);
        num_threads_in_use++;
        // Create a thread for this stage
        create_thread_with_backoff(stage);
        if (stage->next_stage) {
            pthread_detach(stage->thread);
        }
        // Move on to the next stage
        prev_channel = channel;
        stage = stage->next_stage;
    }
    // Wait for all threads to finish
    stage = this->tail_stage;
    pthread_join(stage->thread, NULL);
    // Free the last channel
    pthread_mutex_destroy(&prev_channel->lock);
    pthread_cond_destroy(&prev_channel->not_empty);
    free(prev_channel);
}
/*
 * Frees memory associated with the pipeline.
 * @param this the pipeline to use.
 */
void Pipeline_free(Pipeline* this) {
    PipelineStage* stage = this->head_stage;
    while (stage) {
        PipelineStage* next_stage = stage->next_stage;
        free(stage->input_channel);
        free(stage);
        stage = next_stage;
    }
    free(this);
}

/*
 * Sends a value located in the specified buffer and of specified size (in bytes) on a communication channel.
 * This is to permit a pipeline stage to send values to another stage.
 * @param channel pointer to a communication channel of your own choice.
 * @param buffer pointer to the buffer containing the value to send.
 * @param size the number of bytes to send.
 * @return true on success and false otherwise (if the channel is invalid for example).
 */
bool Pipeline_send(void* channel, void* buffer, size_t size) {
    if (channel == NULL) {
        return true; // nothing to send, return true to indicate success
    }
    PipelineQueue_enqueue(channel, buffer, size);
    return true;
}

/*
 * Receives a value of specified size (in bytes) from a communication channel and stores the result in the specified buffer.
 * This is to permit a pipeline stage to receive values from another stage.
 * @param channel pointer to a communication channel of your own choice.
 * @param buffer pointer to the buffer where the value will be stored upon receipt.
 * @param size the number of bytes to receive.
 * @return true on success and false otherwise (if the channel is invalid for example).
 */
bool Pipeline_receive(void* channel, void* buffer, size_t size) {
    if (channel == NULL) {
        return true; // nothing to receive, return true to indicate success
    }
    PipelineQueue_dequeue(channel, buffer, size);
    return true;
}