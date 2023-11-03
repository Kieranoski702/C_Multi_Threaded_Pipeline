#!/usr/bin/env bash

# change to the src directory
cd ../src
# Run make tests to compile the tests for the custom queue version
make tests
# Run the tests
./RunTests
# Clean up the tests
make clean
# Run make tests to compile the tests for the unix pipe version
make testsPipe
# Run the tests
./RunTestsPipe
# Clean up the tests
make clean