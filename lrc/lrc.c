/* ************************************************************************** */
/** 

  @File Name
    lrc.c

  @Creator
    Ryan Hamamoto
 */
/* ************************************************************************** */

//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define POT 11 //end of the array keeping track of the pot
#define DOWN 0 //used for outFlag
#define UP 1 //used for outFlag


typedef enum faciem { //defines each face option of the die
	LEFT,
	RIGHT,
	CENTER,
	PASS
} faces;

//creates 6 faces with values from the faces enum
faces die[] = {LEFT, RIGHT, CENTER, PASS, PASS, PASS};

const char *names[] = {"Whoopie",
		       "Dale",
		       "Rosie",
		       "Jimmie",
		       "Barbara",
		       "Kyle",
		       "Raven",
		       "Tony",
		       "Jenny",
		       "Clint"};

int main(void)
{	
	//array to keep track of the bank of each player(init at $3) and the pot (init at $0)
	int bank[11] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0};
	//array to keep track of which players are out, init to 0
	unsigned int outFlag[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	
	unsigned int seed = 0, players = 0; //initialize variables
	printf("\nRandom seed:"); //request and scan seed value
	scanf("%u", &seed);
	printf("\nNumber of players:"); //request and scan player value
	scanf("%u", &players);
	srand(seed); //set the seed
	
	unsigned int sum = 0; //resets the calculated sum of players that are out
	while (sum != players - 1) //as long as more than one player is in, keep playing
	{
		for (unsigned int index = 0; index < players; index++) //counts through each player
		{
			int rolls; //determines the amount of rolls the player gets
			if (bank[index] != 0)
			{
				outFlag[index] = DOWN; //reset outFlag if player is back in game
				printf("\n%s rolls... ", names[index]); //initial statement
				
				//allocates amount of rolls based on bank amount
				if (bank[index] >= 3)
				{
					rolls = 3;
				}
				else if (bank[index] == 2)
				{ 
					rolls = 2;
				}
				else if (bank[index] == 1)
				{
					rolls = 1;
				}
			}
			else if (bank[index] == 0)
			{
				//if bank is 0, flags that the player is out
				rolls = 0;
				outFlag[index] = UP;
			}
			
			//determines the outcome of each roll and allocates winnings
			for (int j = 0; j < rolls; j++)
			{
				int randomNumber = rand() % 6; //generates a random between 0 and 5
				switch(die[randomNumber]) //rolls the dice
				{
					case PASS:
						printf(" gets a pass"); //print and do nothing
						break;
					
					case LEFT:
						bank[index]--; //reduces current bank
						if (index == 0) //if at the far left end of the array
						{
							unsigned int temp = players - 1;
							printf(" gives $1 to %s", names[temp]);
							bank[temp]++; //increases bank at far right end of array
						}
						else
						{
						unsigned int temp = index - 1;
						printf(" gives $1 to %s", names[temp]);
						bank[temp]++; //increase currency in left bank
						}
						if(bank[index] == 0) //flags if person is out
						{
							outFlag[index] = UP;
						}
						break;
					
					case RIGHT:
						bank[index]--; //reduces current bank
						if (index == players - 1) //if at the far right end of the array
						{
						printf(" gives $1 to %s", names[0]);
						bank[0]++; //increases bank at far left end of array
						}
						else
						{
						unsigned int temp = index + 1;
						printf(" gives $1 to %s", names[temp]);
						bank[temp]++; //increase currency in right bank
						}
						if(bank[index] == 0) //flags if person is out
						{
							outFlag[index] = UP;
						}
						break;
					
					case CENTER:
						printf(" puts $1 in the pot");
						bank[index]--; //reduce currency in current bank
						bank[POT]++; //increase the currency in the pot
						if(bank[index] == 0) //flags if person is out
						{
							outFlag[index] = UP;
						}
						break;			
				}
			}
			//at the end of every player's turn, calculate sum of out players
			sum = 0;
			for (unsigned int k = 0; k < players; k++)
			{
			sum += outFlag[k]; //add up each flag
			}
 			if(sum == players - 1) //if only one player is in, break out of the loop
			{
				break;
			}
		}
	}
	//determines whose flag is not raised and declares the winner
	unsigned int m, winner = 0;
	for (m = 0; m < players; m++)
	{
	if (outFlag[m] == 0)
		winner = m;
	}
	//prints win message
	printf("\n%s wins the $%d pot with $%d left in the bank!\n", 
	names[winner], bank[POT], bank[winner]);
	return 0;
}
