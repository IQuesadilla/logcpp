CXX = g++
CFLAGS = -o $@ -c $< -std=c++17 -fPIC 
TARGET = liblogcpp.o
TESTS = test1

all: $(TARGET)

liblogcpp.o: logcpp.cpp logcpp.h
	$(CXX) $(CFLAGS)

clean:
	-rm *.o
	-rm tests/bin/*