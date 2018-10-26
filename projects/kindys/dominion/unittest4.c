/*
 * Sonam Kindy
 * CS362
 * Unit Test 3: gainCard
 * Created: 10/25/18
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>

#define FUNCTION    "gainCard"

void testGainCard()
{
    struct gameState* state = (struct gameState*)malloc(sizeof(struct gameState));
    state->whoseTurn = 0;
    state->supplyCount[province] = 0; // set number of province cards in supply to zero
    int player = state->whoseTurn;

	printf("TEST 1: 0 province cards left in supply\n");
    if(gainCard(province, state, 0, player) == -1)
    	printf("gainCard(): PASSED when testing 0 province cards left to gain in supply\n\n");
    else
    	printf("gainCard(): FAILED when testing 0 province cards left to gain in supply\n\n");

    state->supplyCount[province] = 1; // set number of province cards in supply to 1
    state->discardCount[state->whoseTurn] = 10; // set number of cards in player's discard pile to 10
    
    // fill player discard pile with dummy cards (all duchy)
    for(int i = 0; i < state->discardCount[state->whoseTurn]; i++)
        state->discard[state->whoseTurn][i] = duchy;

	printf("TEST 2: 1 province card left in supply to be gained by player and placed in their discard pile\n");
    if(gainCard(province, state, 0, player) == 0 &&
    	state->discard[state->whoseTurn][state->discardCount[state->whoseTurn] - 1] == province &&
    	state->discardCount[state->whoseTurn] == 11)
    	printf("gainCard(): PASSED when testing 1 province card gained and placed in discard\n\n");
    else
    	printf("gainCard(): FAILED when testing 1 province card gained and placed in discard\n\n");

    state->supplyCount[province] = 1; // set number of province cards in supply to 1
    state->deckCount[state->whoseTurn] = 10; // set number of cards in player's discard pile to 10
    
    // fill player deck with dummy cards (all duchy)
    for(int i = 0; i < state->deckCount[state->whoseTurn]; i++)
        state->deck[state->whoseTurn][i] = duchy;

	printf("TEST 3: 1 province card left in supply to be gained by player and placed in their deck\n");
    if(gainCard(province, state, 1, player) == 0 &&
    	state->deck[state->whoseTurn][state->deckCount[state->whoseTurn] - 1] == province &&
    	state->deckCount[state->whoseTurn] == 11)
    	printf("gainCard(): PASSED when testing 1 province card gained and placed in deck\n\n");
    else
    	printf("gainCard(): FAILED when testing 1 province card gained and placed in deck\n\n");

    state->supplyCount[province] = 1; // set number of province cards in supply to 1
    state->handCount[state->whoseTurn] = 10; // set number of cards in player's discard pile to 10
    
    // fill player deck with dummy cards (all duchy)
    for(int i = 0; i < state->handCount[state->whoseTurn]; i++)
        state->hand[state->whoseTurn][i] = duchy;

	printf("TEST 4: 1 province card left in supply to be gained by player and placed in their hand\n");
    if(gainCard(province, state, 1, player) == 0 &&
    	state->hand[state->whoseTurn][state->handCount[state->whoseTurn] - 1] == province &&
    	state->handCount[state->whoseTurn] == 11)
    	printf("gainCard(): PASSED when testing 1 province card gained and placed in hand\n\n");
    else
    	printf("gainCard(): FAILED when testing 1 province card gained and placed in hand\n\n");

    free(state);
}

int main(int argc, char *argv[])
{
	printf("----------------- Unit testing fn %s ----------------\n\n", FUNCTION);
    testGainCard();
    printf(">>>>>> SUCCESS: Unit testing complete of fn %s <<<<<<\n\n", FUNCTION);

    return 0;
}