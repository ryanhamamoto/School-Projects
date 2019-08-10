CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99
CC = gcc $(CFLAGS)
OBJECTS = minsort.o sorting.o bubblesort.o insertionsort.o quicksort.o mergesort.o

all: sorting

sorting: $(OBJECTS)
	$(CC) $(OBJECTS) -o sorting
	
sorting.o: sorting.c
	$(CC) -c sorting.c

minsort.o: minsort.c
	$(CC) -c minsort.c

bubblesort.o: bubblesort.c
	$(CC) -c bubblesort.c

insertionsort.o: insertionsort.c
	$(CC) -c insertionsort.c	

quicksort.o: quicksort.c
	$(CC) -c quicksort.c	

mergesort.o: mergesort.c
	$(CC) -c mergesort.c
clean:
	rm -f sorting $(OBJECTS)
