
//Card.h

#ifndef CARD_H
#define CARD_H

class Card {

public:
	Card(int num, int su);
	int getSuit();
	int getNumber();
	void cardDisplay();
	bool operator<(Card a);
	~Card();
private:
	int suit;
	int number;

	
};

#endif
