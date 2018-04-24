#ifndef GAMEPLAY_H
#define	GAMEPLAY_H

#include "Card.h"
#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

void displayBoard(vector<Card>& h);
void playerTurn(vector<Card>& player, stack<Card>& draw, stack<Card>& discard);
int input(bool v, string s, int max, int min);

#endif
