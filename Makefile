
CC=cc
CFLAGS=-O2 -ansi -pedantic

SOURCES=src/main.c

.PHONY: all clean

all: taco

taco: $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f taco