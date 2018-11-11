/*
 * Sonam Kindy
 * CS362
 * Card Test 2: Village
 * Created: 10/25/18
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "unittests.h"

#define TESTCARD    "Village"

void asserttrue(bool expr)
{
    if(expr)
        printf( ANSI_COLOR_GREEN     "PASSED ✅\n\n" ANSI_COLOR_RESET);
    else
        printf( ANSI_COLOR_RED     "FAILED ❌\n\n" ANSI_COLOR_RESET);
}

void printStart()
{
    printf( ANSI_COLOR_MAGENTA  "----------------- " ANSI_COLOR_RESET
            "Unit testing card %s"
            ANSI_COLOR_MAGENTA  " ----------------\n\n" ANSI_COLOR_RESET, TESTCARD);
}

void printEnd()
{
    printf( ANSI_COLOR_MAGENTA  ">>>>>>"    ANSI_COLOR_RESET
            " DONE: Unit testing complete for %s card"
            ANSI_COLOR_MAGENTA  " <<<<<<\n\n"    ANSI_COLOR_RESET, TESTCARD);
}

void printHeader(char* header)
{
    if(strstr(header, "CHECK"))
        printf(ANSI_COLOR_BLUE  "%s"    ANSI_COLOR_RESET, header);
    else
        printf(ANSI_COLOR_CYAN  "%s"    ANSI_COLOR_RESET, header);
}

void testVillageCard()
{
    int kingdomCards[10] = {
        adventurer, 
        embargo, 
        village, 
        minion, 
        mine, 
        cutpurse,
        sea_hag, 
        tribute, 
        smithy, 
        council_room
    };

    int newCards = 1;
    int discarded = 1;
    int extraActions = 2;
    // int shuffledCards = 0; ???

    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 100;
    int numPlayers = 2;
    int currentPlayer = 0;
    int nextPlayer = 1;
    struct gameState* state = (struct gameState*)malloc(sizeof(struct gameState));
    struct gameState* testState = (struct gameState*)malloc(sizeof(struct gameState));

    initializeGame(numPlayers, kingdomCards, seed, state); // initialize a game state and player cards
    int card = state->hand[currentPlayer][handPos];
    if(card != village) {
        state->supplyCount[card]++;
        state->supplyCount[village]--;
        state->hand[currentPlayer][handPos] = village; // ensure the first card in player's hand is Village
    }
    memcpy(testState, state, sizeof(struct gameState)); // copy contents of state to testState for comparisons
    
    // check first card in hand; should be Village -- for tests to work
    printHeader("CHECK PRE-PLAY:");
    printf(" first card in hand...\nfirst card in hand: %d; expected = %d\n", 
            testState->hand[currentPlayer][handPos], village);
    asserttrue(testState->hand[currentPlayer][handPos] == village);

    printHeader("CHECK PRE-PLAY:");
    printf(" num actions...\nnum actions = %d; expected = %d\n", testState->numActions, 1);
    asserttrue(testState->numActions == 1);

    // check num discarded/played cards of player; should be 0 at start of game
    printHeader("CHECK PRE-PLAY:");
    printf(" num discarded...\nnum discarded = %d; expected = %d\n", testState->playedCardCount, 0);
    asserttrue(testState->playedCardCount == 0);

    // check first card in other player's hand; should be the same pre/post currentPlayer's play
    printHeader("CHECK PRE-PLAY (nextPlayer):");
    printf(" first card in hand...\nfirst card in hand: %d, expected = %d\n", 
            testState->hand[nextPlayer][handPos], state->hand[nextPlayer][handPos]);
    asserttrue(testState->hand[nextPlayer][handPos] == state->hand[nextPlayer][handPos]);

    // check hand count for other player; should be the same pre/post currentPlayer's play
    printHeader("CHECK PRE-PLAY (nextPlayer):");
    printf(" hand count...\nhand count = %d; expected = %d\n", testState->handCount[nextPlayer], state->handCount[nextPlayer]);
    asserttrue(testState->handCount[nextPlayer] == state->handCount[nextPlayer]);

    cardEffect(village, choice1, choice2, choice3, testState, handPos, &bonus); // play Village card

    printHeader("PLAYING CARD:");
    printf(" %s (when game just initialized)\n\n", TESTCARD);
    
    // check hand count should be remain the same (Village adds +1 card; trash Village card)
    printHeader("CHECK POST-PLAY:");
    printf(" hand count...\nhand count = %d; expected = %d\n", testState->handCount[currentPlayer], state->handCount[currentPlayer] + newCards - discarded);
    asserttrue(testState->handCount[currentPlayer] == state->handCount[currentPlayer] + newCards - discarded);
    
    // check deck count should be 1 less (Village adds +1 card)
    printHeader("CHECK POST-PLAY:");
    printf(" deck count...\ndeck count = %d; expected = %d\n", testState->deckCount[currentPlayer], state->deckCount[currentPlayer] - newCards);
    asserttrue(testState->deckCount[currentPlayer] == state->deckCount[currentPlayer] - newCards);
    
    // check num of actions should be 2 more (Village adds +2 action)
    printHeader("CHECK POST-PLAY:");
    printf(" num actions...\nnum actions = %d; expected = %d\n", testState->numActions, state->numActions + extraActions);
    asserttrue(testState->numActions == state->numActions + extraActions);

    // check num discarded/played cards of player; should be 1 after playing Village
    printHeader("CHECK POST-PLAY:");
    printf(" num played cards...\nnum played cards = %d; expected = %d\n", testState->playedCardCount, state->playedCardCount + discarded);
    asserttrue(testState->playedCardCount == state->playedCardCount + discarded);
    
    // check last played/discarded card; should be Village
    printHeader("CHECK POST-PLAY:");
    printf(" last played card...\nlast played card: %d; expected = %d\n", testState->playedCards[testState->playedCardCount - 1], state->hand[currentPlayer][handPos]);
    asserttrue(testState->playedCards[testState->playedCardCount - 1] == state->hand[currentPlayer][handPos]);

    // check num discarded/played cards of player; should be 1 after playing Village
    printHeader("CHECK POST-PLAY:");
    printf(" num discarded...\nnum discarded = %d; expected = %d\n", testState->discardCount[currentPlayer], state->discardCount[currentPlayer] + discarded);
    asserttrue(testState->discardCount[currentPlayer] == state->discardCount[currentPlayer] + discarded);
    
    // check last played/discarded card; should be Village
    printHeader("CHECK POST-PLAY:");
    printf(" last discarded...\nlast discarded card: %d; expected = %d\n", testState->discard[currentPlayer][testState->discardCount[currentPlayer] - 1], state->hand[currentPlayer][handPos]);
    asserttrue(testState->discard[currentPlayer][testState->discardCount[currentPlayer] - 1] == state->hand[currentPlayer][handPos]);

    // check first card in other player's hand; should be the same pre/post currentPlayer's play
    printHeader("CHECK POST-PLAY (nextPlayer):");
    printf(" first card in hand...\nfirst card in hand: %d, expected = %d\n", 
            testState->hand[nextPlayer][handPos], state->hand[nextPlayer][handPos]);
    asserttrue(testState->hand[nextPlayer][handPos] == state->hand[nextPlayer][handPos]);

    // check hand count for other player; should be the same pre/post currentPlayer's play
    printHeader("CHECK POST-PLAY (nextPlayer):");
    printf(" hand count...\nhand count = %d; expected = %d\n", testState->handCount[nextPlayer], state->handCount[nextPlayer]);
    asserttrue(testState->handCount[nextPlayer] == state->handCount[nextPlayer]);

    // check supply count for kingdom cards
    printHeader("CHECK POST-PLAY:");
    printf(" supply count of each card...\n\n");
    int i;
    for(i = adventurer; i <= treasure_map; i++) {
        printf("card id: %d, supply count: %d; expected: %d\n", i, testState->supplyCount[i], state->supplyCount[i]);
        asserttrue(testState->supplyCount[i] == state->supplyCount[i]);
    }

    free(testState);
    free(state);
}

int main()
{
    printStart();
    testVillageCard();
    printEnd();

    return 0;
}