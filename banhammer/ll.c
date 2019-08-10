/*
 * ll.c took influence from piazza post 542 Author:Darrell Long
 * CMPS 12B: Sprint 2017
 */

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stdint.h>
# include "ll.h"

//allocates memory for the new node and assigns the given data to their
//designated sections in the data structure
listNode *newNode(const char *key, const char *transfer)
{
    listNode *t = (listNode *) malloc(sizeof(listNode));
    t->oldspeak = strdup(key);
	t->newspeak = strdup(transfer);
    t->next = NIL;
	t->previous = NIL;
    return t; //return the pointer
}

//frees all memory allocated to the node
//takes influence from guest lecturer Ahmed on linked lists
listNode *delNode(listNode *t, const char *key)
{
	listNode *deleteNode = findLL(&t, key); //find the node to be deleted
	listNode *newList; //prepare new list
	if (deleteNode != NIL) //if this node exists
	{
		if (deleteNode->previous != NIL && deleteNode->next != NIL) //if not at head or tail of list
		{
			deleteNode->previous->next = deleteNode->next;
			deleteNode->next->previous = deleteNode->previous;
			newList = t;
		}
		else if (deleteNode->previous != NIL && deleteNode->next == NIL) //if at tail of list
		{
			deleteNode->previous->next = NIL; //set new tail
			newList = t;
		}
		else if (deleteNode->previous == NIL && deleteNode->next != NIL) //if at head of list
		{
			newList = deleteNode->next;
			deleteNode->next->previous = NIL; //set new head of list
		}
		else if (deleteNode->previous == NIL && deleteNode->next == NIL) //if only item in list
		{
			newList = NIL; //point to NIL
		}
		//now that pointer reallocation is complete, free data, return pointer to new list
		free(deleteNode->oldspeak);
		free(deleteNode->newspeak); 
		free(deleteNode);
		return newList;
	} 
	return t; //if NIL list, return NIL
}

//deletes the linked list, assumes head is entered as n
void delLL(listNode *n)
{
    while (n != NIL)
    {
        listNode *t = n;
        n = n->next;
        delNode(t, t->oldspeak);
    }
    return;
}

//adds a node to the head of the list, sets 'previous' pointer of original head to new node
listNode *insertLL(listNode **n, const char *key, const char *transfer)
{
    listNode *t = newNode(key, transfer);
    t->next = *n;
	t->next->previous = t;
	//previous already set to NIL in newNode
    return t;
}

//finds member of linked list with oldspeak equivalent value to key
listNode *findLL(listNode **n, const char *key)
{
	extern uint32_t seeks, mtfFlag;
	//find where it is in list n so dont change list n
	seeks++;
	//extern int mtfFlag;
        for (listNode *t = *n; t != NIL; t = t->next)
        {
	//distance++;
        if (strcmp(t->oldspeak, key) == 0)
        {
		if(mtfFlag)
		{
			//printf("mtfRule");
				
			//listNode *temp = t;
			//delNode(t, key);
			//temp = insertLL(&temp, t->oldspeak, t->newspeak); //move node to front of list
			//return temp;
		}
		return t;
        }
    }
    return NIL;
}

//prints linked list, assumes head is given as n
void printLL(listNode *n)
{
    for (listNode *t = n; t != NIL; t = t->next)
    {
        printf("\n%s %s", t->oldspeak, t->newspeak);
    }
    printf("\n");
    return;
}
