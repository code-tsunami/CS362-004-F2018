/*
 * Sonam Kindy
 * CS362
 * Unit Test 3: isGameOver
 * Created: 10/25/18
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

#define FUNCTION    "isGameOver"

void testIsGameOver()
{
	struct gameState* state = (struct gameState*)malloc(sizeof(struct gameState));
    state->supplyCount[province] = 0; // set number of province cards in supply to zero

    isGameOver(state);

    if (isGameOver(state) == 1)
        printf("isGameOver(): PASSED when testing 0 province cards left in supply\n\n");
    else
        printf("isGameOver(): FAILED when testing 0 province cards left in supply\n\n");

    // set first three card types' (curse, estate and duchy) supply count to zero 
    for(int i = 0; i < 3; i++)
        state->supplyCount[i] = 0;
    // set the rest of the cards' supply counts to 1
    for(int i = 3; i < 25; i++)
    	state->supplyCount[i] = 1;

    isGameOver(state);

    if (isGameOver(state) == 1)
        printf("isGameOver(): PASSED when testing there are 3 empty supply card piles\n\n");
    else
        printf("isGameOver(): FAILED when testing there are 3 empty supply card piles\n\n");

    // set the supply count of all card types (25 in total) to 1 
    for(int i = 0; i < 25; i++)
    	state->supplyCount[i] = 1;

    if (isGameOver(state) == 0)
        printf("isGameOver(): PASSED when testing game should continue\n\n");
    else
        printf("isGameOver(): FAILED when testing game should continue\n\n");

    free(state);
}

int main(int argc, char *argv[])
{
    printf("----------------- Unit testing fn %s ----------------\n\n", FUNCTION);
    testIsGameOver();
    printf(">>>>>> SUCCESS: Unit testing complete of fn %s <<<<<<\n\n", FUNCTION);
    
    return 0;
}