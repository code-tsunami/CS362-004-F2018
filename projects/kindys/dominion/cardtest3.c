/*
 * Sonam Kindy
 * CS362
 * Card Test 3: Adventurer
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

#define TESTCARD    "Adventurer"
#define NOISY_TEST  0

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
    
    #if NOISY_TEST
    printf("\nDETERMINING COINS AMOUNT FOR PLAYER %d\n", currentPlayer);
    #endif
    for(int i = 0; i < state->handCount[currentPlayer]; i++) {
        int card = state->hand[currentPlayer][i];
        if(card == copper)
            coinAmount++;
        else if(card == silver)
            coinAmount += 2;
        else if(card == gold)
            coinAmount += 3;
        #if NOISY_TEST
        printf("card: %d\n", card);
        #endif
    }

    return coinAmount;
}

void testAdventurerCard()
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

    int newCards = 2;
    int discarded = 1;
    int minCoins = 2;

    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 100;
    int numPlayers = 2;
    int currentPlayer = 0;
    struct gameState* state = (struct gameState*)malloc(sizeof(struct gameState));
    struct gameState* testState = (struct gameState*)malloc(sizeof(struct gameState));

    initializeGame(numPlayers, kingdomCards, seed, state); // initialize a game state and player cards
    state->hand[currentPlayer][handPos] = adventurer; // ensure the first card in player's hand is Adventurer
    memcpy(testState, state, sizeof(struct gameState)); // copy contents of state to testState for comparisons

    // check first card in hand; should be Adventurer -- for tests to work
    printHeader("CHECK PRE-PLAY:");
    printf(" first card in hand...\nfirst card in hand: %d; expected = %d\n", 
            testState->hand[currentPlayer][handPos], adventurer);
    asserttrue(testState->hand[currentPlayer][handPos] == adventurer);

    printHeader("CHECK PRE-PLAY:");
    printf(" num actions...\nnum actions = %d; expected = %d\n", testState->numActions, 1);
    asserttrue(testState->numActions == 1);

    int preNumTreasure = getNumTreasureCards(testState, currentPlayer);
    printHeader("CHECK PRE-PLAY:");
    printf(" num treasure cards...\nnum treasure cards = %d; expected = %d\n", preNumTreasure, 3);
    asserttrue(preNumTreasure == 3);

    printHeader("CHECK PRE-PLAY:");
    printf(" deck count...\ndeck count = %d\n\n", testState->deckCount[currentPlayer]);

    int preCoinAmount = getCoinAmount(testState, currentPlayer);    
    printHeader("CHECK PRE-PLAY:");
    printf(" coin amount...\ncoin amount = %d\n\n", preCoinAmount);

    // check num played cards of player; should be 0 at start of game
    printHeader("CHECK PRE-PLAY:");
    printf(" num discarded...\nnum discarded = %d; expected = %d\n", testState->playedCardCount, 0);
    asserttrue(testState->playedCardCount == 0);

    cardEffect(adventurer, choice1, choice2, choice3, testState, handPos, &bonus); // play Adventurer card

    printHeader("PLAYING CARD:");
    printf(" %s (when game just initialized)\n\n", TESTCARD);
    
    // check hand count; should be remain the same (Adventurer adds +1 card; trash Adventurer card)
    printHeader("CHECK POST-PLAY:");
    printf(" hand count...\nhand count = %d; expected = %d\n", testState->handCount[currentPlayer], state->handCount[currentPlayer] + newCards - discarded);
    asserttrue(testState->handCount[currentPlayer] == state->handCount[currentPlayer] + newCards - discarded);

    // check num of treasure cards; Adventurer adds +2 treasure cards to hand
    int postNumTreasure = getNumTreasureCards(testState, currentPlayer);
    printHeader("CHECK POST-PLAY:");
    printf(" num treasure cards...\nnum treasure cards = %d; expected = %d\n", postNumTreasure, getNumTreasureCards(state, currentPlayer) + newCards);
    asserttrue(postNumTreasure == getNumTreasureCards(state, currentPlayer) + newCards);

    // check deck count; dventurer has player pick up cards until +2 treasure cards added to hand
    printHeader("CHECK POST-PLAY:");
    printf(" deck count...\ndeck count = %d; expected <= %d\n", testState->deckCount[currentPlayer], state->playedCardCount - newCards);
    asserttrue(testState->deckCount[currentPlayer] <= state->deckCount[currentPlayer] - newCards);

    // check coin count; should be >= 5 since Adventurer adds +2 treasure cards
    int postCoinAmount = getCoinAmount(testState, currentPlayer);
    printHeader("CHECK POST-PLAY:");
    printf(" coin amount...\ncoin amount = %d; expected >= %d\n", postCoinAmount, getCoinAmount(state, currentPlayer) + minCoins);
    asserttrue(postCoinAmount >= getCoinAmount(state, currentPlayer) + minCoins);
    
    // check num of actions; should remain the same (no actions added with Adventurer)
    printHeader("CHECK POST-PLAY:");
    printf(" num actions...\nnum actions = %d; expected = %d\n", testState->numActions, state->numActions);
    asserttrue(testState->numActions == state->numActions);

    // check victory points; should increase by 1

    // check num played cards of player; should be 1 after playing Adventurer
    printHeader("CHECK POST-PLAY:");
    printf(" num played cards...\nnum played cards = %d; expected >= %d\n", testState->playedCardCount, state->playedCardCount + discarded);
    asserttrue(testState->playedCardCount >= state->playedCardCount + discarded);
    
    // check last played card; should be Adventurer
    printHeader("CHECK POST-PLAY:");
    printf(" last played card...\nlast played card: %d; expected = %d\n", testState->playedCards[testState->playedCardCount - 1], state->hand[currentPlayer][handPos]);
    asserttrue(testState->playedCards[testState->playedCardCount - 1] == state->hand[currentPlayer][handPos]);

    // check num discarded of player; should be >= 1 after playing Adventurer
    printHeader("CHECK POST-PLAY:");
    printf(" num discarded...\nnum discarded = %d; expected >= %d\n", testState->discardCount[currentPlayer], state->discardCount[currentPlayer] + discarded);
    asserttrue(testState->discardCount[currentPlayer] >= state->discardCount[currentPlayer] + discarded);
    
    // check last discarded card; should be Adventurer
    printHeader("CHECK POST-PLAY:");
    printf(" last discarded...\nlast discarded card: %d; expected = %d\n", testState->discard[currentPlayer][testState->discardCount[currentPlayer] - 1], state->hand[currentPlayer][handPos]);
    asserttrue(testState->discard[currentPlayer][testState->discardCount[currentPlayer] - 1] == state->hand[currentPlayer][handPos]);

    free(testState);
    free(state);
}

int main()
{
    printStart();
    testAdventurerCard();
    printEnd();

    return 0;
}