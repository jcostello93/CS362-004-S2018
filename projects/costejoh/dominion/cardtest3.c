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

void testCouncilRoom() {

	printf("Testing Council Room card.\n");
	srand(time(NULL));
	int randomSeed = rand();

	int k[10] = { gardens, village, council_room, adventurer, smithy, baron, great_hall, remodel, mine, feast };
	struct gameState G;

	initializeGame(2, k, randomSeed, &G);
	
	int choice1 = 0; 
	int choice2 = 0; 
	int choice3 = 0;
	int bonus = 0;
	int currentPlayer = whoseTurn(&G); 
	int otherPlayer;
	if (currentPlayer == 0) {
		otherPlayer = 1;
	}
	else {
		otherPlayer = 0;
	}

	int oldBuys = G.numBuys; 
	int oldCountCurrent = G.handCount[currentPlayer];
	int oldCountOther = G.handCount[otherPlayer]; 

	
	//int test = playCouncilRoom(1, &G, 0)	
	int test = cardEffect(council_room, choice1, choice2, choice3, &G, 0, &bonus);
	printf("Checking successful completion of function...\n");
	asserttrue(test == 0);
	printf("Checking for correct number of buys...\n");
	asserttrue(G.numBuys == oldBuys + 1);
	printf("Checking for correct handCount for currentPlayer...\n");
	asserttrue(G.handCount[currentPlayer] == oldCountCurrent + 3);
	printf("Checking for correct handCount for otherPlayer...\n");
	asserttrue(G.handCount[otherPlayer] == oldCountOther + 1);	

}

int main() {

	testCouncilRoom(); 
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