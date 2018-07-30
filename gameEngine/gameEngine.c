#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gameEngine.h"

// checkBusted(player, curValue) return true if and only if the cards
//   at hand exceeds 21
// effect: mutates curValue
static bool checkBusted(struct Player *player, int *curValue) {

	int sum = 0;
	int numAces = 0;
	int len = getNum(player);

	for(int i = 0; i < len; ++i) {
		char c = (getCardsAtHand(player))[i][0];
		if ('2' <= c && c <= '9') {
			sum += c - 48;
		} else if (c == '1' || c == 'J' || c == 'Q' || c == 'K') {
			sum += 10;
		} else {
			numAces++;
		}
	}

	if(numAces) {
		for(int i = 0; i < numAces; ++i) {
			if ((len == 2) && (sum + 11 == 21)) {
				sum = 21;
			} else if (sum + 11 <= 21) {
				sum += 11;
			} else {
				sum++;
			}
		}
	}

	*curValue = sum;

	if (sum <= 21) {
		return false;
	}
	return true;
}

static int placeAllBets(struct Player **players, int *bets, int numPlayers) {
	int totalBets = 0;
	#pragma omp parallel for
		for(int i = 0; i < numPlayers; ++i) {
			placeBets(players[i], bets[i]);
			totalBets += bets[i];
		}
	return totalBets;
}

void initGame(struct Player **players, int numPlayers, int *bets) {

	struct Deck *deck = initDeck();

	placeAllBets(players, bets, numPlayers);

	bool play = true;
	bool *inGame = malloc(sizeof(bool) * numPlayers);
	bool *busted = malloc(sizeof(bool) * numPlayers);
	int *curValue = malloc(sizeof(int) * numPlayers);

	#pragma omp parallel for
	for(int i = 0; i < numPlayers; ++i) {
		hitCard(players[i], deck);
		hitCard(players[i], deck);
		inGame[i] = true;
		busted[i] = false;
	}

	char *hit = "hit";
	char *stand = "stand";

	char input[8];
	struct Player *player;
	bool endTurn;
	int endRoundCount;

	while (play) {

		for(int i = 0; i < numPlayers && inGame[i]; ++i) {
			player = players[i];
			printf("\nvvvvvv %s vvvvvv\n", getName(player));
			displayCards(player);
			endTurn = false;
			while(!endTurn) {
				
				if (checkBusted(player, &(curValue[i]))) {
					inGame[i] = false;
					endTurn = true;
					busted[i] = true;
					printf("%s is busted\n", getName(player));
					continue;
				} else {
					printf("Current sum: %i\n", curValue[i]);
				}
				
				while (!scanf("%s", &input)) {}
				if (!strcmp(input, "quit")) {
					goto quickEnd;
				} else if (!strcmp(input, hit)) {
					hitCard(player, deck);
					displayCards(player);
				} else if (!strcmp(input, stand)) {
					updateActionSeq(player, stand);
					endTurn = true;
					inGame[i] = false;
				} else if (!strcmp(input, "-help")) {
					printf("Commands:\n *%s\n *%s\n *quit\n", hit, stand);
				} else {
					printf("Invalid command. Type -help for more information.\n");
				}
			}
			if(!play) {
				break;
			}
			printf("^^^^^^^^^^^^\n");
		}

		endRoundCount = 0;
		#pragma omp parallel for
		for(int i = 0; i < numPlayers; ++i) {
			if(!inGame[i]) {
				endRoundCount++;
			}
		}
		if(endRoundCount == numPlayers) {
			break;
		}
	}

	int maxValue = -1;
	int maxValueIndex = -1;

	for(int i = 0; i < numPlayers; ++i) {
		if(!busted[i] && curValue[i] > maxValue) {
			maxValueIndex = i;
			maxValue = curValue[i];
		}
	}

	winBet(players[maxValueIndex], players, numPlayers);

	quickEnd:
	freeDeck(deck);
	free(inGame);
	free(busted);
	free(curValue);
}