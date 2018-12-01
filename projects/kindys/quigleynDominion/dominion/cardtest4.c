/*
 * Sonam Kindy
 * CS362
 * Card Test 3: Smithy
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

#define TESTCARD    "Smithy"
#define NOISY_TEST  0

void asserttrue(bool expr)
{
    if(expr) 
        printf("PASSED ✅\n\n");
    else
        printf("FAILED ❌\n\n");
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

void printEnd()
{
    printf( ">>>>>>"
            " DONE: Unit testing complete for %s card"
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

void testSmithyCard()
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

    int newCards = 3;
    int discarded = 1;

    int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 100;
    int numPlayers = 2;
    int currentPlayer = 0;
    int nextPlayer = 1;
    struct gameState* state = (struct gameState*)malloc(sizeof(struct gameState));
    struct gameState* testState = (struct gameState*)malloc(sizeof(struct gameState));

    initializeGame(numPlayers, kingdomCards, seed, state); // initialize a game state and player cards
    int card = state->hand[currentPlayer][handPos];
    if(card != smithy) {
        state->supplyCount[card]++;
        state->supplyCount[smithy]--;
        state->hand[currentPlayer][handPos] = smithy; // ensure the first card in player's hand is Smithy
    }
    memcpy(testState, state, sizeof(struct gameState)); // copy contents of state to testState for comparisons

    // check first card in hand; should be Smithy -- for tests to work
    printHeader("CHECK PRE-PLAY");
    printf(" first card in hand...\nfirst card in hand: %d; expected = %d\n", 
            testState->hand[currentPlayer][handPos], smithy);
    asserttrue(testState->hand[currentPlayer][handPos] == smithy);

    printHeader("CHECK PRE-PLAY");
    printf(" num actions...\nnum actions = %d; expected = %d\n", testState->numActions, 1);
    asserttrue(testState->numActions == 1);

    printHeader("CHECK PRE-PLAY");
    printf(" deck count...\ndeck count = %d\n\n", testState->deckCount[currentPlayer]);

    // check num discarded/played cards of player; should be 0 at start of game
    printHeader("CHECK PRE-PLAY");
    printf(" num discarded...\nnum discarded = %d; expected = %d\n", testState->playedCardCount, 0);
    asserttrue(testState->playedCardCount == 0);

    // check first card in other player's hand; should be the same pre/post currentPlayer's play
    printHeader("CHECK PRE-PLAY (nextPlayer)");
    printf(" first card in hand...\nfirst card in hand: %d, expected = %d\n", 
            testState->hand[nextPlayer][handPos], state->hand[nextPlayer][handPos]);
    asserttrue(testState->hand[nextPlayer][handPos] == state->hand[nextPlayer][handPos]);

    // check hand count for other player; should be the same pre/post currentPlayer's play
    printHeader("CHECK PRE-PLAY (nextPlayer)");
    printf(" hand count...\nhand count = %d; expected = %d\n", testState->handCount[nextPlayer], state->handCount[nextPlayer]);
    asserttrue(testState->handCount[nextPlayer] == state->handCount[nextPlayer]);

    cardEffect(smithy, choice1, choice2, choice3, testState, handPos, &bonus); // play Smithy card

    printHeader("PLAYING CARD");
    printf(" %s (when game just initialized)\n\n", TESTCARD);
    
    // check hand count should be remain the same (Smithy adds +3 cards; discard Smithy card)
    printHeader("CHECK POST-PLAY");
    printf(" hand count...\nhand count = %d; expected = %d\n", testState->handCount[currentPlayer], state->handCount[currentPlayer] + newCards - discarded);
    asserttrue(testState->handCount[currentPlayer] == state->handCount[currentPlayer] + newCards - discarded);

    // check deck count (Smithy adds +3 cards to hand from deck)
    printHeader("CHECK POST-PLAY");
    printf(" deck count...\ndeck count = %d; expected: %d\n", testState->deckCount[currentPlayer], state->deckCount[currentPlayer] - newCards);
    asserttrue(testState->deckCount[currentPlayer] == state->deckCount[currentPlayer] - newCards);

    // check num of actions; should remain the same (Smithy adds no add'tl actions)
    printHeader("CHECK POST-PLAY");
    printf(" num actions...\nnum actions = %d; expected = %d\n", testState->numActions, state->numActions);
    asserttrue(testState->numActions == state->numActions);

    // check num played cards of player; should be 1 after playing Smithy
    printHeader("CHECK POST-PLAY");
    printf(" num played cards...\nnum played cards = %d; expected >= %d\n", testState->playedCardCount, state->playedCardCount + discarded);
    asserttrue(testState->playedCardCount >= state->playedCardCount + discarded);
    
    // check last played card; should be Smithy
    printHeader("CHECK POST-PLAY");
    printf(" last played card...\nlast played card: %d; expected = %d\n", testState->playedCards[testState->playedCardCount - 1], state->hand[currentPlayer][handPos]);
    asserttrue(testState->playedCards[testState->playedCardCount - 1] == state->hand[currentPlayer][handPos]);

    // check num discarded of player; should be 1 after playing Smithy
    printHeader("CHECK POST-PLAY");
    printf(" num discarded...\nnum discarded = %d; expected >= %d\n", testState->discardCount[currentPlayer], state->discardCount[currentPlayer] + discarded);
    asserttrue(testState->discardCount[currentPlayer] == state->discardCount[currentPlayer] + discarded);
    
    // check last discarded card; should be Smithy
    printHeader("CHECK POST-PLAY");
    printf(" last discarded...\nlast discarded card: %d; expected = %d\n", testState->discard[currentPlayer][testState->discardCount[currentPlayer] - 1], state->hand[currentPlayer][handPos]);
    asserttrue(testState->discard[currentPlayer][testState->discardCount[currentPlayer] - 1] == state->hand[currentPlayer][handPos]);

     // check first card in other player's hand; should be the same pre/post currentPlayer's play
    printHeader("CHECK POST-PLAY (nextPlayer)");
    printf(" first card in hand...\nfirst card in hand: %d, expected = %d\n", 
            testState->hand[nextPlayer][handPos], state->hand[nextPlayer][handPos]);
    asserttrue(testState->hand[nextPlayer][handPos] == state->hand[nextPlayer][handPos]);

    // check hand count for other player; should be the same pre/post currentPlayer's play
    printHeader("CHECK POST-PLAY (nextPlayer)");
    printf(" hand count...\nhand count = %d; expected = %d\n", testState->handCount[nextPlayer], state->handCount[nextPlayer]);
    asserttrue(testState->handCount[nextPlayer] == state->handCount[nextPlayer]);

    // check supply count for kingdom cards
    printHeader("CHECK POST-PLAY");
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
    testSmithyCard();
    printEnd();

    return 0;
}