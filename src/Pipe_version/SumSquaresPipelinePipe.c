/*
 * SumSquaresPipeline.c
 *
 *  Created on: 26 Mar 2021
 *      Author: jonl
 */


#include "PipelinePipe.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int num_ints;

static void generateInts(void* input, void* output) {
    printf("generateInts: thread %p\n", (void*) pthread_self());
    for (int i = 1; i <= num_ints; i++) {
        if (!Pipeline_send(output, (void*) &i, sizeof(int))) exit(EXIT_FAILURE);
    }
}


static void squareInts(void* input, void* output) {
    printf("squareInts: thread %p\n", (void*) pthread_self());
    for (int i = 1; i <= num_ints; i++) {
        int number;
        if (!Pipeline_receive(input, (void*) &number, sizeof(int))) exit(EXIT_FAILURE);
        int result = number * number;
        if (!Pipeline_send(output, (void*) &result, sizeof(int))) exit(EXIT_FAILURE);
    }
}


static void sumIntsAndPrint(void* input, void* output) {
    printf("sumIntsAndPrint: thread %p\n", (void*) pthread_self());
    int number = 0;
    int result = 0;
    for (int i = 1; i <= num_ints; i++) {
        if (!Pipeline_receive(input, (void*) &number, sizeof(int))) exit (EXIT_FAILURE);
        result += number;
    }
    printf("sumIntsAndPrint: result = %i\n", result);
}

static void cleanupExit(Pipeline *p) {
    if (p) {
        Pipeline_free(p);
    }
    exit(EXIT_FAILURE);
}


int main() {
    scanf("%d", &num_ints);
    printf("Setting up pipeline to calculate the sum of squares of integers 1 to %i.\n", num_ints);

    Pipeline *p = new_Pipeline();

    if (p == NULL) cleanupExit(p);
    if (!Pipeline_add(p, generateInts)) cleanupExit(p);
    if (!Pipeline_add(p, squareInts)) cleanupExit(p);
    if (!Pipeline_add(p, sumIntsAndPrint)) cleanupExit(p);
    Pipeline_execute(p);

    Pipeline_free(p);
    return 0;
}
