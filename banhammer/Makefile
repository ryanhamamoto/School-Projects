CFLAGS = -Wall -Wextra -Werror -Wpedantic -g
#the instructions do not say to include -std=c99
CC = gcc $(CFLAGS)
OBJECTS = lex.yy.o bf.o hash.o ll.o banhammer.o aes.o

all: banhammer

banhammer: $(OBJECTS)
	$(CC) $(OBJECTS) -o banhammer -lfl

lex.yy.o: lex.yy.c
	flex words.l
	gcc -c lex.yy.c
	

bf.o: bf.c
	$(CC) -c bf.c

hash.o: hash.c
	$(CC) -c hash.c

banhammer.o: banhammer.c
	$(CC) -c banhammer.c

ll.o: ll.c
	$(CC) -c ll.c

aes.o: aes.c
	$(CC) -c aes.c

clean:
	rm -f $(OBJECTS) banhammer 
