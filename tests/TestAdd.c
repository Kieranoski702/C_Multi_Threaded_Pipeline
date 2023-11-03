#include <assert.h>
#include <stdio.h>


#include "../src/Pipeline.h"
#include "TestAdd.h"

void test_pipeline_add() {
    Pipeline* pipeline = new_Pipeline();
    bool result = Pipeline_add(pipeline, NULL);
    assert(result == true && "Pipeline_add should return true");
    assert(pipeline->head_stage != NULL && "Pipeline_add should add a new stage");
    assert(pipeline->tail_stage == pipeline->head_stage && "Pipeline_add should set tail_stage when adding first stage");

    Pipeline_add(pipeline, NULL);
    assert(pipeline->tail_stage != pipeline->head_stage && "Pipeline_add should set tail_stage when adding subsequent stages");

    Pipeline_free(pipeline);
    printf("test_pipeline_add passed\n");
}

void addTests() {
    test_pipeline_add();
}