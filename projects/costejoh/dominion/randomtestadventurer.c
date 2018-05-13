#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include "interface.h"
#include <time.h>


int asserttrue(int);


int main() {
	printf("Testing Adventurer card.\n");
	srand(time(NULL));

	int k[10] = { gardens, village, council_room, adventurer, smithy, baron, great_hall, remodel, mine, feast };
	struct gameState G;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int bonus = 0;
	const int numTests = 100000;

	int i; 
	int test; 
	int randomSeed;
	int randomDeckSize; 
	int randomHandSize; 
	int completions = 0; 
	int checkTreasures = 0;
	int handBefore = 0; 
	int handAfter = 0; 
	int checkHand = 0; 

	for (i = 0; i < numTests; i++) {
		randomSeed = rand();
		randomDeckSize = rand() % 30 + 1; 
		randomHandSize = rand() % randomDeckSize + 1; 

		initializeGame(2, k, randomSeed, &G);
		int currentPlayer = whoseTurn(&G);
		int oldTreasures = 0;
		int newTreasures = 0;
		G.deckCount[currentPlayer] = randomDeckSize;
		G.handCount[currentPlayer] = randomHandSize; 

		int j; 
		for (j = 0; j < G.handCount[currentPlayer]; j++) {
			if (G.hand[currentPlayer][j] == copper) {
				oldTreasures = oldTreasures + 1;
			}
			else if (G.hand[currentPlayer][j] == silver) {
				oldTreasures = oldTreasures + 1;
			}
			else if (G.hand[currentPlayer][j] == gold) {
				oldTreasures = oldTreasures + 1;
			}
		}

		handBefore = G.handCount[currentPlayer]; 

		test = cardEffect(adventurer, choice1, choice2, choice3, &G, 0, &bonus); 
		completions = completions + asserttrue(test == 0);


		if (test == 0) {
			for (j = 0; j < G.handCount[currentPlayer]; j++) {
				if (G.hand[currentPlayer][j] == copper) {
					newTreasures = newTreasures + 1;
				}
				else if (G.hand[currentPlayer][j] == silver) {
					newTreasures = newTreasures + 1;
				}
				else if (G.hand[currentPlayer][j] == gold) {
					newTreasures = newTreasures + 1;
				}
			}

		handAfter= G.handCount[currentPlayer];
	
		checkHand = checkHand + asserttrue(handAfter - handBefore == 2); 
		checkTreasures = checkTreasures + asserttrue(newTreasures - oldTreasures == 2);
		}
	}

	printf("\n\nYou called this function %d times. It completed successfully %d times.\n", numTests, completions);
	printf("It returned the correct number of treasures %d times.\n", checkTreasures); 
	printf("The hand count at the end was correct %d times.\n\n", checkHand); 

	return 0; 
}

int asserttrue(int claim) {
	if (claim) {
		return 1; 
	}
	else {
		return 0; 
	}
}