SRCS = serial.cc util.cc timer.cc myHeap.cc
OBJS = $(SRCS:.cc=.o)
CXX = mpiCC

.SUFFIXES: .cc .o
.cc.o:
	$(CXX) -c -o $@ $<

default: all 
all: quicksort_pthread quicksort_MPI quicksort_MemoryOpt quicksort_topology hybrid

quicksort_pthread: quicksortpthread.o pthread.o $(OBJS)
	g++ -o $@ $^ -lm -lpthread -lstdc++
quicksort_MPI: quicksortMPI.o parallel_main.o $(OBJS)
	$(CXX) -o $@ $^ -lm -lpthread
quicksort_MemoryOpt: quicksortMemoryOpt.o $(OBJS)
	$(CXX) -o $@ $^ -lm -lpthread
quicksort_topology: parallel_topology.o parallel_topology_main.o $(OBJS)
	$(CXX) -o $@ $^ -lm -lpthread
hybrid: hybrid.o parallel_hybrid.o pthread.o $(OBJS)
	$(CXX) -o $@ $^ -lm -lpthread


clean:
	/bin/rm -f *.o quicksort quicksort_pthread quicksort_MPI quicksort_MemoryOpt hybrid quicksort_topology

