#include "Card.h"
#include "Dealing.h"
#include "Gameplay.h"
#include "Scoring.h"
#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {

	srand(time(0));

	vector<Card> deck;

	stack<Card> draw;
	stack<Card> discard;
	vector<Card> playerHand;
	vector<Card> compHand;
	
	createDeck(draw, deck);
	
	int n = draw.size();

	cout << n << endl;

	Card x = draw.top();

	x.cardDisplay();

	cout<<endl;

	dealToHands(10, playerHand, draw);
	dealToHands(10, compHand, draw);
	dealToDiscard(1, discard, draw);

	cout << draw.size() << " " << playerHand.size() << " " << compHand.size() <<  " " << discard.size() << endl;

	int i = 0;

	while (i <= 2) {
		playerTurn(playerHand, draw, discard);
		i++;
	}

	reset(deck, draw, discard, playerHand, compHand);

	cout << draw.size() << " " << playerHand.size() << " " << compHand.size() <<  " " << discard.size() << endl;
	
	cout << endl;

return 0;
}
