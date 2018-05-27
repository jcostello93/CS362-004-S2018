#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include "interface.h"
#include <time.h>

void asserttrue(int);

void testUpdateCoins() {

	printf("Testing updateCoins function.\n");
	srand(time(NULL));
	int randomSeed = rand();

	int k[10] = { gardens, village, council_room, adventurer, smithy, baron, great_hall, remodel, mine, feast };
	struct gameState G;

	initializeGame(2, k, randomSeed, &G);
	int currentPlayer = whoseTurn(&G); 

	G.handCount[currentPlayer] = 3;
	G.hand[currentPlayer][0] = copper; 
	G.hand[currentPlayer][1] = silver; 
	G.hand[currentPlayer][2] = gold; 

	// check for right amount of coins
	int bonus = 10; 
	int test = updateCoins(currentPlayer, &G, bonus); 
	printf("Checking for successful completition of updateCoins function...\n");
	asserttrue(test == 0); 
	printf("Checking for correct amount of coins...\n");
	asserttrue(G.coins == 1 + 2 + 3 + bonus);	// copper + silver + gold + bonus

}

int main() {

	testUpdateCoins(); 
	return 0; 
}

void asserttrue(int claim) {

	if (claim) {
		printf("TEST SUCCESSFULLY COMPLETED\n\n");
	}
	else {
		printf("TEST FAILED\n\n");
	}
}