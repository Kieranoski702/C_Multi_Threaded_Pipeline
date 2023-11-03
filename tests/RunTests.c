#include "TestExampleFiles.h"
#include "TestSendAndReceive.h"
#include "TestAdd.h"
#include "TestExampleFilesPipe.h"
#include "TestSendAndReceivePipe.h"
#include "TestAddPipe.h"
#include <stdio.h>

// Entry point for the test suite
int main() {
    printf("Starting tests...\n");
    printf("Starting example file tests...\n");
    exampleFileTests();
    printf("All example file tests passed\n");
    printf("Starting send and receive tests...\n");
    SendAndReceiveTests();
    printf("All send and receive tests passed\n");
    printf("Starting add tests...\n");
    addTests();
    printf("All add tests passed\n");
    printf("All tests passed for custom queue version of the pipeline framework\n");
    printf("All tests passed\n");
    return 0;
}