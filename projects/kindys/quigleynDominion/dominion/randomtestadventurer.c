/*
 * Sonam Kindy
 * CS362
 * Random Test - Card: Adventurer
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

#define TESTCARD    "Adventurer"

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

int getNumTreasureCards(struct gameState* state, int currentPlayer)
{
    int numTreasureCards = 0;
    
    for(int i = 0; i < state->handCount[currentPlayer]; i++) {
        int card = state->hand[currentPlayer][i];
        if(card == copper || card == silver || card == gold)
            numTreasureCards++;
    }

    return numTreasureCards;
}

int getCoinAmount(struct gameState* state, int currentPlayer)
{
    int coinAmount = 0;

    for(int i = 0; i < state->handCount[currentPlayer]; i++) {
        int card = state->hand[currentPlayer][i];
        if(card == copper)
            coinAmount++;
        else if(card == silver)
            coinAmount += 2;
        else if(card == gold)
            coinAmount += 3;
    }

    return coinAmount;
}

int checkGreatHall(int player, struct gameState* testState)
{
    int newCards = 2;
    int discarded = 1;
    int minCoins = 2;
    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

    int currentTestFailures = 0;

    struct gameState state;
    memcpy(&state, testState, sizeof(struct gameState));
    
    cardEffect(adventurer, choice1, choice2, choice3, testState, handPos, &bonus); // play Adventurer card
    
    // check hand count; should be remain the same (Adventurer adds +1 card; trash Adventurer card)
    printHeader("CHECKING");
    printf(" hand count...\nhand count = %d; expected = %d\n", testState->handCount[player], state.handCount[player] + newCards - discarded);
    currentTestFailures += asserttrue(testState->handCount[player] == state.handCount[player] + newCards - discarded);

    // check num of treasure cards; Adventurer adds +2 treasure cards to hand
    int postNumTreasure = getNumTreasureCards(testState, player);
    printHeader("CHECKING");
    printf(" num treasure cards...\nnum treasure cards = %d; expected = %d\n", postNumTreasure, getNumTreasureCards(&state, player) + newCards);
    currentTestFailures += asserttrue(postNumTreasure == getNumTreasureCards(&state, player) + newCards);

    // check deck count; dventurer has player pick up cards until +2 treasure cards added to hand
    printHeader("CHECKING");
    printf(" deck count...\ndeck count = %d; expected <= %d\n", testState->deckCount[player], state.playedCardCount - newCards);
    currentTestFailures += asserttrue(testState->deckCount[player] <= state.deckCount[player] - newCards);

    // check coin count; should be >= 5 since Adventurer adds +2 treasure cards
    int postCoinAmount = getCoinAmount(testState, player);
    printHeader("CHECKING");
    printf(" coin amount...\ncoin amount = %d; expected >= %d\n", postCoinAmount, getCoinAmount(&state, player) + minCoins);
    currentTestFailures += asserttrue(postCoinAmount >= getCoinAmount(&state, player) + minCoins);
    
    // check num of actions; should remain the same (no actions added with Adventurer)
    printHeader("CHECKING");
    printf(" num actions...\nnum actions = %d; expected = %d\n", testState->numActions, state.numActions);
    currentTestFailures += asserttrue(testState->numActions == state.numActions);

    // check victory points; should increase by 1
    printHeader("CHECKING");
    printf(" victory points...\nvictory points = %d; expected = %d\n", scoreFor(player, testState), scoreFor(player, &state) + 1);
    currentTestFailures += asserttrue(scoreFor(player, testState) == scoreFor(player, &state) + 1);

    // check num played cards of player; should be 1 after playing Adventurer
    printHeader("CHECKING");
    printf(" num played cards...\nnum played cards = %d; expected >= %d\n", testState->playedCardCount, state.playedCardCount + discarded);
    currentTestFailures += asserttrue(testState->playedCardCount >= state.playedCardCount + discarded);
    
    // check last played card; should be Adventurer
    printHeader("CHECKING");
    printf(" last played card...\nlast played card: %d; expected = %d\n", testState->playedCards[testState->playedCardCount - 1], state.hand[player][handPos]);
    currentTestFailures += asserttrue(testState->playedCards[testState->playedCardCount - 1] == state.hand[player][handPos]);

    // check num discarded of player; should be >= 1 after playing Adventurer
    printHeader("CHECKING");
    printf(" num discarded...\nnum discarded = %d; expected >= %d\n", testState->discardCount[player], state.discardCount[player] + discarded);
    currentTestFailures += asserttrue(testState->discardCount[player] >= state.discardCount[player] + discarded);
    
    // check last discarded card; should be Adventurer
    printHeader("CHECKING");
    printf(" last discarded...\nlast discarded card: %d; expected = %d\n", testState->discard[player][testState->discardCount[player] - 1], state.hand[player][handPos]);
    currentTestFailures += asserttrue(testState->discard[player][testState->discardCount[player] - 1] == state.hand[player][handPos]);

    return currentTestFailures;
}

void randomTestAdventurer()
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
        initializeGame(numPlayers, kingdomCards, Random() * 256, &state);
        int deckCount, discardCount, handCount;
        
        for (int j = 0; j < numPlayers; j++) {
            // the deck/discard/hand count all together need to be < 500
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
        int player = state.whoseTurn;

        int numTreasureCardsInDeck = 0;
        for(int i = 0; i < deckCount; i++) {
            if((state.deck[player][i] == gold) || (state.deck[player][i] == silver) || (state.deck[player][i] == copper))
                numTreasureCardsInDeck++;
        }
        if(numTreasureCardsInDeck < 1)
            state.deck[player][0] = copper;
        
        int numTreasureCardsInDiscard = 0;
        for(int i = 0; i < discardCount; i++) {
            if((state.discard[player][i] == gold) || (state.deck[player][i] == silver) || (state.deck[player][i] == copper))
                numTreasureCardsInDiscard++;
        }
        if(numTreasureCardsInDiscard < 1)
            state.discard[player][0] = copper;


        
        int handPos = 0;
        int card = state.hand[player][handPos];
        // ensure the first card in player's hand is Adventurer
        if(card != adventurer)
            state.hand[player][handPos] = adventurer;

        failedAsserts += checkGreatHall(player, &state);
    }
    printResults(failedAsserts);
}

int main()
{
    srand(time(NULL));
    printStart();
    randomTestAdventurer();

    return 0;
}