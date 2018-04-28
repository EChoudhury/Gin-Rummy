#ifndef SCOREKEEPER_H
#define SCOREKEEPER_H

#include "Card.h"
#include <iostream>
#include <vector>

using namespace std;

class ScoreKeeper {

private:

int melds;
int playerscore;
int deadwood;
int totalScore;
int wins;
vector<Card> playerHand;

public:

ScoreKeeper();
int getMelds();
void updateScore(int score);
void updateWins();
int getScore();
int getPlayerScore();
int getDeadwood();
int checkWin();
void getPlayerHand(vector<Card> h);
int scoreHand(vector<Card> h);

};

#endif
