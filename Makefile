CC=gcc
CFLAGS=-I. -g -lm
DEPS = randmst.h binheap.h pcg_basic.h heaptest.h daryheap.h darytest.h
ODIR=obj
TARGETS= randmst heaptest darytest
CLEAN= randmst.dSYM 

default: randmst

all: $(TARGETS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

randmst: randmst.o pcg_basic.o binheap.o
	$(CC) -o randmst randmst.o pcg_basic.o binheap.o $(CFLAGS)

heaptest: heaptest.o pcg_basic.o binheap.o
	${CC} -o heaptest heaptest.o pcg_basic.o binheap.o $(CFLAGS)

darytest: darytest.o pcg_basic.o daryheap.o
	${CC} -o darytest darytest.o pcg_basic.o daryheap.o $(CFLAGS)

.PHONY: clean

clean:
	rm -rf *.o *~ core $(TARGETS) $(CLEAN)