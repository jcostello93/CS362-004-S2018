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

void testSmithy() {
	printf("Testing Smithy card.\n");
	srand(time(NULL));
	int randomSeed = rand();
	int option1 = 0; 
	int option2 = 0; 
	int option3 = 0; 
	int bonus = 0; 
	int k[10] = { gardens, village, council_room, adventurer, smithy, baron, great_hall, remodel, mine, feast };
	struct gameState G;

	initializeGame(2, k, randomSeed, &G);
	int currentPlayer = whoseTurn(&G);

	G.handCount[currentPlayer] = 5; 	
	int oldHandCount = G.handCount[currentPlayer];
	int test = cardEffect(smithy, option1, option2, option3, &G, 0, &bonus);
	printf("Checking successful completion of function...\n");
	asserttrue(test == 0);
	printf("Checking for correct handCount...\n");
	asserttrue(G.handCount[currentPlayer] == oldHandCount + 2);	// draw 3 cards, then play 1
}

int main() {

	testSmithy(); 
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
