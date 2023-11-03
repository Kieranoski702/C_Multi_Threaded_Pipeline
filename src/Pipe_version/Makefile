CC = clang
RM = rm -f
DFLAG = -g
GFLAGS = -Wall -Wextra
CFLAGS = $(DFLAG) $(GFLAGS) -c
LFLAGS = $(DFLAG) $(GFLAGS) -pthread

all: SumSquaresPipelinePipe SievePipelinePipe WordSumPipelinePipe

SumSquaresPipelinePipe: SumSquaresPipelinePipe.o PipelinePipe.o
	$(CC) $(LFLAGS) SumSquaresPipelinePipe.o PipelinePipe.o -o SumSquaresPipelinePipe

SievePipelinePipe: SievePipelinePipe.o PipelinePipe.o
	$(CC) $(LFLAGS) SievePipelinePipe.o PipelinePipe.o -o SievePipelinePipe

WordSumPipelinePipe: WordSumPipelinePipe.o PipelinePipe.o
	$(CC) $(LFLAGS) WordSumPipelinePipe.o PipelinePipe.o -o WordSumPipelinePipe


SievePipelinePipe.o: SievePipelinePipe.c
	$(CC) $(CFLAGS) SievePipelinePipe.c

SumSquaresPipelinePipe.o: SumSquaresPipelinePipe.c
	$(CC) $(CFLAGS) SumSquaresPipelinePipe.c

WordSumPipelinePipe.o: WordSumPipelinePipe.c
	$(CC) $(CFLAGS) WordSumPipelinePipe.c



PipelinePipe.o: PipelinePipe.c PipelinePipe.h
	$(CC) $(CFLAGS) PipelinePipe.c


clean:
	$(RM) SumSquaresPipelinePipe SievePipelinePipe WordSumPipelinePipe *.o
