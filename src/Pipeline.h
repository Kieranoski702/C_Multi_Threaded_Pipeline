/*
 * Pipeline.h
 *
 *  Created on: 26 Mar 2021
 *      Author: jonl
 */

#ifndef PIPELINE_H_
#define PIPELINE_H_

#include <stdbool.h>
#include <pthread.h>

#include "Queue.h"

#define MAX_THREADS_IN_POOL 1000
#define INITIAL_BACKOFF_TIME 100 // microseconds
#define MAX_BACKOFF_TIME 1000000 // microseconds


typedef void (*Function)(void* input, void* output);

typedef struct PipelineStage {
    Function function;
    struct PipelineStage* next_stage;
    pthread_t thread;
    PipelineQueue* input_channel;
    PipelineQueue* output_channel;
} PipelineStage;

typedef struct Pipeline {
    PipelineStage* head_stage;
    PipelineStage* tail_stage;
} Pipeline;


/*
 * Creates a new empty processing pipeline.
 * @return a pointer to a new empty pipeline (with no stages) upon success and otherwise NULL.
 */
Pipeline* new_Pipeline();


/*
 * Adds a new stage to the pipeline with the specified pipeline function.
 * @param this the pipeline to use.
 * @param f pointer to pipeline function to use.
 * @return true on success and false if unable to add the new stage.
 *
 */
bool Pipeline_add(Pipeline* this, Function f);


/*
 * Executes the specified pipeline.
 * @param this the pipeline to use.
 */
void Pipeline_execute(Pipeline* this);


/*
 * Frees memory associated with the pipeline.
 * @param this the pipeline to use.
 */
void Pipeline_free(Pipeline* this);


/*
 * Sends a value located in the specified buffer and of specified size (in bytes) on a communication channel.
 * This is to permit a pipeline stage to send values to another stage.
 * @param channel pointer to a communication channel of your own choice.
 * @param buffer pointer to the buffer containing the value to send.
 * @param size the number of bytes to send.
 * @return true on success and false otherwise (if the channel is invalid for example).
 */
bool Pipeline_send(void* channel, void* buffer, size_t size);


/*
 * Receives a value of specified size (in bytes) from a communication channel and stores the result in the specified buffer.
 * This is to permit a pipeline stage to receive values from another stage.
 * @param channel pointer to a communication channel of your own choice.
 * @param buffer pointer to the buffer where the value will be stored upon receipt.
 * @param size the number of bytes to receive.
 * @return true on success and false otherwise (if the channel is invalid for example).
 */
bool Pipeline_receive(void* channel, void* buffer, size_t size);




#endif /* PIPELINE_H_ */
