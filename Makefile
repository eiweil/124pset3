CC=gcc
CFLAGS=-I. -g
DEPS = randmst.h binheap.h pcg_basic.h heaptest.h
ODIR=obj
TARGETS= randmst heaptest
CLEAN= randmst.dSYM 

default: randmst

all: $(TARGETS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

randmst: randmst.o pcg_basic.o binheap.o
	$(CC) -o randmst randmst.o pcg_basic.o binheap.o $(CFLAGS)

heaptest: heaptest.o pcg_basic.o binheap.o
	${CC} -o heaptest heaptest.o pcg_basic.o binheap.o $(CFLAGS)

.PHONY: clean

clean:
	rm -rf *.o *~ core $(TARGETS) $(CLEAN)