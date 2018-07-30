#include "../deck/deck.h"

struct Player;

// initPlayer(name, money) returns a pointer to the struct Player with the money
//   and name specified
struct Player *initPlayer(char *name, long money);

// initAllPlayers(numPlayers, playerNames, money) returns an array of pointers to
//   the struct Player with playerNames and money standardized
struct Player **initAllPlayers(int numPlayers, char **playerNames, long money);

// freePlayer(player) frees all allocated memory associated to player
void freePlayer(struct Player *player);

// freePlayer(players, numPlayers) frees all allocated memory associated to
//   each player in players including players pointer
void freeAllPlayers(struct Player **players, int numPlayers);

// refreshPlayer(player) sets numCards of player to 0
void refreshPlayer(struct Player *player);

// updateCardsAtHand(player, card) mutates the array of cardsAtHand at current
//   index to card
void updateCardsAtHand(struct Player *player, char *card);

// updateActionSeq(player, action) mutates the array of actionSeq at current
//   index to action
void updateActionSeq(struct Player *player, char *action);

// getCardsAtHand(player) returns the cardsAtHand of player
char **getCardsAtHand(struct Player *player);

// updateNum(player) increments (mutates) the index of player and returns the value
int updateNum(struct Player *player);

// getNum(player) returns the index of the player
int getNum(struct Player *player);

// getName(player) returns the name of the player
char *getName(struct Player *player);

// getMoney(player) returns the current amount of money the player has
long getMoney(struct Player *player);

// placeBets(player, amount) returns true if and only if the player has enough
//   money to place bets
// effects: mutates the amount of money player has
//          mutates the currBet of the player
bool placeBets(struct Player *player, int amount);


void winBet(struct Player *winner, struct Player **players, int numPlayers);

// hitCard(player, deck) returns the card drawn
// effects: mutates the available of card in deck
//          mutates the cardsAtHand of player
char *hitCard(struct Player *player, struct Deck *deck);

// displayCards(player) prints the cards the player currently has
void displayCards(struct Player *player);