/*
 * Sonam Kindy
 * CS362
 * Unit Test 2: buyCard
 * Created: 10/25/18
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "unittests.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FUNCTION    "buyCard"

void asserttrue(bool expr)
{
    if(expr)
        printf( ANSI_COLOR_GREEN     "PASSED ✅\n\n" ANSI_COLOR_RESET);
    else
        printf( ANSI_COLOR_RED     "FAILED ❌\n\n" ANSI_COLOR_RESET);
}

void testBuyCard()
{
    int res;
    struct gameState* state = (struct gameState*)malloc(sizeof(struct gameState));
    state->whoseTurn = 0;
    state->numBuys = 0;

    printf("TEST 1: attempting to buy estate; numBuys < 1, i.e. numBuys = 0\n");
    res = buyCard(estate, state);
    printf("res of buyCard: %d; expected: %d\n", res, -1);
    asserttrue(res == -1);
    
    state->supplyCount[estate] = 0;
    state->numBuys = 1;

    printf("TEST 2: attempting to buy estate; supplyCount of estate cards = 0\n");
    res = buyCard(estate, state);
    printf("res of buyCard: %d; expected: %d\n", res, -1);
    asserttrue(res == -1);
    
    state->supplyCount[estate] = 1;
    state->numBuys = 1;
    state->coins = 1;

    printf("TEST 3: attempting to buy estate, which costs 2 coins; coins = 1\n");
    res = buyCard(estate, state);
    printf("res of buyCard: %d; expected: %d\n", res, -1);
    asserttrue(res == -1);

    state->supplyCount[estate] = 1;
    state->numBuys = 1;
    state->coins = 2;
    state->discardCount[state->whoseTurn] = 10; // set number of cards in player's discard pile to 10
    
    // fill player discard pile with dummy cards (all duchy)
    for(int i = 0; i < state->discardCount[state->whoseTurn]; i++)
        state->discard[state->whoseTurn][i] = duchy;

    printf("TEST 4: attempting to buy estate, which costs 2 coins; coins = 2\n");
    res = buyCard(estate, state);
    printf( "res of buyCard: %d; expected: %d\n", res, 0);
    printf( "numBuys: %d; expected: %d\n", state->numBuys, 0);
    printf( "discard count: %d; expected: %d\n", state->discardCount[state->whoseTurn], 11);
    printf( "top of discard pile: %d; expected: %d\n", state->discard[state->whoseTurn][state->discardCount[state->whoseTurn] - 1], estate);
    asserttrue(res == 0 && state->coins == 0 && 
        state->numBuys == 0 && state->discardCount[state->whoseTurn] == 11 &&
        state->discard[state->whoseTurn][state->discardCount[state->whoseTurn] - 1] == estate);

    free(state);
}

int main(int argc, char *argv[])
{
    printf("----------------- Unit testing fn %s ----------------\n\n", FUNCTION);
    testBuyCard();
    printf(">>>>>> SUCCESS: Unit testing complete of fn %s <<<<<<\n\n", FUNCTION);

    return 0;
}