# CS2002 W11-SP

## Overview

In this practical we were asked to design, implement and test a multi-threaded pipeline framework in accordance with the module interface in Pipeline.h

## Usage

To build the main version of my pipeline framework that uses my custom thread safe queue and the examples that use it, run the following command from within the src directory:

```bash
    make
```
To build the second version of my pipeline framework that uses unix pipes and the examples that use it, run the following command from within the src/Pipe_version directory:

```bash
    make 
```

To run the examples, run the following commands along with inputting whatever values you'd like with them from within the src directory:

```bash
    ./SumSquaresPipeline
```

```bash
    ./SievePipeline
```

To clean the build directory, run the following command from within the src or src/Pipe_version directory:

```bash
    make clean
```


## Running tests

To run all the tests for my pipeline framework, run the following command from within the test directory:

```bash
    ./RunAll.sh
```

This shell script runs tests on both the queue version and the pipe version of my pipeline framework.

If you get a permission denied error, run the following command to give the script permission to run:

```bash
    chmod +x RunAll.sh
```

To clean the build directory, run the following command from within the src directory:

```bash
    make clean
```

## Report
A rendered version of my report can be found in the report directory under the name report.pdf