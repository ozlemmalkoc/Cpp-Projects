CC := g++

CFLAGS := 

HDRS := DayofYearSet.h

SRCS := main.cpp DayofYearSet.cpp

OBJS := $(SRCS:.c=.o)

EXEC := run

all: $(EXEC)

$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm -f $(EXEC)

.PHONY: all clean