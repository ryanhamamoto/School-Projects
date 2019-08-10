/*
 * increment.c
 * Author: Ryan Hamamoto
 * CMPS12B: Spring 2017
 */

# include <stdio.h>
# include <getopt.h>
# include <stdint.h>
# include <pthread.h>
# include <stdlib.h>
# include <errno.h>

typedef struct threadArguments //this data will hold the assigned count of the given thread (1000)
{
	int count;
} threadArguments;

void *threadFunction(void *myArguments); //the operation that each thread must execute

void threadSafeIncrement(void); //the threadsafe operation each thread must execute

uint64_t globalCounter = 0; //global counter large enough for large amount of function calls
pthread_mutex_t mutex; //global mutex

int main(int argc, char *argv[])
{
	int userOption = 0, printFlag = 0;
	uint16_t threadCount = 0;
	while ((userOption = getopt(argc, argv, "n:")) != -1) //take in the thread count
	{
		switch(userOption)
		{
			case 'n':
			threadCount = atoi(optarg);
			printFlag = 1; //the user used the command line correctly, print an output
			break;
			
			case '?':
			if(optopt == 'n')
			{
				printf("\nERROR: please enter an argument after (-n)\n");
			}
			else
			{
				printf("\nERROR: unrecognized input\n");
			}
			break;
		}
	}
	
	pthread_mutex_init(&mutex, NULL); //initialize the mutex
	//allocate space for the threads
	threadArguments *argData = (threadArguments *)calloc(threadCount, sizeof(threadArguments));
	pthread_t *thread = (pthread_t *)calloc(threadCount, sizeof(pthread_t));
	for(uint16_t i = 0; i < threadCount; i += 1)
	{
		argData[i].count = 1000; //store the amount of incrementations desired
		pthread_create(&thread[i], NULL, threadFunction, &argData[i]); //spawn the new thread
	}
	for(uint16_t k = 0; k < threadCount; k += 1)
	{
		if(pthread_join(thread[k], NULL)) //await termination
		{
				exit(errno); //exit if join does not return 0
		}
	}
	if(printFlag)
	{
		printf("%lu\n", globalCounter); //print the incremented result
	}
	free(argData); //free everything that was allocated
	free(thread);
	pthread_mutex_destroy(&mutex); //destroy the mutex
	return 0;
}

void *threadFunction(void *myArguments)
{
	threadArguments *arguments = (threadArguments *)myArguments;
	int count = arguments->count; //copy count data
	for(int j = 0; j < count; j += 1)
	{
		threadSafeIncrement(); //use each thread to increment the counter
	}
	return NULL;
}

void threadSafeIncrement(void)
{
	pthread_mutex_lock(&mutex); //lock the mutex so only one thread can access function at a time
	globalCounter += 1; //increment
	pthread_mutex_unlock(&mutex); //unlock the mutex
	return;
}

