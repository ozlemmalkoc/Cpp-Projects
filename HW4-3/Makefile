CC := g++

CFLAGS := --std=c++11

HDRS := Robot.h Bulldozer.h Roomba.h Human.h Optimusprime.h Robocop.h

SRCS := main.cpp Robot.cpp Bulldozer.cpp Roomba.cpp Human.cpp Optimusprime.cpp Robocop.cpp

OBJS := $(SRCS:.c=.o)

EXEC := run

all: $(EXEC)

$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm -f $(EXEC)

.PHONY: all clean