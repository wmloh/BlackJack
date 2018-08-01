# BlackJack in C

## Command Line Interface
The game runs with command line (look at _"How to Use"_ section).

## Dependencies
* Cygwin

## How to Use

```
BlackJack
Welcome to BlackJack! Type -help for a list of commands
-> new
Player name?: p1
-> new
Player name?: p2
-> money
Enter amount: 100
-> dealer
Dealer name?: dealer1
Enter amount: 200
end

Players: p1 p2
Initial amount of money: $100
The dealer(dealer1) has $200

Type "play", "reconfigure" or "quit"
-> play
Bet amount for p1: 20
Bet amount for p2: 20

vvvvvv p1 vvvvvv
6S, 7H
Current sum: 13
hit
6S, 7H, 3C
Current sum: 16
stand
^^^^^^^^^^^^

vvvvvv p2 vvvvvv
10D, 5C
Current sum: 15
hit
10D, 5C, KD
p2 is busted
^^^^^^^^^^^^

vvvvvv dealer1 vvvvvv
KH, 9H
Current sum: 19
stand
^^^^^^^^^^^^
p1: $80
p2: $80
dealer: $240
Type "play", "reconfigure" or "quit"
-> quit
```

## Further (Potential) Improvements
* Include a custom C function pointer parameter in initGame to enable training of a machine learning / genetic algorithm model
