#include <stdlib.h>
#include <stdio.h>
#include "./gameEngine/gameEngine.h"
#include "./player/player.h"

int main(void) {

	char *playerNames[2] = {"p1", "p2"};

	int bets[] = {10, 10};
	int money = 100;

	struct Player **players = initAllPlayers(2, playerNames, money);

	initGame(players, 2, bets);

	printf("%i\n", getMoney(players[0]));
	printf("%i\n", getMoney(players[1]));

	initGame(players, 2, bets);

	printf("%i\n", getMoney(players[0]));
	printf("%i\n", getMoney(players[1]));

	freeAllPlayers(players, 2);
}