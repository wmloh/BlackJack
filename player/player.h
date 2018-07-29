#include "../deck/deck.h"

struct Player;

struct Player *initPlayer(char *name, long money);

struct Player **initAllPlayers(int numPlayers, char **playerNames, long money);

void freePlayer(struct Player *player);

void freeAllPlayers(struct Player **players, int numPlayers);

void refreshPlayer(struct Player *player);

void updateCardsAtHand(struct Player *player, char *card);

void updateActionSeq(struct Player *player, char *action);

char **getCardsAtHand(struct Player *player);

int updateNum(struct Player *player);

int getNum(struct Player *player);

char *getName(struct Player *player);

long getMoney(struct Player *player);

bool placeBets(struct Player *player, int amount);

void winBet(struct Player *winner, struct Player **players, int numPlayers);

char *hitCard(struct Player *player, struct Deck *deck);

void displayCards(struct Player *player);