#include <stdlib.h>
#include <stdio.h>
#include "./gameEngine/gameEngine.h"
#include "./player/player.h"

#define NUMPLAYERS 2

int main(void) {

	char *playerNames[NUMPLAYERS] = {"p1", "p2"};

	int bets[] = {10, 10};
	int money = 100;
	int dealerMoney = 200;

	struct Player **players = initAllPlayers(NUMPLAYERS, playerNames, money);
	struct Player *dealer = initPlayer("dealer", dealerMoney);

	initGame(players, NUMPLAYERS, bets, dealer);

	for(int i = 0; i < NUMPLAYERS; ++i) {
		printf("%i\n", getMoney(players[i]));
	}
	
	printf("%i\n", getMoney(dealer));

	freeAllPlayers(players, NUMPLAYERS);
	freePlayer(dealer);
}