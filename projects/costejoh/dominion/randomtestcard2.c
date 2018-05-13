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

	printf("Testing Council Room card.\n");
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
	int handBefore = 0;
	int handAfter = 0;
	int currentPlayer;
	int otherPlayer;
	int buysBefore = 0; 
	int buysAfter = 0; 
	int otherHandBefore = 0; 
	int otherHandAfter = 0; 
	int randomBuys = 0; 
	int checkHand = 0;
	int checkBuys = 0; 
	int checkOtherHand = 0; 

	for (i = 0; i < numTests; i++) {
		randomSeed = rand();
		randomDeckSize = rand() % 30 + 1;
		randomHandSize = rand() % randomDeckSize + 1;
		randomBuys = rand() % 6;

		initializeGame(2, k, randomSeed, &G);
		currentPlayer = whoseTurn(&G);
		if (currentPlayer == 0) {
			otherPlayer = 1;
		}
		else {
			otherPlayer = 0;
		}

		G.handCount[currentPlayer] = randomHandSize;
		G.deckCount[currentPlayer] = randomDeckSize;
		G.numBuys = randomBuys;
		G.numPlayers = 2;

		buysBefore = G.numBuys;
		handBefore = G.handCount[currentPlayer];
		otherHandBefore = G.handCount[otherPlayer];

		test = cardEffect(council_room, choice1, choice2, choice3, &G, 0, &bonus);
		completions = completions + asserttrue(test == 0);

		if (test == 0) {
			buysAfter = G.numBuys;
			handAfter = G.handCount[currentPlayer];
			otherHandAfter = G.handCount[otherPlayer];

			checkBuys = checkBuys + asserttrue(buysAfter == buysBefore + 1);
			checkHand = checkHand + asserttrue(handAfter == handBefore + 3);
			checkOtherHand = checkOtherHand + asserttrue(otherHandAfter == otherHandBefore + 1);
		}

	}

	printf("\n\nYou called this function %d times. It completed successfully %d times.\n", numTests, completions);
	printf("The current player's number of buys at the end was correct %d times.\n\n", checkBuys);
	printf("The current player's hand count at the end was correct %d times.\n\n", checkHand);
	printf("The other player's hand count at the end was correct %d times.\n\n", checkOtherHand);


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