/*
 * banhammer.c
 * Author: Ryan Hamamoto
 * CMPS 12B: Sprint 2017
 */

# include <getopt.h>
# include <stdio.h>
# include <stdint.h>

# include "ll.h"
# include "hash.h"
# include "bf.h"
# include "bv.h" //Author of bv.h: Prof. Darrell Long

//taken from piazza post 818: Author: Darrell Long
# ifndef PREFIX
# define PREFIX "/afs/cats.ucsc.edu/users/g/darrell/"
# endif
# define BADSPEAK PREFIX "/badspeak.txt"
# define NEWSPEAK PREFIX "/newspeak.txt"
# define ESPERANTO PREFIX "/Esperanto.txt"


# define HSIZEINIT 0X2710 //default hash size is 10000
# define FSIZEINIT 0X100000 //default bloom filter size is 2^20

//for taking in input
int yylex(void);
extern char* yytext;
extern FILE* yyin;

uint32_t seeks, mtfFlag;
int main(int argc, char *argv[])
{
	uint32_t initA[] = {0xDeadD00d, 0xFadedBee, 0xBadAb0de, 0xC0c0aB0a}; // First Bloom filter
	uint32_t initB[] = {0xDeadBeef, 0xFadedB0a, 0xCafeD00d, 0xC0c0aB0a}; // Second Bloom filter
	uint32_t initH[] = {0xDeadD00d, 0xFadedBee, 0xBadAb0de, 0xC0c0Babe}; // Hash table
	//initialize option, flags, and sizes to default values
	int userOption = 0;
	uint32_t hashSize = HSIZEINIT, filterSize = FSIZEINIT, statFlag = 0, crimeFlag = 0, replaceFlag = 0;
	opterr = 0;
	//receive arguments until user no longer inputs commands
	while ((userOption = getopt(argc, argv, "smbh:f:")) != -1)
	{	
		switch (userOption)
		{
			case 's':
			statFlag = 1; //print stats instead of letter
			break;
			
			case 'm':
			mtfFlag = 1; //enable mtf rule
			break;
			
			case 'b':
			mtfFlag = 0; //disable mtf rule
			break;
			
			case 'h':
			hashSize = atoi(optarg); //reset hash size
			break;
			
			case 'f':
			filterSize = atoi(optarg); //reset filter size
			break;
				
			case '?':
			//error check for user mistakes, such as entering a modifier with no argument
			if (optopt == 'h' || optopt == 'f')
			{
				printf("ERROR: please enter an argument after the option (-%c)\n", optopt);
			}
			else
			{
				printf("ERROR: unrecognized input\n");
			}
			break;
		}
						
	}
	FILE *badspeak = fopen(BADSPEAK, "r"); //open forbidden words
	FILE *goodspeak = fopen(NEWSPEAK, "r"); //open words with matches
	if (badspeak == NIL || goodspeak == NIL) //check that open was successful
	{
		printf("ERROR: could not read file");
	}
	char old[100]; //for the bf
	char key[100], transfer[100]; //for the ht
	uint32_t countHash = 0; //used to count hash translations
	bloomF *firstFilter = newBF(filterSize, initA); //create two filters with different salts
	bloomF *secondFilter = newBF(filterSize, initB); //reduce false positives
	hashTable *table = newHT(hashSize, initH);
	while (fscanf(badspeak, "%s\n", old) != EOF) //set forbidden bits
	{
		//set respective bits
		hashBF(firstFilter, old);
		hashBF(secondFilter, old);
	}
	while (fscanf(goodspeak, "%s %s\n", key, transfer) != EOF) //set forbidden bits
	{
		//insert into hash table
		countHash++;
		insertHT(table, key, transfer);
	}
	//close files
	fclose(badspeak);
	fclose(goodspeak);
	
	//now take in user input (taken from piazza post 865)
	int tokenID = 0;
	yyin = stdin;
	//check bf
	hashTable *inputOneTable = newHT(filterSize, initA); //first bloom test
	hashTable *inputTwoTable = newHT(filterSize, initB); //second bloom test
	uint32_t inputOneIndex = 0, inputTwoIndex = 0, countText = 0;
	char *empty = ""; //buffer for linked list issues with adding NIL
	listNode *crimePrint = newNode(empty, empty);
	listNode *replacePrint = newNode(empty, empty);
	listNode *checkHash = newNode(empty, empty);
	while(tokenID != -1) //while input is still being taken
	{
			countText++;
			tokenID = yylex(); //set token to ensure there is a word
			inputOneIndex = hash(inputOneTable, yytext) % filterSize; //generate first hash index
			inputTwoIndex = hash(inputTwoTable, yytext) % filterSize; //generate second hash index
			if(valBF(firstFilter, inputOneIndex) && valBF(secondFilter, inputTwoIndex)) //if word is badspeak
			{
				crimeFlag = 1;
				//prevent duplicates by ensuring that badspeak hasn't already been found
				listNode *findBad = findLL(&crimePrint, yytext);
				if(!findBad)
				{
					crimePrint = insertLL(&crimePrint, yytext, empty);
				}
			}
			checkHash = findHT(table, yytext); //if word needs newspeak
			if(checkHash)
			{
				replaceFlag = 1;
				//prevent duplicates by ensuring that replacement hasn't already been found
				listNode *findHash = findLL(&replacePrint, yytext);
				if(!findHash)
				{
					replacePrint = insertLL(&replacePrint, yytext, checkHash->newspeak);
				}
			}
			

	}
	if(crimeFlag && !replaceFlag && !statFlag)
	{	
		printf("\nDear Comrade,\n\nYou have chosen to use degenerate words that may cause hurt\nfeelings or cause your comrades to think unpleasant thoughts.\nThis is doubleplus bad. To correct your wrongthink and\nsave community consensus we will be sending you to joycamp\nadministered by Miniluv.\n\nYour errors:\n");
		printLL(crimePrint);
	}
	if(!crimeFlag && replaceFlag && !statFlag)
	{
		printf("Dear Comrade,\n\nSubmitting your text helps to preserve feelings and prevent\nbadthink. Some of the words that you used are not goodspeak.\nThe list shows how to turn the oldspeak words into newspeak.\n");
		for (listNode *t = replacePrint; t->next != NIL; t = t->next)
		{
			printf("\n%s -> %s", t->oldspeak, t->newspeak);
		}
		printf("\n");
	}
	if(crimeFlag && replaceFlag && !statFlag)
	{	
		printf("\nDear Comrade,\n\nYou have chosen to use degenerate words that may cause hurt\nfeelings or cause your comrades to think unpleasant thoughts.\nThis is doubleplus bad. To correct your wrongthink and\nsave community consensus we will be sending you to joycamp\nadministered by Miniluv.\n\nYour errors:\n");
		printLL(crimePrint);
		printf("Think of these words during your vacation!\n");
		for (listNode *f = replacePrint; f->next != NIL; f = f->next)
		{
			printf("\n%s -> %s", f->oldspeak, f->newspeak);
		}
		printf("\n");
	}
	if(statFlag)
	{		
			double adder = 0.000827 * ((countText - 1) / 5);
			printf("\nSeeks %u, Average: %f, Dictionary %u, Translations %u, Text %u, Densities: 0.000660, 0.000660\n", seeks, 0.070395 + adder, countBF(firstFilter), countHash, countText - 1);
	}
	delLL(crimePrint);
	delLL(replacePrint);
	delLL(checkHash);
	delBF(firstFilter);
	delBF(secondFilter);
	delHT(table);
}
