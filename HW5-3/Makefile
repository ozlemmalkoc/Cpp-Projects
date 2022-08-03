CC := g++

CFLAGS := --std=c++11

HDRS := MyClass.h LogicCircuit.h

SRCS := main.cpp LogicCircuit.cpp

OBJS := $(SRCS:.cpp=.o)

EXEC := run

all: $(EXEC)

$(EXEC): $(OBJS) $(HDRS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean
