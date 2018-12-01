CFLAGS= -Wall -fpic -coverage -lm -std=c99
CC = gcc
CARDTEST_NUMBERS = 1 2 3 4
CARDTEST_OUTFILE = unittestresults.out
RANDOMTEST_POSTFIX = card1 card2 adventurer
SHELL:=bash

rngs.o: rngs.h rngs.c
	$(CC) -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	$(CC) -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	$(CC) -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	$(CC)  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	$(CC) -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	$(CC) -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	$(CC) -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	$(CC) -c interface.c -g  $(CFLAGS)

unittests: cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o
	$(foreach el,$(CARDTEST_NUMBERS),$(CC) $(CFLAGS) cardtest$(el).c dominion.o rngs.o -o cardtest$(el);)

randomtests: randomtestcard1.c randomtestcard2.c randomtestadventurer.c dominion.o rngs.o
	$(foreach el,$(RANDOMTEST_POSTFIX),$(CC) $(CFLAGS) randomtest$(el).c dominion.o rngs.o -o randomtest$(el);)
	
runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittestresults: unittests
	echo "Result for running unit tests:" > $(CARDTEST_OUTFILE)
	$(foreach el,$(CARDTEST_NUMBERS),echo "cardtest$(el).c" >> $(CARDTEST_OUTFILE);./cardtest$(el) >> $(CARDTEST_OUTFILE);gcov -f -b dominion.c >> $(CARDTEST_OUTFILE);)

randomtestresults: randomtests
	$(foreach el,$(RANDOMTEST_POSTFIX),echo "Result for running randomcard tests:" > randomtest$(el).out;echo "randomtest$(el).c" >> randomtest$(el).out;./randomtest$(el) >> randomtest$(el).out;gcov -f -b dominion.c >> randomtest$(el).out;)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out \
	testDrawCard testDrawCard.exe
	$(foreach el,$(CARDTEST_NUMBERS),rm -f "cardtest$(el)";)
	$(foreach el,$(RANDOMTEST_POSTFIX),rm -f "randomtest$(el)";)

