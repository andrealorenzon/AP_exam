CC      = g++
CFLAGS  = -I/home/scale/g++Projects/gLib/ -Wall -Wextra
LDFLAGS = -lfltk

all: binary_tree clean

BLT: binary_tree.o
	$(CC) -o $@ $^ $(LDFLAGS)

binary_tree.o: binary_tree.cpp 
	$(CC) -c $(CFLAGS) $<

.PHONY: clean cleanest

clean:
	rm *.o

cleanest: clean
	rm binary_tree