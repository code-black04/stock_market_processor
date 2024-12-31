# The following just specifies some variables for "flexibility".

# Specify the C++ compiler
CXX     = g++

# Specify options to pass to the compiler. Here it sets the optimisation
# level, outputs debugging info for gdb, and C++ version to use.
CXXFLAGS = -O0 -g3 -std=c++17

All: all
all: main transaction.o order.o stock_processor.o

# These are the two executables to be produced
main: main.cpp transaction.o order.o stock_processor.o
	$(CXX) $(CXXFLAGS) main.cpp transaction.o order.o stock_processor.o -o main

transaction.o: transaction.cpp transaction.h
	$(CXX) $(CXXFLAGS) -c transaction.cpp -o transaction.o

order.o: order.cpp order.h
	$(CXX) $(CXXFLAGS) -c order.cpp -o order.o

stock_processor.o: stock_processor.cpp stock_processor.h
	$(CXX) $(CXXFLAGS) -c stock_processor.cpp -o stock_processor.o

# Some cleanup functions, invoked by typing "make clean" or "make deepclean"
deepclean:
	rm -f *~ *.o stock_processor order main main.exe *.stackdump

clean:
	rm -f *~ *.o *.stackdump
