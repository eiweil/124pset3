CC=gcc
CFLAGS=-I.
DEPS = randmst.h binheap.h pcg_basic.h heaptest.h
ODIR=obj
TARGETS= randmst heaptest

all: $(TARGETS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

randmst: randmst.o pcg_basic.o binheap.o
	$(CC) -o randmst randmst.o pcg_basic.o binheap.o $(CFLAGS)

heaptest: heaptest.o pcg_basic.o binheap.o
	${CC} -o heaptest heaptest.o pcg_basic.o binheap.o $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o *~ core $(TARGETS)