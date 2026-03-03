CC=gcc
CFLAGS= -O3 -g -Wall -Werror -Wno-error -Wno-unused-but-set-variable -Wno-unused-variable -DNDEBUG 
CCCOM=$(CC) $(CFLAGS) -std=c11

LDLIBS=-lmingw32 -lSDLmain -lSDL 
LDFLAGS=-L/mingw/bin

SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

EXE=lolo

all:$(EXE)

$(EXE):$(OBJS)
	$(CCCOM) $(LDFLAGS) -o  $@ $^ $(LDLIBS)

.PHONY: clean

clean:
	$(RM) $(OBJS) *.exe 