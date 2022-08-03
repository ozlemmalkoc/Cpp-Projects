CC := g++

CFLAGS := -Wall --std=c++11

HDRS := src/PegSolitaire.h src/Basis.h

SRCS := main.cpp src/PegSolitaire.cpp

OBJS := $(SRCS:.c=.o)

EXEC := run

all: $(EXEC)

$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm -f $(EXEC)

.PHONY: all clean
