CC=gcc
CFLAGS=-I.
DEPS = randmst.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

randmst: randmst.o 
	gcc -o randmst randmst.o -I.