#include "Gameplay.h"
#include "Scoring.h"
#include "Dealing.h"
#include "Card.h"
#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

string names[] = {"Ace", "Two", "Three", "Four", "Five",
 "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

string suits[] = {"Spades", "Hearts", "Clubs", "Diamonds"};

string abrevNames[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
char abrevSuits[] = {'S','H','C','D'};

void displayBoard(vector<Card>& h) {	
	
	for (int x = 0; x < h.size(); x++) {
		Card c = h[x];		
		int num = c.getNumber();
		int suit = c.getSuit();
		cout << abrevNames[num-1] << "---" << abrevSuits[suit-1]<< "\t";
	}

	cout << endl;

	for (int i = 0; i < h.size(); i++) {
		cout << "|" << "   " << "|" << "\t";
	}

	cout << endl;

	for (int i = 0; i < h.size(); i++) {
		cout << "|" << " " << i + 1 << " " << "|" << "\t";
	}

	cout << endl;
	
	for (int i = 0; i < h.size(); i++) {
		cout << "|" << "   " << "|" << "\t";
	}
	
	cout << endl;

	for (int x = 0; x < h.size(); x++) {
		Card c = h[x];	
		int num = c.getNumber();
		int suit = c.getSuit();	
		cout << abrevSuits[suit-1] << "---" << abrevNames[num-1] << "\t";
	}
	
	cout << endl;

	for (int x = 0; x < h.size(); x++) {	
		Card c = h[x];
		int num = c.getNumber();
		int suit = c.getSuit();
		cout << names[num-1] << "\t";
	}

	cout << endl;

	for (int x = 0; x < h.size(); x++) {	
		Card c = h[x];
		int suit = c.getSuit();
		cout << "of " << abrevSuits[suit-1] << "\t";
	}
	
	cout << endl;
}

int input(bool v, string s, int max, int min) {
	
	int choice;

	while (!v) {
		
		v = true;
	
		cout << endl << s;
		cin >> choice;
		
		if (cin.fail() || choice > max || choice < min) {
			cin.clear();
			cin.ignore();
			cout << "Sorry, that response was not understood. Please try again." << endl;
			v = false;	
		}

		cout << "You chose " << choice << endl;
		
	}

	return choice;
}

void playerTurn(vector<Card>& player, stack<Card>& draw, stack<Card>& discard) {
	bool valid = false;
	int choice;
	string selectDraw = "Select from the draw pile (1) or discard pile (2)! Press (3) to sort! (1-3)\n>";
	string selectDiscard = "Select card to discard! (1-11)\n>";

	displayBoard(player);
	
	choice = input(valid, selectDraw, 2, 1);

	if (choice == 1) {
		dealToHands(1, player, draw);
		cout << "You took a card from draw! " << choice << endl;
		displayBoard(player);
		cout <<"Your deadwood value is " << deadwoodPairsRuns(player) << endl;

		choice = input(valid, selectDiscard, 11, 1);
	
		choice -= 1;
		Card c = player[choice];
		discard.push(c);
		player.erase(player.begin() + choice);

		displayBoard(player);
		cout <<"Your deadwood value is " << deadwoodPairsRuns(player) << endl;
	}
	/*else if (choice == 3) {
		sort(player.begin(), player.end());
	}
*/
	 else {
		dealToHands(1, player, discard);
		cout << "You took a card from discard! " << choice << endl;
		displayBoard(player);
		cout <<"Your deadwood value is " << deadwoodPairsRuns(player) << endl;
		
		choice = input(valid, selectDiscard, 11, 1);

		choice -= 1;
		Card c = player[choice];
		discard.push(c);
		player.erase(player.begin() + choice);

		displayBoard(player);
		cout <<"Your deadwood value is " << deadwoodPairsRuns(player) << endl;

	}
	system("clear"); //<-- Confirm that this doesn't mess stuff up.
}
