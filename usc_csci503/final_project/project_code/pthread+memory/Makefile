SRCS = serial.cc util.cc timer.cc myHeap.cc
OBJS = $(SRCS:.cc=.o)
CXX = g++

.SUFFIXES: .cc .o
.cc.o:
	g++ -c -o $@ $<

default: all 
all: quicksort_pthread quicksort_MemoryOpt

quicksort_pthread: quicksortpthread.o pthread.o $(OBJS)
	$(CXX) -o $@ $^ -lm -lpthread -lstdc++
quicksort_MemoryOpt: quicksortMemoryOpt.o $(OBJS)
	$(CXX) -o $@ $^ -lm -lpthread


clean:
	/bin/rm -f *.o quicksort quicksort_pthread quicksort_MPI quicksort_MemoryOpt

