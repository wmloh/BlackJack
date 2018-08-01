#include <stdlib.h>
#include <stdio.h>
#include "gameInit.h"

#define NUMLINES 8

static char *quit = "quit";
static char *new = "new";
static char *pop = "pop";
static char *money = "money";
static char *dealer = "dealer";
static char *end = "end";
static char *help = "-help";

static bool commandLine(struct dArray *playerNames, char **dealerName, int *playerMoney, int *dealerMoney) {
	char *input;
	char *answer;
	
	while(true) {
		input = getInput();
		if(!strcmp(input, quit)) {
			free(input);
			exit(0);
		} else if (!strcmp(input, new)) {
			printf("Player name?: ");
			answer = getInput();
			appendObj(playerNames, answer);
		} else if (!strcmp(input, pop)) {
			void *obj = removeObj(playerNames);
			printf("%s removed\n", (char *)obj);
			free(obj);
		} else if (!strcmp(input, money)) {
			printf("Enter amount: ");
			answer = getInput();
			*playerMoney = atoi(answer);
			free(answer);
		} else if (!strcmp(input, dealer)) {
			printf("Dealer name?: ");
			*dealerName = getInput();
			printf("Enter amount: ");
			answer = getInput();
			*dealerMoney = atoi(answer);
			free(answer);
		} else if (!strcmp(input, end)) {
			printf("\nPlayers: ");
			int len = getLen(playerNames);
			for(int i = 0; i < len; ++i) {
				printf("%s ", getObj(playerNames, i));
			}
			printf("\nInitial amount of money: $%i\n", *playerMoney);
			printf("The dealer (%s) has $%i\n\n", *dealerName, *dealerMoney);
			return true;
		} else if (!strcmp(input, help)) {
			FILE *fp = fopen("instructions.txt", "r");
			char str[100];
			for(int i = 0; i < NUMLINES; ++i) {
				printf("%s", fgets(str, 99, fp));
			}
			fclose(fp);
		} else {
			printf("Invalid command. Type -help for more information.\n");
		}
	}
}

void initGame(void) {

	struct dArray *playerNames = initdArray();

	char *dealerName;
	int money;
	int dealerMoney;

	if(!commandLine(playerNames, &dealerName, &money, &dealerMoney)){
		goto quickEnd;
	}

	int len;
	struct Player **players;
	struct Player *dealer;
	while(true) {
		printf("Type \"play\", \"reconfigure\" or \"quit\"\n");
		char *input = getInput();
		len = getLen(playerNames);
		if(!strcmp(input, "play")) {
			int *bets = malloc(sizeof(int) * len);
			char *amount;
			for(int i = 0; i < len; ++i) {
				printf("Bet amount for %s: ", getObj(playerNames, i));
				amount = getInput();
				bets[i] = atoi(amount);
				free(amount);
			}

			players = initAllPlayers(playerNames, money);
			dealer = initPlayer(dealerName, dealerMoney);

			initRound(players, len, bets, dealer);

			for(int i = 0; i < len; ++i) {
				printf("%s: $%i\n", getName(players[i]), getMoney(players[i]));
			}
			
			printf("%s: $%i\n", getName(dealer), getMoney(dealer));
			free(bets);
		} else if (!strcmp(input, "reconfigure")) {
			commandLine(playerNames, &dealerName, &money, &dealerMoney);
		} else if (!strcmp(input, quit)) {
			exit(0);
		} else {
			printf("Invalid command. Type either \"play\", \"reconfigure\" or \"quit\".\n");
		}
		free(input);
	}

	quickEnd:
	while(getLen(playerNames)) {
		removeObj(playerNames);
	}
	freeArray(playerNames);
	freeAllPlayers(players, len);
	freePlayer(dealer);
	
}