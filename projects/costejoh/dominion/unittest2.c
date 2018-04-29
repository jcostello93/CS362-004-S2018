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


void testIsGameOver() {
	printf("Testing isGameOver function.\n");
	srand(time(NULL));
	int randomSeed = rand();

	int k[10] = { gardens, village, council_room, adventurer, smithy, baron, great_hall, remodel, mine, feast };
	struct gameState G;

	initializeGame(2, k, randomSeed, &G);

	// no more provinces left 
	G.supplyCount[province] = 0; 
	int test = isGameOver(&G); 
	printf("Checking for 0 provinces...\n");
	asserttrue(test == 1); 

	// 3 empty piles
	G.supplyCount[province] = 1; 
	G.supplyCount[adventurer] = 0; 
	G.supplyCount[council_room] = 0; 
	G.supplyCount[feast] = 0; 
	test = isGameOver(&G);
	printf("Checking for 3 empty stacks...\n");
	asserttrue(test == 1);

	// game not over
	G.supplyCount[adventurer] = 1; 
	G.supplyCount[council_room] = 1; 
	G.supplyCount[feast] = 1; 
	test = isGameOver(&G); 
	printf("Checking for ongoing game...\n");
	asserttrue(test == 0); 

}

int main() {

	testIsGameOver(); 
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