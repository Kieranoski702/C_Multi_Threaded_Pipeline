#include "TestExampleFiles.h"
#include "TestSendAndReceive.h"
#include "TestAdd.h"
#include "TestExampleFilesPipe.h"
#include "TestSendAndReceivePipe.h"
#include "TestAddPipe.h"
#include <stdio.h>

// Entry point for the test suite
int main() {
    printf("Starting tests for pipe version of the pipeline framework...\n");
    exampleFileTestsPipe();
    printf("All example file tests passed for pipe version of the pipeline framework\n");
    SendAndReceiveTestsPipe();
    printf("All send and receive tests passed for pipe version of the pipeline framework\n");
    addTestsPipe();
    printf("All add tests passed for pipe version of the pipeline framework\n");
    printf("All tests passed for unix pipe version of the pipeline framework\n");
    printf("All tests passed\n");
    return 0;
}