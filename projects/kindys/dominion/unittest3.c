/*
 * Sonam Kindy
 * CS362
 * Unit Test 3: isGameOver
 * Created: 10/25/18
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "unittests.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FUNCTION    "isGameOver"

void asserttrue(bool expr)
{
    if(expr)
        printf( ANSI_COLOR_GREEN     "PASSED ✅\n\n" ANSI_COLOR_RESET);
    else
        printf( ANSI_COLOR_RED     "FAILED ❌\n\n" ANSI_COLOR_RESET);
}

void testIsGameOver()
{
    struct gameState* state = (struct gameState*)malloc(sizeof(struct gameState));
    state->supplyCount[province] = 0; // set number of province cards in supply to zero

    printf("TEST 1: 0 province cards left in supply\n");
    printf("isGameOver: %d; expected: %d\n", isGameOver(state), 1);
    asserttrue(isGameOver(state) == 1);

    // set first three card types' (curse, estate and duchy) supply count to zero 
    for(int i = 0; i < 3; i++)
        state->supplyCount[i] = 0;
    // set the rest of the cards' supply counts to 1
    for(int i = 3; i < 25; i++)
        state->supplyCount[i] = 1;

    printf("TEST 2: 3 empty supply card piles\n");
    printf("isGameOver: %d; expected: %d\n", isGameOver(state), 1);
    asserttrue(isGameOver(state) == 1);

    // set the supply count of all card types (25 in total) to 1 
    for(int i = 0; i < 25; i++)
        state->supplyCount[i] = 1;

    printf("TEST 3: no supply cards empty\n");
    printf("isGameOver: %d; expected: %d\n", isGameOver(state), 0);
    asserttrue(isGameOver(state) == 0);

    // set the supply count for first two card types to zero
    for(int i = 0; i < 2; i++)
        state->supplyCount[i] = 0;

    printf("TEST 4: 2 supply cards empty\n");
    printf("isGameOver: %d; expected: %d\n", isGameOver(state), 0);
    asserttrue(isGameOver(state) == 0);

    free(state);
}

int main(int argc, char *argv[])
{
    printf("----------------- Unit testing fn %s ----------------\n\n", FUNCTION);
    testIsGameOver();
    printf(">>>>>> SUCCESS: Unit testing complete of fn %s <<<<<<\n\n", FUNCTION);
    
    return 0;
}