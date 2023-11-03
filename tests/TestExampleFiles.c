#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "TestExampleFiles.h"
#include "../src/Pipeline.h"


// Run SumSquaresPipeline file with example input.
void testSumSquaresPipeline() {
    freopen("../tests/TestFiles/Output.txt", "w", stdout);
    int status = system("cd ../src/ && make && ./SumSquaresPipeline < ../tests/TestFiles/SumSquaresPipelineInput.txt");
    assert(status == 0);
    char expected[] = "sumIntsAndPrint: result = 385\n";
    char actual[1000] = "";  // initialize actual string
    FILE *fp = fopen("../tests/TestFiles/Output.txt", "r");
    char line[1000];
    while (fgets(line, sizeof(line), fp)) {  // read file line by line
        if (strcmp(line, "\n") != 0) {  // skip blank lines
            strcpy(actual, line);  // copy non-blank line to actual string
        }
    }
    assert(strcmp(expected, actual) == 0);
    fclose(fp);
    freopen("/dev/tty", "w", stdout);
    printf("testSumSquaresPipeline passed\n");
}

// Run SumSquaresPipeline file with example large input. 
void testSumSquaresPipelineLarge() {
    freopen("../tests/TestFiles/Output.txt", "w", stdout);
    int status = system("cd ../src/ && make && ./SumSquaresPipeline < ../tests/TestFiles/SumSquaresPipelineLargeInput.txt");
    assert(status == 0);
    char expected[] = "sumIntsAndPrint: result = 1126125250\n";
    char actual[1000] = "";  // initialize actual string
    FILE *fp = fopen("../tests/TestFiles/Output.txt", "r");
    char line[1000];
    while (fgets(line, sizeof(line), fp)) {  // read file line by line
        if (strcmp(line, "\n") != 0) {  // skip blank lines
            strcpy(actual, line);  // copy non-blank line to actual string
        }
    }
    assert(strcmp(expected, actual) == 0);
    fclose(fp);
    freopen("/dev/tty", "w", stdout);
    printf("testSumSquaresPipelineLarge passed\n");
}

// Run SievePipeline file with example input.
void testSievePipeline() {
    freopen("../tests/TestFiles/Output.txt", "w", stdout);
    int status = system("cd ../src/ && make && ./SievePipeline < ../tests/TestFiles/SievePipelineInput.txt");
    assert(status == 0);
    char actual[1000] = "";  // initialize actual string
    FILE *fp = fopen("../tests/TestFiles/Output.txt", "r");
    char line[1000];
    while (fgets(line, sizeof(line), fp)) {  // read file line by line
        if (strcmp(line, "\n") != 0) {  // skip blank lines
            strcpy(actual, line);  // copy non-blank line to actual string
        }
    }
    // Expected out is "sieveInts: thread %p: prime = 11\n" where %p is a pointer to the thread. 
    // Due to the pointer being different each time, we can't check for the exact string. 
    // Instead, we check if the actual string contains the expected prefix and suffix.
    assert(strstr(actual, "sieveInts: thread ") != NULL); // check if the actual string contains the expected prefix
    assert(strstr(actual, ": prime = 11\n") != NULL); // check if the actual string contains the expected suffix
    fclose(fp);
    freopen("/dev/tty", "w", stdout);
    printf("testSievePipeline passed\n");
}

// Run SievePipeline file with example large input.
void testSievePipelineLarge() {
    freopen("../tests/TestFiles/Output.txt", "w", stdout);
    int status = system("cd ../src/ && make && ./SievePipeline < ../tests/TestFiles/SievePipelineLargeInput.txt");
    assert(status == 0);
    char actual[1000] = "";  // initialize actual string
    FILE *fp = fopen("../tests/TestFiles/Output.txt", "r");
    char line[1000];
    while (fgets(line, sizeof(line), fp)) {  // read file line by line
        if (strcmp(line, "\n") != 0) {  // skip blank lines
            strcpy(actual, line);  // copy non-blank line to actual string
        }
    }
    // Expected out is "sieveInts: thread %p: prime = 104729\n" where %p is a pointer to the thread. 
    // Due to the pointer being different each time, we can't check for the exact string. 
    // Instead, we check if the actual string contains the expected prefix and suffix.
    assert(strstr(actual, "sieveInts: thread ") != NULL); // check if the actual string contains the expected prefix
    assert(strstr(actual, ": prime = 104729\n") != NULL); // check if the actual string contains the expected suffix
    fclose(fp);
    freopen("/dev/tty", "w", stdout);
    printf("testSievePipelineLarge passed\n");
}

// Run WordSumPipeline file with example input.
void testWordSumPipeline() {
    freopen("../tests/TestFiles/Output.txt", "w", stdout);
    int status = system("cd ../src/ && make && ./WordSumPipeline < ../tests/TestFiles/WordSumPipelineInput.txt");
    assert(status == 0);
    char expected[] = "sumWordsAndPrint: result = 10\n";
    char actual[1000] = "";  // initialize actual string
    FILE *fp = fopen("../tests/TestFiles/Output.txt", "r");
    char line[1000];
    // Get the last line of the file
    while (fgets(line, sizeof(line), fp)) {  // read file line by line
        if (strcmp(line, "\n") != 0) {  // skip blank lines
            strcpy(actual, line);  // copy non-blank line to actual string
        }
    }
    assert(strcmp(expected, actual) == 0);
    fclose(fp);
    freopen("/dev/tty", "w", stdout);
    printf("testWordSumPipeline passed\n");
}

// Run WordSumPipeline file with example large input.
void testWordSumPipelineLarge() {
    freopen("../tests/TestFiles/Output.txt", "w", stdout);
    int status = system("cd ../src/ && make && ./WordSumPipeline < ../tests/TestFiles/WordSumPipelineLargeInput.txt");
    assert(status == 0);
    char expected[] = "sumWordsAndPrint: result = 100000\n";
    char actual[1000] = "";  // initialize actual string
    FILE *fp = fopen("../tests/TestFiles/Output.txt", "r");
    char line[1000];
    // Get the last line of the file
    while (fgets(line, sizeof(line), fp)) {  // read file line by line
        if (strcmp(line, "\n") != 0) {  // skip blank lines
            strcpy(actual, line);  // copy non-blank line to actual string
        }
    }
    assert(strcmp(expected, actual) == 0);
    fclose(fp);
    freopen("/dev/tty", "w", stdout);
    printf("testWordSumPipelineLarge passed\n");
}

void exampleFileTests() {
    testSumSquaresPipeline();
    testSumSquaresPipelineLarge();
    testSievePipeline();
    testSievePipelineLarge();
    testWordSumPipeline();
    testWordSumPipelineLarge();
}