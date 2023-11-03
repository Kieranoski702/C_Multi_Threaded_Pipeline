

CC = clang
RM = rm -f
DFLAG = -g
GFLAGS = -Wall -Wextra
CFLAGS = $(DFLAG) $(GFLAGS) -c
LFLAGS = $(DFLAG) $(GFLAGS) -pthread

all: SumSquaresPipeline SievePipeline WordSumPipeline

SumSquaresPipeline: SumSquaresPipeline.o Pipeline.o Queue.o
	$(CC) $(LFLAGS) SumSquaresPipeline.o Pipeline.o Queue.o -o SumSquaresPipeline

SievePipeline: SievePipeline.o Pipeline.o Queue.o
	$(CC) $(LFLAGS) SievePipeline.o Pipeline.o Queue.o -o SievePipeline

WordSumPipeline: WordSumPipeline.o Pipeline.o Queue.o
	$(CC) $(LFLAGS) WordSumPipeline.o Pipeline.o Queue.o -o WordSumPipeline

SievePipeline.o: SievePipeline.c
	$(CC) $(CFLAGS) SievePipeline.c

SumSquaresPipeline.o: SumSquaresPipeline.c
	$(CC) $(CFLAGS) SumSquaresPipeline.c

WordSumPipeline.o: WordSumPipeline.c
	$(CC) $(CFLAGS) WordSumPipeline.c


Pipeline.o: Pipeline.c Pipeline.h Queue.h
	$(CC) $(CFLAGS) Pipeline.c

Queue.o: Queue.c Queue.h
	$(CC) $(CFLAGS) Queue.c

tests: RunTests.o TestFileExamples.o TestSendAndReceive.o TestAdd.o Pipeline.o Queue.o
	$(CC) $(LFLAGS) RunTests.o TestExampleFiles.o TestSendAndReceive.o TestAdd.o Pipeline.o Queue.o -o RunTests

RunTests.o: ../tests/RunTests.c
	$(CC) $(CFLAGS) ../tests/RunTests.c

TestFileExamples.o: ../tests/TestExampleFiles.c Pipeline.h Queue.h
	$(CC) $(CFLAGS) ../tests/TestExampleFiles.c

TestSendAndReceive.o: ../tests/TestSendAndReceive.c Pipeline.h Queue.h
	$(CC) $(CFLAGS) ../tests/TestSendAndReceive.c

TestAdd.o: ../tests/TestAdd.c Pipeline.h Queue.h
	$(CC) $(CFLAGS) ../tests/TestAdd.c

testsPipe: RunTestsPipe.o TestFileExamplesPipe.o TestSendAndReceivePipe.o TestAddPipe.o PipelinePipe.o
	$(CC) $(LFLAGS) RunTestsPipe.o TestExampleFilesPipe.o TestSendAndReceivePipe.o TestAddPipe.o PipelinePipe.o -o RunTestsPipe

RunTestsPipe.o: ../tests/RunTestsPipe.c
	$(CC) $(CFLAGS) ../tests/RunTestsPipe.c

TestFileExamplesPipe.o: ../tests/TestExampleFilesPipe.c ./Pipe_version/PipelinePipe.h
	$(CC) $(CFLAGS) ../tests/TestExampleFilesPipe.c

TestSendAndReceivePipe.o: ../tests/TestSendAndReceivePipe.c ./Pipe_version/PipelinePipe.h
	$(CC) $(CFLAGS) ../tests/TestSendAndReceivePipe.c

TestAddPipe.o: ../tests/TestAddPipe.c ./Pipe_version/PipelinePipe.h
	$(CC) $(CFLAGS) ../tests/TestAddPipe.c

PipelinePipe.o: ./Pipe_version/PipelinePipe.c ./Pipe_version/PipelinePipe.h
	$(CC) $(CFLAGS) ./Pipe_version/PipelinePipe.c



clean:
	$(RM) SumSquaresPipeline SievePipeline WordSumPipeline RunTests RunTestsPipe *.o
