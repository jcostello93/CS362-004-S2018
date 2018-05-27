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

void testAdventurer() {
	printf("Testing Adventurer card.\n");
	srand(time(NULL));
	int randomSeed = rand();

	int k[10] = { gardens, village, council_room, adventurer, smithy, baron, great_hall, remodel, mine, feast };
	struct gameState G;

	initializeGame(2, k, randomSeed, &G);
	int currentPlayer = whoseTurn(&G);
	
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0; 
	int bonus = 0; 

	int i;

	int oldTreasures = 0; 
	for (i = 0; i < G.handCount[currentPlayer]; i++) {
		if (G.hand[currentPlayer][i] == copper) {
			oldTreasures = oldTreasures + 1;
		}
		else if (G.hand[currentPlayer][i] == silver) {
			oldTreasures = oldTreasures + 1;
		}
		else if (G.hand[currentPlayer][i] == gold) {
			oldTreasures = oldTreasures + 1;
		}
	}
	int test = cardEffect(adventurer, choice1, choice2, choice3, &G, 0, &bonus);
	printf("Checking successful completion of function...\n");
	asserttrue(test == 0);

	int newTreasures = 0; 
	for (i = 0; i < G.handCount[currentPlayer]; i++) {
		if (G.hand[currentPlayer][i] == copper) {
			newTreasures = newTreasures + 1; 
		}
		else if (G.hand[currentPlayer][i] == silver) {
			newTreasures = newTreasures + 1;
		}
		else if (G.hand[currentPlayer][i] == gold) {
			newTreasures = newTreasures + 1; 
		}
	}

	printf("Checking for 2 new treasures...\n");
	asserttrue(newTreasures - oldTreasures == 2);
}

int main() {

	testAdventurer(); 
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