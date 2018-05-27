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

void testBuyCard() {

	printf("Testing the buyCard function.\n");
	srand(time(NULL));
	int randomSeed = rand();
	int k[10] = { gardens, village, council_room, adventurer, smithy, baron, great_hall, remodel, mine, feast };
	struct gameState G;
	int oldCoins; 

	int supplyPos = copper;
	G.coins = 1; 
	G.numBuys = 1; 
	int test = buyCard(supplyPos, &G); 
	printf("Testing successful completion of buyCard function...\n");
	asserttrue(test == -1);

	initializeGame(2, k, randomSeed, &G);

	// buy copper and check coins
	oldCoins = G.coins; 
	test = buyCard(supplyPos, &G);
	asserttrue(test == 0); 
	printf("Checking for correct coins...\n");
	asserttrue(oldCoins == G.coins - getCost(copper));					// copper costs 0 coins

	// try buying copper with 0 buys 
	G.coins = 5; 
	G.numBuys = 0; 
	test = buyCard(supplyPos, &G);
	printf("Checking for correct buys...\n");
	asserttrue(test == -1);											

	// try buying silver with 0 coins
	G.coins = 0; 
	G.numBuys = 1; 
	supplyPos = silver; 
	printf("Checking for enough coins...\n");
	test = buyCard(supplyPos, &G);    
	asserttrue(test == -1); 
}


int main() {
    
    testBuyCard(); 
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