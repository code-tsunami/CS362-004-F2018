/*
 * Sonam Kindy
 * CS362
 * Unit Test 3: gainCard
 * Created: 10/25/18
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "unittests.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FUNCTION    "gainCard"

void asserttrue(bool expr)
{
    if(expr)
        printf( ANSI_COLOR_GREEN     "PASSED ✅\n\n" ANSI_COLOR_RESET);
    else
        printf( ANSI_COLOR_RED     "FAILED ❌\n\n" ANSI_COLOR_RESET);
}

void testGainCard()
{
    int res;
    struct gameState* state = (struct gameState*)malloc(sizeof(struct gameState));
    state->whoseTurn = 0;
    state->supplyCount[estate] = 0; // set number of estate cards in supply to zero
    int player = state->whoseTurn;

	printf("TEST 1: 0 estate cards left in supply\n");
    res = gainCard(estate, state, 0, player);
    printf("res of gainCard: %d; expected: %d\n", res, -1);
    asserttrue(res == -1);
    
    state->supplyCount[estate] = 1; // set number of estate cards in supply to 1
    state->discardCount[state->whoseTurn] = 10; // set number of cards in player's discard pile to 10
    
    // fill player discard pile with dummy cards (all duchy)
    for(int i = 0; i < state->discardCount[state->whoseTurn]; i++)
        state->discard[state->whoseTurn][i] = duchy;

	printf("TEST 2: 1 estate card left in supply to be gained by player and placed in their discard pile\n");
    res = gainCard(estate, state, 0, player);
    printf("res of gainCard: %d; expected: %d\n", res, 0);
    printf( "top of discard pile: %d; expected: %d\n", 
            state->discard[state->whoseTurn][state->discardCount[state->whoseTurn] - 1], estate);
    printf( "discard count: %d; expected: %d\n", 
            state->discardCount[state->whoseTurn], 11);
    asserttrue( res == 0 && 
                state->discard[state->whoseTurn][state->discardCount[state->whoseTurn] - 1] == estate &&
                state->discardCount[state->whoseTurn] == 11);

    state->supplyCount[estate] = 1; // set number of estate cards in supply to 1
    state->deckCount[state->whoseTurn] = 10; // set number of cards in player's discard pile to 10
    
    // fill player deck with dummy cards (all duchy)
    for(int i = 0; i < state->deckCount[state->whoseTurn]; i++)
        state->deck[state->whoseTurn][i] = duchy;

	printf("TEST 3: 1 estate card left in supply to be gained by player and placed in their deck\n");
    res = gainCard(estate, state, 1, player);
    printf("res of gainCard: %d; expected: %d\n", res, 0);
    printf( "top of deck: %d; expected: %d\n", 
            state->deck[state->whoseTurn][state->deckCount[state->whoseTurn] - 1], estate);
    printf( "deck count: %d; expected: %d\n", 
            state->deckCount[state->whoseTurn], 11);
    asserttrue( res == 0 && 
                state->deck[state->whoseTurn][state->deckCount[state->whoseTurn] - 1] == estate &&
                state->deckCount[state->whoseTurn] == 11);
    
    state->supplyCount[estate] = 1; // set number of estate cards in supply to 1
    state->handCount[state->whoseTurn] = 10; // set number of cards in player's discard pile to 10
    
    // fill player deck with dummy cards (all duchy)
    for(int i = 0; i < state->handCount[state->whoseTurn]; i++)
        state->hand[state->whoseTurn][i] = duchy;

	printf("TEST 4: 1 estate card left in supply to be gained by player and placed in their hand\n");
    res = gainCard(estate, state, 2, player);
    printf("res of gainCard: %d; expected: %d\n", res, 0);
    printf( "last card in hand: %d; expected: %d\n", 
            state->hand[state->whoseTurn][state->handCount[state->whoseTurn] - 1], estate);
    printf( "hand count: %d; expected: %d\n", 
            state->handCount[state->whoseTurn], 11);
    asserttrue( res == 0 && 
                state->hand[state->whoseTurn][state->handCount[state->whoseTurn] - 1] == estate &&
                state->handCount[state->whoseTurn] == 11);

    free(state);
}

int main(int argc, char *argv[])
{
	printf("----------------- Unit testing fn %s ----------------\n\n", FUNCTION);
    testGainCard();
    printf(">>>>>> SUCCESS: Unit testing complete of fn %s <<<<<<\n\n", FUNCTION);

    return 0;
}