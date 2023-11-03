/*
 * WordSumPipeline.c
 *
 */


#include "PipelinePipe.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int num_lines;
int num_words;

// Generate num_words amount of words on each line up to num_lines. Words are of random length.
static void generateWords(void* input, void* output) {
    printf("generateWords: thread %p\n", (void*) pthread_self());
    for (int i = 1; i <= num_lines; i++) {
        for (int j = 1; j <= num_words; j++) {
            int word_length = rand() % 10 + 1;
            char word[word_length];
            printf("generateWords: word_length = %i\n", word_length);
            for (int k = 0; k < word_length; k++) {
                word[k] = rand() % 26 + 97;
            }
            if (!Pipeline_send(output, (void*) &word, sizeof(word))) exit(EXIT_FAILURE);
        }
    }
}

// Count the number of words on each line as a total and print the result
static void sumWordsAndPrint(void* input, void* output) {
    printf("sumWordsAndPrint: thread %p\n", (void*) pthread_self());
    char word[10];
    int result = 0;
    for (int i = 1; i <= num_lines; i++) {
        for (int j = 1; j <= num_words; j++) {
            if (!Pipeline_receive(input, (void*) &word, sizeof(word))) exit (EXIT_FAILURE);
            result++;
        }
    }
    printf("sumWordsAndPrint: result = %i\n", result);
}

static void cleanupExit(Pipeline *p) {
    if (p) {
        Pipeline_free(p);
    }
    exit(EXIT_FAILURE);
}


int main() {
    scanf("%i %i", &num_lines, &num_words);
    printf("Setting up pipeline to calculate the sum of words on %i lines.\n", num_lines);

    Pipeline *p = new_Pipeline();

    if (p == NULL) cleanupExit(p);
    if (!Pipeline_add(p, generateWords)) cleanupExit(p);
    if (!Pipeline_add(p, sumWordsAndPrint)) cleanupExit(p);
    Pipeline_execute(p);

    Pipeline_free(p);
    return 0;
}
