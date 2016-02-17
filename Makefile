CC=gcc
CFLAGS=-I.
DEPS = randmst.h
ODIR=obj

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

randmst: randmst.o 
	gcc -o randmst randmst.o -I.

.PHONY: clean

clean:
	rm -f *.o *~ core randmst