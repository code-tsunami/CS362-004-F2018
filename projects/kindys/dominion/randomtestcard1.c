/*
 * Sonam Kindy
 * CS362
 * Random Test - Card 1: Great Hall
 * Created: 11/13/18
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "unittests.h"

#define TESTCARD    "Great Hall"

int asserttrue(bool expr)
{
    if(expr) {
        printf("PASSED ✅\n\n");
        return 1;
    }
    printf("FAILED ❌\n\n");
    return 0;
}

void printStart()
{
    printf("----------------- "
            "Random testing card %s"
           " ----------------\n\n", TESTCARD);
}

void printHeader(char* header)
{
    printf("🔍 %s: ", header);
}

void printResults(int failedAssertions)
{
    if(failedAssertions)
        printf( ">>>>>> OH NO: Random testing complete for %s card; %d assertions failed"
                " <<<<<<\n\n", TESTCARD, failedAssertions);
    else
        printf(">>>>>> SUCCESS: Random testing complete for %s card; zero assertions failed"
           " <<<<<<\n\n", TESTCARD);
}

int checkGreatHall(int player, struct gameState* testState)
{
    int newCards = 1;
    int discarded = 1;
    int extraActions = 1;
    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

    int currentTestFailures = 0;

    struct gameState state;
    memcpy(&state, testState, sizeof(struct gameState));
    
    cardEffect(great_hall, choice1, choice2, choice3, testState, handPos, &bonus); // play Great Hall card

    // check hand count should be remain the same (Great Hall adds +1 card; discard Great Hall card)
    printHeader("CHECKING");
    printf(" hand count...\nhand count = %d; expected = %d\n", testState->handCount[player], state.handCount[player] + newCards - discarded);
    currentTestFailures += asserttrue(testState->handCount[player] == state.handCount[player] + newCards - discarded);
    
     // check deck count should be 1 less (Great Hall adds +1 card)
    printHeader("CHECKING");
    printf(" deck count...\ndeck count = %d; expected = %d\n", testState->deckCount[player], state.deckCount[player] - newCards);
    currentTestFailures += asserttrue(testState->deckCount[player] == state.deckCount[player] - newCards);
    
    // check coin count should remain the same (Great Hall adds no coins)
    printHeader("CHECKING");
    printf(" coins amount...\ncoins amount = %d; expected = %d\n", testState->coins, state.coins);
    currentTestFailures += asserttrue(testState->coins == state.coins);
    
    // check num of actions should be 1 more (Great Hall adds +1 action)
    printHeader("CHECKING");
    printf(" num actions...\nnum actions = %d; expected = %d\n", testState->numActions, state.numActions + extraActions);
    currentTestFailures += asserttrue(testState->numActions == state.numActions + extraActions);
    
    // check num discarded/played cards of player; should be 1 after playing Great Hall
    printHeader("CHECKING");
    printf(" num played cards...\nnum discarded = %d; expected = %d\n", testState->playedCardCount, state.playedCardCount + discarded);
    currentTestFailures += asserttrue(testState->playedCardCount == state.playedCardCount + discarded);
    
    // check last played/discarded card; should be Great Hall
    printHeader("CHECKING");
    printf(" last played card...\nlast played card: %d; expected = %d\n", testState->playedCards[testState->playedCardCount - 1], state.hand[player][handPos]);
    currentTestFailures += asserttrue(testState->playedCards[testState->playedCardCount - 1] == state.hand[player][handPos]);

    // check num discarded/played cards of player; should be 1 after playing Great Hall
    printHeader("CHECKING");
    printf(" num discarded...\nnum discarded = %d; expected = %d\n", testState->discardCount[player], state.discardCount[player] + discarded);
    currentTestFailures += asserttrue(testState->discardCount[player] == state.discardCount[player] + discarded);
    
    // check last played/discarded card; should be Great Hall
    printHeader("CHECKING");
    printf(" last discarded...\nlast discarded card: %d; expected = %d\n", testState->discard[player][testState->discardCount[player] - 1], state.hand[player][handPos]);
    currentTestFailures += asserttrue(testState->discard[player][testState->discardCount[player] - 1] == state.hand[player][handPos]);

    return currentTestFailures;
}

void randomTestVillage()
{
    int kingdomCards[10] = {
        smithy, 
        adventurer, 
        embargo, 
        village, 
        minion, 
        mine, 
        cutpurse,
        sea_hag, 
        tribute, 
        council_room
    };

    SelectStream(2);
    PutSeed(3);

    struct gameState state;
    int numTimesToTest = 2000;
    int failedAsserts = 0;
    
    for (int n = 0; n < numTimesToTest; n++) {
        for (int i = 0; i < sizeof(struct gameState); i++)
            ((char*)&state)[i] = floor(Random() * 256);

        int numPlayers = floor(Random() * 3) + 2; // min is 2; max is 4

        // initialize game state with a random seed
        initializeGame(numPlayers, kingdomCards, Random() * RAND_MAX, &state);
        for (int j = 0; j < numPlayers; j++) {
            // the deck/discard/hand count all together need to be < 500
            int deckCount, discardCount, handCount;
            do {
                deckCount = floor(Random() * MAX_DECK);
                discardCount = floor(Random() * MAX_DECK);
                handCount = floor(Random() * MAX_HAND);
            } while(deckCount + discardCount + handCount >= 500);

            state.deckCount[j] = deckCount;
            state.discardCount[j] = discardCount;
            state.handCount[j] = handCount;
        }
        state.whoseTurn = rand() % numPlayers;
        int currentPlayer = state.whoseTurn;
        
        int handPos = 0;
        int card = state.hand[currentPlayer][handPos];
        // ensure the first card in player's hand is Great Hall
        if(card != great_hall)
            state.hand[currentPlayer][handPos] = great_hall;

        failedAsserts += checkGreatHall(currentPlayer, &state);
    }
    printResults(failedAsserts);
}

int main()
{
    srand(time(NULL));
    printStart();
    randomTestVillage();

    return 0;
}