CC := g++

CFLAGS := -Wall --std=c++11

HDRS :=

SRCS := main.cpp

OBJS := $(SRCS:.c=.o)

EXEC := a.out

all: $(EXEC)

$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm -f $(EXEC)

.PHONY: all clean
