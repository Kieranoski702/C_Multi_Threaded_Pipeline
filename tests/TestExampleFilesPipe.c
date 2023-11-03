#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "TestExampleFilesPipe.h"
#include "../src/Pipe_version/PipelinePipe.h"

// Run SumSquaresPipeline file with example input.
void testSumSquaresPipelinePipe() {
    freopen("../tests/TestFiles/Output.txt", "w", stdout);
    int status = system("cd ../src/Pipe_version && make && ./SumSquaresPipelinePipe < ../../tests/TestFiles/SumSquaresPipelineInput.txt");
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
    printf("testSumSquaresPipelinePipe passed\n");
}

// Run SumSquaresPipeline file with example large input. 
void testSumSquaresPipelineLargePipe() {
    freopen("../tests/TestFiles/Output.txt", "w", stdout);
    int status = system("cd ../src/Pipe_version && make && ./SumSquaresPipelinePipe < ../../tests/TestFiles/SumSquaresPipelineLargeInput.txt");
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
    printf("testSumSquaresPipelineLargePipe passed\n");
}

// Run SievePipeline file with example input.
void testSievePipelinePipe() {
    freopen("../tests/TestFiles/Output.txt", "w", stdout);
    int status = system("cd ../src/Pipe_version && make && ./SievePipelinePipe < ../../tests/TestFiles/SievePipelineInput.txt");
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
    printf("testSievePipelinePipe passed\n");
}

// Run SievePipeline file with example large input.
void testSievePipelineLargePipe() {
    freopen("../tests/TestFiles/Output.txt", "w", stdout);
    int status = system("cd ../src/Pipe_version && make && ./SievePipelinePipe < ../../tests/TestFiles/SievePipelineLargeInput.txt");
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
    printf("testSievePipelineLargePipe passed\n");
}

void exampleFileTestsPipe() {
    testSumSquaresPipelinePipe();
    testSumSquaresPipelineLargePipe();
    testSievePipelinePipe();
    testSievePipelineLargePipe();
}