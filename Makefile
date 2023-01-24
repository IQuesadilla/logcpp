CXX = g++
CFLAGS = -o $@ -c $< -std=c++17 -fPIC 
TARGET = liblogcpp.o
TESTS = test1

all: $(TARGET)

tests: $(TESTS)

test1: liblogcpp.o tests/test1.cpp
	$(CXX) -o ./tests/bin/$@ $^ -std=c++17

liblogcpp.o: logcpp.cpp logcpp.h
	$(CXX) $(CFLAGS)

clean:
	-rm *.o
	-rm tests/bin/*