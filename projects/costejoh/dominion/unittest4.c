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

void testScoreFor() {

	printf("Testing scoreFor function.\n");
	srand(time(NULL));
	int randomSeed = rand();

	int k[10] = { gardens, village, council_room, adventurer, smithy, baron, great_hall, remodel, mine, feast };
	struct gameState G;

	initializeGame(2, k, randomSeed, &G);
	int currentPlayer = whoseTurn(&G); 

	G.handCount[currentPlayer] = 0;
	G.discardCount[currentPlayer] = 0;
	G.deckCount[currentPlayer] = 0;

	int i; 

	for (i = 0; i < 6; i++) {
		G.handCount[currentPlayer]++;
		G.discardCount[currentPlayer]++;
		G.deckCount[currentPlayer]++;

		if (i == 0) {
			G.hand[currentPlayer][0] = curse;
			G.discard[currentPlayer][0] = curse;
			G.deck[currentPlayer][0] = curse;

			int test = scoreFor(currentPlayer, &G);
			printf("Testing curse...\n");
			asserttrue(test == -3);
		}

		if (i == 1) {
			G.hand[currentPlayer][1] = estate;
			G.discard[currentPlayer][1] = estate;
			G.deck[currentPlayer][1] = estate;

			int test = scoreFor(currentPlayer, &G);
			printf("Testing estate...\n");
			asserttrue(test == -3 + 3);
		}

		if (i == 2) {
			G.hand[currentPlayer][2] = duchy;
			G.discard[currentPlayer][2] = duchy;
			G.deck[currentPlayer][2] = duchy;

			int test = scoreFor(currentPlayer, &G);
			printf("Testing duchy...\n");
			asserttrue(test == -3 + 3 + 9);
		}

		if (i == 3) {
			G.hand[currentPlayer][3] = province;
			G.discard[currentPlayer][3] = province;
			G.deck[currentPlayer][3] = province;

			int test = scoreFor(currentPlayer, &G);
			printf("Testing province...\n");
			asserttrue(test == -3 + 3 + 9 + 18);
		}

		if (i == 4) {
			G.hand[currentPlayer][4] = great_hall;
			G.discard[currentPlayer][4] = great_hall;
			G.deck[currentPlayer][4] = great_hall;

			int test = scoreFor(currentPlayer, &G);
			printf("Testing estate...\n");
			asserttrue(test == -3 + 3 + 9 + 18 + 3);
		}

		if (i == 4) {
			G.hand[currentPlayer][5] = gardens;
			G.discard[currentPlayer][5] = gardens;
			G.deck[currentPlayer][5] = gardens;

			int test = scoreFor(currentPlayer, &G);
			printf("Testing gardens...\n");
			asserttrue(test == -3 + 3 + 9 + 18 + 3 + 18 / 10 );
		}
	}
}

int main() {

	testScoreFor(); 
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