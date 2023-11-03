/*
 * SievePipeline.c
 *
 *  Created on: 26 Mar 2021
 *      Author: jonl
 */


#include "PipelinePipe.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>


static int max_ints;
static int number_of_primes;

static void generateInts(void* input, void* output) {
    printf("generateInts: thread %p\n", (void*) pthread_self());
    int i = 0;
    for (i = 2; i <= max_ints; i++) {
        Pipeline_send(output, &i, sizeof(int));
    }
    i = -1;
    Pipeline_send(output, &i, sizeof(int)); // write -1 to indicate end
}

/*
 * Treats the first number it gets as a prime number prints it out and then
 * sieves out multiples of that prime by only sending on numbers that are
 * not multiples of that prime to the next stage in the pipeline.
 */
static void sieveInts(void* input, void* output) {
    int prime, number = 0;
    Pipeline_receive(input, &prime, sizeof(int));
    printf("sieveInts: thread %p: prime = %i\n", (void*) pthread_self(), prime);
    if (prime == -1) { // this means we have already got to the end
        Pipeline_send(output, &prime, sizeof(int)); // pass on -1 terminator to child sieve stage
    } else {
        while (number != -1) {
            Pipeline_receive(input, &number, sizeof(int));
            if (number % prime != 0) {
                Pipeline_send(output, &number, sizeof(int));
            }
        }
    }
}



static void cleanupExit(Pipeline *p) {
    if (p) {
        Pipeline_free(p);
    }
    exit(EXIT_FAILURE);
}

int main() {
    scanf("%i %i", &number_of_primes, &max_ints);
    printf("Setting up pipeline to sieve out the first %i prime numbers up to %i\n", number_of_primes, max_ints);

    Pipeline *p = new_Pipeline();
    if (p == NULL) cleanupExit(p);
    if (!Pipeline_add(p, generateInts)) cleanupExit(p);
    for (int i = 0; i < number_of_primes; i++) {
        if (!Pipeline_add(p, sieveInts)) cleanupExit(p);
    }
    Pipeline_execute(p);

    Pipeline_free(p);
    return 0;
}
