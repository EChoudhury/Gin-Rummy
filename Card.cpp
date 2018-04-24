
#include "Card.h"
#include <iostream>

using namespace std;

Card::Card(int num, int su) { number = num; suit = su; }

int Card::getSuit() { return suit; }

int Card::getNumber() { return number; }

void Card::cardDisplay() { cout << number << ", " << suit; }

bool Card::operator<(Card a) { return (this->number < a.number); } 

Card::~Card() { }
