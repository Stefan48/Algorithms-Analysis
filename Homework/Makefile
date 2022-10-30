CC = g++
CFLAGS = -Wall -Wextra -O2

build: algo1.o algo2.o

build_first: algo1.o algo_test.o
	g++ algo1.o algo_test.o -o algo_test $(CFLAGS)

build_second: algo2.o algo_test.o
	g++ algo2.o algo_test.o -o algo_test $(CFLAGS)	

algo1.o: algo1.cpp
	g++ algo1.cpp -c $(CFLAGS)

algo2.o: algo2.cpp
	g++ algo2.cpp -c $(CFLAGS)

algo_test.o: algo_test.cpp
	g++ algo_test.cpp -c $(CFLAGS)

.PHONY: clean
clean:
	rm -rf *.o algo_test