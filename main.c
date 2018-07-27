#include <stdio.h>
#include <stdlib.h>
#include "./deck/deck.h"
#include "./player/player.h"
#include <string.h>

int main(void) {

	struct Deck *deck = initDeck();
	struct Player *player = initPlayer();

	bool play = true;
	printf("%s\n", drawCard(deck));

	char *hit = "hit";
	char *stand = "stand";

	char input[8];
	int result = 0;

	while (play) {
		while (!result) {
			result = scanf("%s", &input);
		}
		if (!strcmp(input, "quit")) {
			break;
		} else if (!strcmp(input, hit)) {
			char *card = drawCard(deck);
			updateCardsAtHand(player, card);
			updateActionSeq(player, hit);
			printf("NumCards: %i\n", updateNum(player));
			printf("Pass\n");
		} else if (!strcmp(input, stand)) {
			updateActionSeq(player, stand);
		} else if (!strcmp(input, "-help")) {
			printf("");
		} else {
			printf("Invalid command. Type -help for more information.\n");
		}
		displayCards(player);
		result = 0;
	}


	free(getCardsLeft(deck));
	free(getAllCards(deck));
	free(deck);
}