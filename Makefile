CXX = g++

CXXFLAGS = -O3 -std=c++14 
LDFLAGS  = 
LIBS     = 
TARGET = main

SRCS = main.cpp matrix_funcs.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
		$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)


clean:
		-rm -rf $(OBJS) $(TARGET)

.PHONY: all clean
