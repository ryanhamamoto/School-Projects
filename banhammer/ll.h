/*
 * ll.h
 * Author: Darrell Long
 * CMPS 12B: Sprint 2017
 */
# ifndef NIL
# define NIL (void *) 0
# endif
# ifndef MTF
# define MTF 	true
# endif

# ifndef _LL_H
# define _LL_H

# include <stdbool.h>

extern bool moveToFront;

typedef struct listNode listNode;

//data struct for doubly linked list
struct listNode
{
	char *oldspeak, *newspeak;
	listNode *next;
	listNode *previous;
};

listNode *newNode(const char *key, const char *transfer);

listNode *delNode(listNode *t, const char *key);

void delLL(listNode *n);

listNode *insertLL(listNode **n, const char *key, const char *transfer);

listNode *findLL(listNode **n, const char *key);

void printLL(listNode *n);
# endif
