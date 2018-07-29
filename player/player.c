#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "player.h"
#include <omp.h>

#define MAXDRAWS 7

struct Player {
	char *name;
	int numCards;
	int currBet;
	long money;
	char **cardsAtHand;
	char **actionSeq;
};

struct Player *initPlayer(char *name, long money) {
	struct Player *player = malloc(sizeof(struct Player));
	player->name = malloc(sizeof(char) * (strlen(name) + 1));
	strcpy(player->name, name);
	player->numCards = 0;
	player->currBet = 0;
	player->money = money;
	player->cardsAtHand = malloc(sizeof(char *) * MAXDRAWS);
	player->actionSeq = malloc(sizeof(char *) * MAXDRAWS);
	return player;
}

struct Player **initAllPlayers(int numPlayers, char **playerNames, long money) {
	struct Player **players = malloc(sizeof(struct Player *) * numPlayers);
	#pragma omp parallel for
	for(int i = 0; i < numPlayers; ++i) {
		players[i] = initPlayer(playerNames[i], money);
	}
	return players;
}

void freePlayer(struct Player *player) {
	free(player->cardsAtHand);
	free(player->actionSeq);
	free(player->name);
	free(player);
}

void freeAllPlayers(struct Player **players, int numPlayers) {
	#pragma omp parallel for
	for(int i = 0; i < numPlayers; ++i) {
		freePlayer(players[i]);
	}
	free(players);
}

void refreshPlayer(struct Player *player) {
	player->numCards = 0;
}

void updateCardsAtHand(struct Player *player, char *card) {
	(player->cardsAtHand)[player->numCards] = card;
}

void updateActionSeq(struct Player *player, char *action) {
	(player->actionSeq)[player->numCards] = action;
}

char **getCardsAtHand(struct Player *player) {
	return player->cardsAtHand;
}

int updateNum(struct Player *player) {
	(player->numCards)++;
	return player->numCards;
}

int getNum(struct Player *player) {
	return player->numCards;
}

char *getName(struct Player *player) {
	return player->name;
}

long getMoney(struct Player *player) {
	return player->money;
}

bool placeBets(struct Player *player, int amount) {
	if (player->money >= amount) {
		player->money -= amount;
		player->currBet = amount;
		return true;
	}
	return false;
}

void winBet(struct Player *winner, struct Player **players, int numPlayers) {
	for(int i = 0; i < numPlayers; ++i) {
		winner->money += (players[i])->currBet;
		(players[i])->currBet = 0;
		refreshPlayer(players[i]);
	}
}

char *hitCard(struct Player *player, struct Deck *deck) {
	char *card = drawCard(deck);
	updateCardsAtHand(player, card);
	updateActionSeq(player, "hit");
	updateNum(player);
	return card;
}

void displayCards(struct Player *player) {
	int numCards = player->numCards;

	if (numCards == 1) {
		printf("%s\n", (player->cardsAtHand)[0]);
		return;
	} else if (numCards == 0) {
		return;
	} else {
		int len = numCards - 1;
		for (int i = 0; i < len; ++i) {
			printf("%s, ", (player->cardsAtHand)[i]);
		}
		printf("%s\n", (player->cardsAtHand)[len]);
	}
	

}