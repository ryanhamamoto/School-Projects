CFLAGS = -Wall -Wextra -Werror -Wpedantic -g
CC = gcc $(CFLAGS)
OBJECTS = increment.o

all: increment

increment: $(OBJECTS)
	$(CC) $(OBJECTS) -o increment -lpthread

increment.o: increment.c
	$(CC) -c increment.c

clean:
	rm -f $(OBJECTS) increment
