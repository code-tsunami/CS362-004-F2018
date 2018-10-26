/*
 * Sonam Kindy
 * CS362
 * Unit Test 2: buyCard
 * Created: 10/25/18
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

#define FUNCTION    "buyCard"

void testBuyCard()
{
    struct gameState* state = (struct gameState*)malloc(sizeof(struct gameState));
    state->whoseTurn = 0;
    state->numBuys = 0;

    printf("TEST 1: numBuys < 1, i.e. numBuys = 0\n");
    if (buyCard(estate, state) == -1)
        printf("buyCard(): PASSED when testing numBuys < 1\n\n");
    else
        printf("buyCard(): FAILED when testing numBuys < 1\n\n");

    state->supplyCount[estate] = 0;
    state->numBuys = 1;

    printf("TEST 2: supplyCount of estate cards = 0\n");
    if (buyCard(estate, state) == -1)
        printf("buyCard(): PASSED when testing no cards of that type left to buy\n\n");
    else
        printf("buyCard(): FAILED when testing no cards of that type left to buy\n\n");

    state->supplyCount[estate] = 1;
    state->numBuys = 1;
    state->coins = 1;

    printf("TEST 3: coins = 1; attempting to buy estate, which costs 2 coins\n");
    if (buyCard(estate, state) == -1)
        printf("buyCard(): PASSED when testing NOT enough money to buy card\n\n");
    else
        printf("buyCard(): FAILED when testing NOT enough money to buy card\n\n");

    state->supplyCount[estate] = 1;
    state->numBuys = 1;
    state->coins = 2;
    state->discardCount[state->whoseTurn] = 10; // set number of cards in player's discard pile to 10
    
    // fill player discard pile with dummy cards (all duchy)
    for(int i = 0; i < state->discardCount[state->whoseTurn]; i++)
        state->discard[state->whoseTurn][i] = duchy;

    printf("TEST 4: coins = 2; attempting to buy estate, which costs 2 coins\n");
    if (buyCard(estate, state) == 0 && state->coins == 0 && 
        state->numBuys == 0 && state->discardCount[state->whoseTurn] == 11 &&
        state->discard[state->whoseTurn][state->discardCount[state->whoseTurn] - 1] == estate)
        printf("buyCard(): PASSED when testing enough money to buy card\n\n");
    else
        printf("buyCard(): FAILED when testing enough money to buy card\n\n");

    free(state);
}

int main(int argc, char *argv[])
{
    printf("----------------- Unit testing fn %s ----------------\n\n", FUNCTION);
    testBuyCard();
    printf(">>>>>> SUCCESS: Unit testing complete of fn %s <<<<<<\n\n", FUNCTION);

    return 0;
}