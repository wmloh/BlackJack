#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gameEngine.h"

static char *hit = "hit";
static char *stand = "stand";

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

static bool commandLine(bool *endTurn, bool *inGame, struct Player *player, struct Deck *deck) {
	char input[8];
	while (!scanf("%s", &input)) {}
		if (!strcmp(input, "quit")) {
			return false;
		} else if (!strcmp(input, hit)) {
			hitCard(player, deck);
			displayCards(player);
		} else if (!strcmp(input, stand)) {
			updateActionSeq(player, stand);
			*endTurn = true;
			*inGame = false;
		} else if (!strcmp(input, "-help")) {
			printf("Commands:\n *%s\n *%s\n *quit\n", hit, stand);
		} else {
			printf("Invalid command. Type -help for more information.\n");
		}
	return true;
}

void initGame(struct Player **players, int numPlayers, int *bets, struct Player *dealer) {

	struct Deck *deck = initDeck();

	placeAllBets(players, bets, numPlayers);

	bool *inGame = malloc(sizeof(bool) * numPlayers);
	bool *busted = malloc(sizeof(bool) * numPlayers);
	int *curValue = malloc(sizeof(int) * numPlayers);

	bool dealerInGame = true;
	bool dealerBusted = false;
	int dealerCurValue;

	#pragma omp parallel for
	for(int i = 0; i < numPlayers; ++i) {
		hitCard(players[i], deck);
		hitCard(players[i], deck);
		inGame[i] = true;
		busted[i] = false;
	}
	hitCard(dealer, deck);
	hitCard(dealer, deck);

	struct Player *player;
	bool endTurn;

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
			
			if(!commandLine(&endTurn, &inGame[i], player, deck)) {
				goto quickEnd;
			}

		}
		printf("^^^^^^^^^^^^\n");
	}

	printf("\nvvvvvv %s vvvvvv\n", getName(dealer));
	displayCards(dealer);
	endTurn = false;
	while(!endTurn) {
		if(checkBusted(dealer, &dealerCurValue)) {
			dealerInGame = false;
			endTurn = true;
			dealerBusted = true;
			break;
			printf("%s is busted\n", getName(dealer));
		} else {
			printf("Current sum: %i\n", dealerCurValue);
		}

		if(!commandLine(&endTurn, &dealerInGame, dealer, deck)) {
			goto quickEnd;
		}
	}
	printf("^^^^^^^^^^^^\n");

	for(int i = 0; i < numPlayers; ++i) {
		if (dealerBusted && !busted[i]) {
			winBet(players[i], dealer);
		} else if(!busted[i]) {
			if (curValue[i] > dealerCurValue) {
				winBet(players[i], dealer);
			} else if (curValue[i] < dealerCurValue) {
				loseBet(players[i], dealer);
			} else {
				drawBet(players[i], dealer);
			}
		} else {
			drawBet(players[i], dealer);
		}
	}

	quickEnd:
	freeDeck(deck);
	free(inGame);
	free(busted);
	free(curValue);
}