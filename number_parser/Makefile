CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99
CC = gcc $(CFLAGS)
OBJECTS = parfait.o bv.o sieve.o
EXECUTABLES = parfait

.PHONY: all
all: parfait 

parfait: $(OBJECTS)
	$(CC) $(OBJECTS) -o parfait -lm

parfait.o: parfait.c
	$(CC) -c parfait.c

bv.o: bv.c
	$(CC) -c bv.c

sieve.o: sieve.c
	$(CC) -c sieve.c
	
.PHONY: clean
clean:
	rm $(OBJECTS) $(EXECUTABLES)

	
