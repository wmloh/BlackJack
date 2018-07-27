#include <stdlib.h>
#include <stdio.h>
#include "player.h"

#define MAXDRAWS 5

struct Player {
	int score;
	int numCards;
	char **cardsAtHand;
	char **actionSeq;
};

struct Player *initPlayer(void) {
	struct Player *player = malloc(sizeof(struct Player));
	player->score = 0;
	player->numCards = 0;
	player->cardsAtHand = malloc(sizeof(char *) * MAXDRAWS);
	player->actionSeq = malloc(sizeof(char *) * MAXDRAWS);
	return player;
}

void updateCardsAtHand(struct Player *player, char *card) {
	(player->cardsAtHand)[player->numCards] = card;
}

void updateActionSeq(struct Player *player, char *action) {
	(player->actionSeq)[player->numCards] = action;
}

int updateNum(struct Player *player) {
	(player->numCards)++;
	return player->numCards;
}

void displayCards(struct Player *player) {
	if (player->numCards == 1) {
		printf("%s\n", (player->cardsAtHand)[0]);
		return;
	} else {
		int len = player->numCards - 1;
		for (int i = 0; i < len; ++i) {
			printf("%s, ", (player->cardsAtHand)[i]);
		}
		printf("%s\n", (player->cardsAtHand)[len]);
	}
	

}